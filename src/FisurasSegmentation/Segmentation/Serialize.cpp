#include "pch.h"
#include "Serialize.h"

Serialize::Serialize(const std::string& ADDRESS) {
    IMG = Get_structure_from_directory(ADDRESS + "\\IMG\\");
    MASK = Get_structure_from_directory(ADDRESS + "\\MASK\\");
    Proccess_picture();
}

bool Serialize::Directory_exists(const std::string& DIRNAME) {
    #ifdef WINDOWS_COMPILER_VERSION
        DWORD ftyp = GetFileAttributesA(DIRNAME.c_str());
        if (ftyp == INVALID_FILE_ATTRIBUTES)
            return false;  //something is wrong with your path!

        if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
            return true;   // this is a directory!

        return false;    // this is not a directory!
    #endif // WINDOWS_COMPILER_VERSION

    #ifndef WINDOWS_COMPILER_VERSION
        std::cout << "Falta version de la funcion equivalente para LINUX." << std::endl;
        std::cout << "bool Serialize::Directory_exists(const std::string & DIRNAME)" << std::endl;
        exit(-1);
    #endif
};

std::vector<std::string> Serialize::Get_structure_from_directory(const std::string& ADDRESS) {
    #ifdef  WINDOWS_COMPILER_VERSION
        std::vector<std::string> TYPES = { "png","jpg" };
        std::vector<std::string> FILELIST;
        HANDLE hFind;
        WIN32_FIND_DATA data;

        for (auto datatype : TYPES) {
            hFind = FindFirstFile(std::string(ADDRESS + "*." + datatype).c_str(), &data);
            if (hFind != INVALID_HANDLE_VALUE) {
                do {
                    FILELIST.push_back(data.cFileName);
                } while (FindNextFile(hFind, &data));
                FindClose(hFind);
            }
        }
        return FILELIST;
    #endif // WINDOWS_COMPILER_VERSION
    
    #ifndef WINDOWS_COMPILER_VERSION
        std::cout << "Falta version de la funcion equivalente para LINUX." << std::endl;
        std::cout << "std::vector<std::string> Serialize::Get_structure_from_directory(const std::string& ADDRESS)" << std::endl;
        exit(-1);
    #endif
};

std::vector<cv::Mat> Serialize::Augmentation(const cv::Mat& SRC, bool FLIP, bool ROTATE) {
    std::vector<cv::Mat> VEC;
    cv::Mat DES;

    if (FLIP) {
        flip(SRC, DES, 0);
        VEC.push_back(DES.clone());
        flip(SRC, DES, 1);
        VEC.push_back(DES.clone());
        flip(SRC, DES, -1);
        VEC.push_back(DES.clone());
    };
    if (ROTATE) {
        rotate(SRC, DES, cv::ROTATE_90_CLOCKWISE);
        VEC.push_back(DES.clone());
        rotate(SRC, DES, cv::ROTATE_180);
        VEC.push_back(DES.clone());
        rotate(SRC, DES, cv::ROTATE_90_COUNTERCLOCKWISE);
        VEC.push_back(DES.clone());
    }
    return VEC;
};

