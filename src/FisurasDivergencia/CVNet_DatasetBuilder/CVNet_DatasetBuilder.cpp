#include "pch.h"
#include "DataBuilder.h"
//#include "cmdlineopt.h"

#include <cmdlineopt.hpp> 
#include "../common/globals.h"

const uint32_t m_batch_size = 32; // establecido en Net.h

using namespace cv;
using namespace std;

torch::Device device = (torch::cuda::is_available() ? torch::kCUDA : torch::kCPU);

int main(int argc, char* argv[]) {
    cout << "Cement DatasetBuilder" << endl;

try {
    // Opciones de línea de comando
    // --input=C:/Users/User/Proyectos/data/CementCrack/5y9wdsg2zt-1-c20 --training_percentage=0.15 --prefix=64 --size_x=64 --size_y=64 --verbose 
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
    float Percentage_of_pictures_used_to_train = opt.TrainingPercentage();

    // Opciones tamaño imagen
    int resize_x = (opt.SizeX() > 0) ? opt.SizeX() : 64; // Se usa 64x64 en caso de hacer el resize <= 0. Significa que no se pasó como parámetro
    //int resize_y = (opt.SizeY() > 0) ? opt.SizeY() : 64;

    assert(resize_y == resize_y);
    pair<uint32_t, uint32_t> image_resize(resize_x, resize_x);

    // Device: CPU - GPU
    if (globals::verbose_mode) {
        std::cout << "Device: ";
        if (device == torch::kCUDA) cout << "CUDA"; else cout << "CPU";
        cout << endl;
    }

    //------------------------------------------------------------------------------------------------
    // 5y9wdsg2zt-1.zip: Crea dos subcarpetas Negative y Positive, se decomprimio en esta direccion.
    // https://data.mendeley.com/datasets/5y9wdsg2zt/1
    //string DATA_DIR = "C:/Users/User/Proyectos/data/CementCrack/5y9wdsg2zt-1";
    //string DATA_DIR = "C:\\Repositories\\CementCrack\\SDNET2018";
    // https://www.ncbi.nlm.nih.gov/pmc/articles/PMC6247444/
    //------------------------------------------------------------------------------------------------
    // Variables con las cuales voy a entrenar la RED
    //------------------------------------------------------------------------------------------------

    torch::data::datasets::Create_tensor_files_from_images(DATA_DIR, prefix, Percentage_of_pictures_used_to_train, image_resize, true);

#ifdef ANULAR
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

    std::cout << "m_data_set_train size: " << m_data_set_train.size().value() << endl;
    std::cout << "m_data_set_test size: " << m_data_set_test.size().value() << endl;
#endif

    return 0;
}
catch (exception e) {
    cerr << "Error: " << e.what();
}
};


