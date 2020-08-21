#include "pch.h"
#include "Net.h"
#include "CementTrainer.h"
#include <cmdlineopt.hpp> 
#include "../common/globals.h"

#include "Tensor_utils.h"

using namespace std;

template <typename DataLoader>
float test_batch(Net MODEL, DataLoader& DATA_LOADER, size_t SIZE) {
    printf("Testing... ");

    MODEL->eval();
    int64_t correct = 0;
    for (const auto& batch : DATA_LOADER) {
        auto prediction = MODEL->forward(batch.data);
        correct += prediction.argmax(1).eq(batch.target).sum().template item<int64_t>();
    };

    float ACCURACY = ((float)correct / (float)SIZE);
    printf("Accuracy: %.3f \r\n", ACCURACY);
    return ACCURACY;
};

template <typename DataLoader>
void train_batch(size_t EPOCH, Net MODEL, DataLoader& DATA_LOADER, torch::optim::Optimizer& optimizer, size_t SIZE) {
    printf("Trainning... ");

    MODEL->train();
    size_t batch_idx = 0;
    for (auto& batch : DATA_LOADER) {
        optimizer.zero_grad();

        auto prediction = MODEL->forward(batch.data);
        auto loss = torch::nll_loss(prediction, batch.target);

        loss.backward();
        optimizer.step();

        printf("\rTrain Epoch: %ld [%zd/%zd] Loss: %.4f ", EPOCH, batch_idx++ * m_batch_size, SIZE, loss.template item<float>());
    }
    printf("\r\n");
};

torch::Device device = (torch::cuda::is_available() ? torch::kCUDA : torch::kCPU);

