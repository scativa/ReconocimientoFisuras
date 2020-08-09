#include "pch.h"
#include "Cement.h"
//#include "cmdlineopt.h"

#include <cmdlineopt.hpp> 
#include "../common/globals.h"

const uint32_t m_batch_size = 32; // establecido en Net.h

using namespace cv;
using namespace std;

torch::Device device = (torch::cuda::is_available() ? torch::kCUDA : torch::kCPU);

int main(int argc, char* argv[]) {


    cout << "Cement Trainer" << endl; // exit(0);

    // --input=C:/Users/User/Proyectos/data/CementCrack/5y9wdsg2zt-1 --verbose --prefix=100x100 --percent_to_train=0.75 --resize_x=32 --resize_y=32
    cmdlineopt::CmdLineOpt opt(argc, argv);
    opt.Parse();

    globals::verbose_mode = opt.Verbose();
    if (globals::verbose_mode) opt.Show();

    string DATA_DIR = opt.Input();
    string prefix = "";
    opt.Parse("prefix", prefix);

    string modelfn = opt.Model();

    int resize_x = 64;
    int resize_y = 64;
    opt.Parse("resize_x", resize_x);
    opt.Parse("resize_y", resize_y);

    pair<uint32_t, uint32_t> image_resize(resize_y, resize_x);

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

    torch::data::datasets::Create_tensor_files_from_images(DATA_DIR, prefix, 0.75f, image_resize, true);
    torch::data::datasets::Create_tensor_files_from_images(DATA_DIR, prefix, 0.75f, image_resize, true);

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


    //system("pause");
    return 0;
};


