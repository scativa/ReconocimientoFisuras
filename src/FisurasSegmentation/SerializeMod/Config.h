#pragma once
#include "pch.h"

// Comentar si solo quiero visualizar los resultados de un modelo previamente entranado
//#define TRAIN_NET true 

#define WINDOWS_COMPILER_VERSION true 
// Faltan las versiones para LINUX sobre el manejo de directorios.
// Cuando esten se puede poner false en el flag.

/*
#ifdef WINDOWS_COMPILER_VERSION
#include <windows.h>
#endif // WINDOWS_COMPILER_VERSION
*/

// Indica si se activa el mode Verbose donde muestra en pantalla cosas
//bool Verbose;


//--------------------------------------------------------------------------------------------------
// la RED tendra una entrada de image_size*image_size con 8bit por pixel.(escala de grises)
constexpr size_t image_size = 96; 

//--------------------------------------------------------------------------------------------------
// CONSTANTES PARA LA CLASE DATASET
//--------------------------------------------------------------------------------------------------
/*
constexpr size_t train_batch_size = 4;
constexpr size_t test_batch_size  = 4;
const float Percentage_of_pictures_used_to_train = 0.85f;
const std::vector<std::string> classes = { "CRACK" };// directorio de donde levanta el DATASET.
const torch::DeviceType running_into = torch::cuda::is_available() ? torch::kCUDA : torch::kCPU;
*/

//--------------------------------------------------------------------------------------------------
// CONSTANTES PARA LA CLASE SERIALIZE
//--------------------------------------------------------------------------------------------------
// Abajo estan donde se encuentras las imagenes que tengo que procesar, recordar que como se trata
// de una RED de Segmentacion, debe tener su imagen y la mascara de la misma 
// que indica donde esta el objeto que quiero detectar, por eso, en el directorio \imgs estan las
// imagenes de las fracturas y en el directorio \masks contienen la ubicacion de las fracturas para
// poder saber donde se alojan.
//static const std::string Folder_with_RAW_pictures = "C:/Users/User/Proyectos/data/Samples_Segmentation";
//static const std::string FRAW = "C:/Users/User/Proyectos/data/Samples_Segmentation";

// En este directorio es donde crea la estructura de archivos que posteriormente voy a levantar con el DATASET
//static const std::string FProc = "C:/Users/User/Proyectos/data/Segmentation";
//Folder_with_Procceced_pictures
//├── CRACKS
//│   ├── IMG
//│   │   ├── 0.png
//│   │   ├── 1.png
//│   │   ├── ...
//│   ├── MASK
//│   │   ├── 0.png
//│   │   ├── 1.png
//│   │   ├── ...
//├── NO_CRACKS
//│   ├── IMG
//│   │   ├── 0.png
//│   │   ├── 1.png
//│   │   ├── ...
//│   ├── MASK
//│   │   ├── 0.png
//│   │   ├── 1.png
//│   │   ├── ...

//--------------------------------------------------------------------------------------------------
// Directorio donde estan los PNG y/o los JPG que quiero analizar.-----------------------------
// static const std::string Folder_with_JPGs = "C:/Users/User/Proyectos/data/Positive";
//static const std::string Folder_with_JPGs = "C:/Repositories/CementCrack/5y9wdsg2zt-1/Positive";
//static const std::string Folder_with_JPGs = "C:/Repositories/Samples_Segmentation/img";
//static const std::string Folder_with_JPGs = "C:/Repositories/CementCrack/SDNET2018/POSITIVE";