int main(int argc, char* argv[]) {

    cout << "Cement Trainer" << endl;

try {
    // Opciones de línea de comando
    // --input=E:\data\CementCrack\5y9wdsg2zt-1 --prefix=32x32(0.50) --epoch=1 --model=model.pt --verbose
    cmdlineopt::CmdLineOpt opt(argc, argv);
    opt.Parse();

    // Opciones generales
    globals::quiet_mode = opt.Quiet();
    globals::verbose_mode = opt.Verbose();
    if (globals::verbose_mode) opt.Show();
   
    // Opciones Archivos
    string DATA_DIR = opt.Input();
    string prefix = opt.Prefix();

    // Opciones Entrenamiento
    string modelfn = opt.Model();

    // Device: CPU - GPU
    if (globals::verbose_mode) {
        std::cout << "Device: ";
        if (device == torch::kCUDA) cout << "CUDA"; else cout << "CPU";
        cout << endl;
    }

    //------------------------------------------------------------------------------------------------
    Net net; // auto net = make_shared<NetImpl>();
    // es equivalente ya que uso el TORCH_MODULE(Net) para "envolver la definicion" y poder usar la
    // definicion como Net simplemente. explicado en profundidad MUY POCO claro en,
    // https://pytorch.org/tutorials/advanced/cpp_frontend.html
    
    // Revisar si esto es útil y necesario
    net->to(device); // lo paso a GPU si existe.

    //------------------------------------------------------------------------------------------------
    // Si existe un entrenamiento previo arranca desde ahi, sino empieza desde cero/
    try {
        torch::load(net, modelfn);
        if (globals::verbose_mode) cout << "Archivo '" << modelfn << "'!" << endl;
    }
    catch (...) { 
        if (globals::verbose_mode) cout << "Archivo '" << modelfn << "' no encontrado. Creando '" << modelfn << "' de cero." << endl;
    }

    //------------------------------------------------------------------------------------------------
    // 5y9wdsg2zt-1.zip: Crea dos subcarpetas Negative y Positive, se decomprimio en esta direccion.
    // https://data.mendeley.com/datasets/5y9wdsg2zt/1
    // Windows = "C:/Repositories/CementCrack/5y9wdsg2zt-1"
    // Linux = "/home/seba/Repositories/CementCrack/5y9wdsg2zt-1"
    // Google Colab = "/content/5y9wdsg2zt-1"
    //string DATA_DIR = "C:\\Repositories\\CementCrack\\SDNET2018";
    // https://www.ncbi.nlm.nih.gov/pmc/articles/PMC6247444/
    
    
    //------------------------------------------------------------------------------------------------
    // Variables con las cuales voy a entrenar la RED
    //------------------------------------------------------------------------------------------------
    auto m_data_set_train =
        torch::data::datasets::Cement(DATA_DIR, prefix, torch::data::datasets::Cement::Mode::Train)/*TRAIN*/
        /* creo q la opcion que le sigue es para que vaya sacando secuencialmente el par <IMG,LABEL>
        y no seleccione al azar, xq ya lo mezcle cuando cree objeto <Cement>.*/
        .map(torch::data::transforms::Stack<>());

    auto m_data_loader_train =
        torch::data::make_data_loader(
            m_data_set_train, // para que no haga copias x ahi al pedo.
            /*opciones el tamano del lote y la cantidad de threads para cargar rapido*/
            torch::data::DataLoaderOptions().batch_size(m_batch_size).workers(4));
    //------------------------------------------------------------------------------------------------
    // Variables para testear la RED, la RED nunca las aprende, aca es donde tiene que generalizar.
    //------------------------------------------------------------------------------------------------
    auto m_data_set_test =
        torch::data::datasets::Cement(DATA_DIR, prefix, torch::data::datasets::Cement::Mode::Test)/*TEST*/
        .map(torch::data::transforms::Stack<>());

    auto m_data_loader_test =
        torch::data::make_data_loader(
            m_data_set_test,
            torch::data::DataLoaderOptions().batch_size(m_batch_size).workers(4));

    cout << "m_data_set_train size: " << m_data_set_train.size().value() << endl;
    cout << "m_data_set_test size: " << m_data_set_test.size().value() << endl;


    //------------------------------------------------------------------------------------------------
    // Aca elijo que algoritmo de aprendizaje que quiero, hay bocha, se pueden probar..
    // https://pytorch.org/cppdocs/api/namespace_torch__optim.html
    // https://arxiv.org/pdf/1412.6980.pdf
    //------------------------------------------------------------------------------------------------
    //torch::optim::SGD optimizer(net.parameters(), torch::optim::SGDOptions(0.1).momentum(0.4));
    //torch::optim::Adam optimizer(net->parameters(), torch::optim::AdamOptions(2e-4).beta1(0.5));
    torch::optim::Adam optimizer(net->parameters(), torch::optim::AdamOptions(2e-4).betas(make_tuple (0.5, 0.5)));
    //--------------------------------------------------------------------------------------------

    size_t N_EPOCH_TO_TRAIN = opt.Epoch();
    float m_best_accuracy = 0.0f;

    for (size_t epoch = 0; epoch < N_EPOCH_TO_TRAIN; epoch++) {
        if (!globals::quiet_mode) cout << endl << "Epoch: " << epoch << "/" << N_EPOCH_TO_TRAIN << ":" << endl;
        // Testea las imagenes de entrenamiento
        size_t m_train = m_data_set_train.size().value();
        if (!globals::quiet_mode) cout << "Try " << float(m_train / 1000) << "k train data: ";
        test_batch(net, *m_data_loader_train, m_train);

        //Ahora testeo con imagenes con la cuales no entrena y nunca vio, si la red aprendio la graba a disco.
        size_t m_test = m_data_set_test.size().value();
        if (!globals::quiet_mode) cout << "Try " << float(m_test / 1000) << "k test data: ";
        float m_accuracy = test_batch(net, *m_data_loader_test, m_test);

        if (m_accuracy > m_best_accuracy) {
            m_best_accuracy = m_accuracy;
            if (globals::verbose_mode) cout << "Guardando '" << modelfn << "' ";
            torch::save(net, modelfn);
            if (globals::verbose_mode) cout << "Listo!" << endl;
        }

        //Haciendo una pasada por todas las imagenes para entrenar.
        if (globals::verbose_mode) cout << "Entrenando:" << endl;
        train_batch(epoch, net, *m_data_loader_train, optimizer, m_train);
    };

    return 0;
}
catch (exception e) {
    cerr << "Error: " << e.what();
}
};

