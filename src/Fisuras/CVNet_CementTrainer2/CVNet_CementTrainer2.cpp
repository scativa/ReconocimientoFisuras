#include "pch.h"
#include "Net.h"
#include "CementTrainer.h"
#include "cmdlineopt.h"

using namespace cv;
using namespace std;

template <typename DataLoader>
float test_batch(Net MODEL, DataLoader& DATA_LOADER, size_t SIZE) {
    std::printf("Testing... ");

    MODEL->eval();
    int64_t correct = 0;
    for (const auto& batch : DATA_LOADER) {
        auto prediction = MODEL->forward(batch.data);
        correct += prediction.argmax(1).eq(batch.target).sum().template item<int64_t>();
    };

    float ACCURACY = ((float)correct / (float)SIZE);
    std::printf("Accuracy: %.3f% \r\n", ACCURACY);
    return ACCURACY;
};

template <typename DataLoader>
void train_batch(size_t EPOCH, Net MODEL, DataLoader& DATA_LOADER, torch::optim::Optimizer& optimizer, size_t SIZE) {
    std::printf("Trainning... ");

    MODEL->train();
    size_t batch_idx = 0;
    for (auto& batch : DATA_LOADER) {
        optimizer.zero_grad();

        auto prediction = MODEL->forward(batch.data);
        auto loss = torch::nll_loss(prediction, batch.target);

        loss.backward();
        optimizer.step();

        std::printf("\rTrain Epoch: %ld [%zd/%zd] Loss: %.4f ", EPOCH, batch_idx++ * m_batch_size, SIZE, loss.template item<float>());
    }
    std::printf("\r\n");
};

torch::Device device = (torch::cuda::is_available() ? torch::kCUDA : torch::kCPU);

int main(int argc, char* argv[]) {

    cout << "Cement Trainer2 ABc" << endl; // exit(0);

    CmdLineOpt opt(argc, argv);

    //------------------------------------------------------------------------------------------------
    Net net; // auto net = std::make_shared<NetImpl>();
    // es equivalente ya que uso el TORCH_MODULE(Net) para "envolver la definicion" y poder usar la
    // definicion como Net simplemente. explicado en profundidad MUY POCO claro en,
    // https://pytorch.org/tutorials/advanced/cpp_frontend.html
    net->to(device); // lo paso a GPU si existe.

    if (opt.Verbose()) {
        std::cout << "Device: ";
        if (device == torch::kCUDA) cout << "CUDA"; else cout << "CPU";
        cout << endl;
    }

    //------------------------------------------------------------------------------------------------
    // Si existe un entrenamiento previo arranca desde ahi, sino empieza desde cero/
    if (opt.NewModel())
        try {
        torch::load(net, opt.ModelFN());
        if (opt.Verbose())
            cout << "Archivo '" << opt.ModelFN() << "'!" << endl;
    }
    catch (...) { if (opt.Verbose()) cout << "Archivo '" << opt.ModelFN() << "' no encontrado. Creando '" << opt.ModelFN() << "' de cero." << endl; }
    else
        if (opt.Verbose()) cout << "Creando '" << opt.ModelFN() << "' de cero." << endl;

    //------------------------------------------------------------------------------------------------
    // 5y9wdsg2zt-1.zip: Crea dos subcarpetas Negative y Positive, se decomprimio en esta direccion.
    // https://data.mendeley.com/datasets/5y9wdsg2zt/1
    string DATA_DIR = "C:/Repositories/CementCrack/5y9wdsg2zt-1";
    //string DATA_DIR = "C:\\Repositories\\CementCrack\\SDNET2018";
    // https://www.ncbi.nlm.nih.gov/pmc/articles/PMC6247444/
    //------------------------------------------------------------------------------------------------
    // Variables con las cuales voy a entrenar la RED
    //------------------------------------------------------------------------------------------------

    // torch::data::datasets::Create_tensor_files_from_images(DATA_DIR, opt.DatasetPrefix(), opt.PercentToTrain(), opt.OverwriteDataset());

    auto m_data_set_train =
        torch::data::datasets::Cement(DATA_DIR, opt.DatasetPrefix(), torch::data::datasets::Cement::Mode::Train)/*TRAIN*/
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
        torch::data::datasets::Cement(DATA_DIR, opt.DatasetPrefix(), torch::data::datasets::Cement::Mode::Test)/*TEST*/
        .map(torch::data::transforms::Stack<>());

    auto m_data_loader_test =
        torch::data::make_data_loader(
            m_data_set_test,
            torch::data::DataLoaderOptions().batch_size(m_batch_size).workers(4));

    std::cout << "m_data_set_train size: " << m_data_set_train.size().value() << endl;
    std::cout << "m_data_set_test size: " << m_data_set_test.size().value() << endl;


    //------------------------------------------------------------------------------------------------
    // Aca elijo que algoritmo de aprendizaje que quiero, hay bocha, se pueden probar..
    // https://pytorch.org/cppdocs/api/namespace_torch__optim.html
    // https://arxiv.org/pdf/1412.6980.pdf
    //------------------------------------------------------------------------------------------------
    //torch::optim::SGD optimizer(net.parameters(), torch::optim::SGDOptions(0.1).momentum(0.4));
    torch::optim::Adam optimizer(net->parameters(), torch::optim::AdamOptions(2e-4).beta1(0.5));
    //--------------------------------------------------------------------------------------------

    size_t N_EPOCH_TO_TRAIN = opt.EpochCount();
    float m_best_accuracy = 0.0f;

    for (int epoch = 0; epoch < N_EPOCH_TO_TRAIN; epoch++) {
        cout << endl << "Epoch: " << epoch << "/" << N_EPOCH_TO_TRAIN << ":" << endl;
        // Testea las imagenes de entrenamiento
        size_t m_train = m_data_set_train.size().value();
        cout << "Try " << float(m_train / 1000) << "k train data: ";
        test_batch(net, *m_data_loader_train, m_train);

        //Ahora testeo con imagenes con la cuales no entrena y nunca vio, si la red aprendio la graba a disco.
        size_t m_test = m_data_set_test.size().value();
        cout << "Try " << float(m_test / 1000) << "k test data: ";
        float m_accuracy = test_batch(net, *m_data_loader_test, m_test);

        if (m_accuracy > m_best_accuracy) {
            m_best_accuracy = m_accuracy;
            cout << "Guardando '" << opt.ModelFN() << "'... ";
            torch::save(net, opt.ModelFN());
            cout << "Listo!" << endl;
        }

        //Haciendo una pasada por todas las imagenes para entrenar.
        cout << "Entrenando:" << endl;
        train_batch(epoch, net, *m_data_loader_train, optimizer, m_train);
    };


    //system("pause");
    return 0;
};