void Serialize::Proccess_picture() {
    //------------------------------------------------------------------------------------------------
    // Verifico si ya existe la estructura de directorios, sino es asi, la crea y prepara las imagenes
    //------------------------------------------------------------------------------------------------
    if (!Directory_exists(Folder_with_Procceced_pictures)) {
    #ifdef  WINDOWS_COMPILER_VERSION
        CreateDirectory(std::string(Folder_with_Procceced_pictures).c_str(), NULL);
        CreateDirectory(std::string(Folder_with_Procceced_pictures + "\\CRACK").c_str(), NULL);
        CreateDirectory(std::string(Folder_with_Procceced_pictures + "\\CRACK\\IMG").c_str(), NULL);
        CreateDirectory(std::string(Folder_with_Procceced_pictures + "\\CRACK\\MASK").c_str(), NULL);
        CreateDirectory(std::string(Folder_with_Procceced_pictures + "\\NO_CRACK").c_str(), NULL);
        CreateDirectory(std::string(Folder_with_Procceced_pictures + "\\NO_CRACK\\IMG").c_str(), NULL);
        CreateDirectory(std::string(Folder_with_Procceced_pictures + "\\NO_CRACK\\MASK").c_str(), NULL);
    #endif // WINDOWS_COMPILER_VERSION

    #ifndef WINDOWS_COMPILER_VERSION
        std::cout << "Falta version de la funcion equivalente para LINUX." << std::endl;
        std::cout << "CreateDirectory()" << std::endl;
        exit(-1);
    #endif // !WINDOWS_COMPILER_VERSION


    //------------------------------------------------------------------------------------------------
    //  Voy recorriendo cada imagen encontrada con su respectivo MASK y me voy fijando cuadricula x cuadricula
    //  si existe una fisura o no, luego grabo los resultados en los directorios previamente creados.
    //------------------------------------------------------------------------------------------------
        for (size_t idx = 0; idx < IMG.size(); idx++) {
            auto imagen = cv::imread(Folder_with_RAW_pictures + "\\IMG\\" + IMG[idx], 0);
            auto imagen_mask = cv::imread(Folder_with_RAW_pictures + "\\MASK\\" + MASK[idx], 0);
            //------------------------------------------------------------------------------------------------
            // Tengo que RECORTAR la imagen, para que pueda barrerla con la cuadricula, sin desperdicio.
            //------------------------------------------------------------------------------------------------
            auto m_size_max_cols = (imagen.cols / image_size) * image_size;
            auto m_size_max_rows = (imagen.rows / image_size) * image_size;
            cv::Mat image_crop(imagen, cv::Rect(0, 0, m_size_max_cols, m_size_max_rows));
            cv::Mat image_mask_crop(imagen_mask, cv::Rect(0, 0, m_size_max_cols, m_size_max_rows));
            //------------------------------------------------------------------------------------------------
            // Analizo cuadricula x cuadricula y selecciono si tiene fractura o no, dependiendo de la mascara
            //------------------------------------------------------------------------------------------------
            cv::Mat white_image = cv::Mat(image_size, image_size, 0, cv::Scalar(255));
            cv::Mat dst = cv::Mat(cv::Size(image_size, image_size), 0, cv::Scalar(0));
            for (size_t i = 0; i <= image_mask_crop.cols - image_size; i += image_size) {
                for (size_t j = 0; j <= image_mask_crop.rows - image_size; j += image_size) {

                    cv::Rect rect(i, j, image_size, image_size);
                    cv::Mat image_chunk(image_crop, rect);
                    cv::Mat image_mask_chunk(image_mask_crop, rect);

                    cv::bitwise_xor(image_mask_chunk, white_image, dst);
                    int margin = cv::countNonZero(dst);
                    if (margin == 0) {
                        //No hay fracturas en esta porcion de la imagen.
                        static size_t count = 0;
                        cv::imwrite(Folder_with_Procceced_pictures + "\\NO_CRACK\\IMG\\" + std::to_string(count) + ".png", image_chunk, { cv::IMWRITE_PNG_COMPRESSION, 0 });
                        cv::imwrite(Folder_with_Procceced_pictures + "\\NO_CRACK\\MASK\\" + std::to_string(count) + ".png", image_mask_chunk, { cv::IMWRITE_PNG_COMPRESSION, 0 });
                        count++;
                    }
                    //if (margin > (0.04 * (image_size * image_size))) {
                    //    // Hay "SUFICIENTE" fractura en esta imagen como para guardarla como un caso positivo.
                    //    // Como las imagenes de fracturas cuando se va examinando la cuadricula terminan siendo 
                    //    // menos que las que no tienen fractura, uso AUMENTACION para que rellenen el DATASET.
                    else {
                        // Existe en algun lado de la region selecionada alguna fracrura en la imagen.
                        static size_t count = 0;
                        auto V1 = Augmentation(image_chunk, true, true);
                        auto V2 = Augmentation(image_mask_chunk, true, true);

                        for (size_t k = 0; k < V1.size(); k++) {
                            cv::imwrite(Folder_with_Procceced_pictures + "\\CRACK\\IMG\\" + std::to_string(count) + ".png", V1[k], { cv::IMWRITE_PNG_COMPRESSION, 0 });
                            cv::imwrite(Folder_with_Procceced_pictures + "\\CRACK\\MASK\\" + std::to_string(count) + ".png", V2[k], { cv::IMWRITE_PNG_COMPRESSION, 0 });
                            count++;
                        }
                    }
                }
            }
        }
    };
};
