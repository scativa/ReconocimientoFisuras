#include <iostream>
//#include <cxxopts.hpp>
#include "cmdlineopt.h"
#include "pch.h"

CmdLineOpt::CmdLineOpt(int argc, char* argv[]) {
    try {
        cxxopts::Options options(argv[0], " - example command line options");

        options
            .positional_help("[optional args]")
            .show_positional_help()
            //.parse_positional({ "first", "second", "last" })
            ;

        options
            .allow_unrecognised_options()
            .add_options()
            ("m,model_fn", "Nombre del archivo 'model' donde se leen y guardan los pesos de la red", cxxopts::value<std::string>()->implicit_value(model_fn))
            ("n,new_model", "Indica si se se usa como base el archivo 'model' existente")
            ("e,epoch_count", "Fija la cantidad de epoch para el entrenamiento", cxxopts::value<int>())

            ("p,dataset_prefix", "Prefijo para los nombres de los archivos de dataset '*.tensor' (ej. 'PREFIJO_TRAIN_IMAGES.tensor'", cxxopts::value<std::string>(dataset_prefix))
            ("o,overwrite_dataset", "Indica si se fuerza la sobreescritura de los archivos de dataset '*.tensor'")

            ("t,percent_to_train", "Porcentaje de imágenes para entrenamiento", cxxopts::value<float>())

            ("v,verbose","Muestra...")
            ;

        auto result = options.parse(argc, argv);

        if (result.count("help")) {
            std::cout << options.help({ ""}) << std::endl;
            exit(0);
        }

        if (result.count("dataset_prefix")) {
            dataset_prefix = result["dataset_prefix"].as<std::string>() + std::string("_");
            std::cout << "dataset_prefix=" << dataset_prefix << std::endl;
        }

        if (result.count("model_fn")) {
            model_fn = result["model_fn"].as<std::string>();
            std::cout << "model_fn=" << model_fn << std::endl;
        }

        new_model = (bool) result.count("new_model");
        overwrite_dataset = (bool) result.count("overwrite_dataset");

        if (new_model) std::cout << "new_model set on" << std::endl;
        if (overwrite_dataset) std::cout << "overwrite_dataset set on" << std::endl;

        if (result.count("epoch_count")) {
            epoch_count = result["epoch_count"].as<int>();
            std::cout << "epoch_count=" << epoch_count << std::endl;
        }

        if (result.count("percent_to_train")) {
            percent_to_train = result["percent_to_train"].as<float>();
            std::cout << "percent_to_train=" << percent_to_train << std::endl;
            if (percent_to_train >= 1.0f)
                throw cxxopts::OptionException("El valor de percent_to_train debe ser menor a 1.00");
        }

        verbose = (bool) result.count("verbose");
        if (verbose) std::cout << "verbose set on" << std::endl;
    }
    catch (const cxxopts::OptionException& e) {
        std::cout << "CmdLineOpt error: " << e.what() << std::endl;
        exit(1);
    }
}
