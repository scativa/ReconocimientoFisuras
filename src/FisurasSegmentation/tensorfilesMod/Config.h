//
// Tensorfiles
// Config
//

#pragma once
#include "pch.h"

//--------------------------------------------------------------------------------------------------
// la RED tendra una entrada de image_size*image_size con 8bit por pixel.(escala de grises)
constexpr size_t image_size = 96; 

//--------------------------------------------------------------------------------------------------
// CONSTANTES PARA LA CLASE DATASET
//--------------------------------------------------------------------------------------------------
// constexpr size_t train_batch_size = 4;
// constexpr size_t test_batch_size  = 4;

//const float Percentage_of_pictures_used_to_train = 0.85f;
//float Percentage_of_pictures_used_to_train = 0.85f;

const std::vector<std::string> classes = { "CRACK" };// directorio de donde levanta el DATASET.
const torch::DeviceType running_into = torch::cuda::is_available() ? torch::kCUDA : torch::kCPU;

// En este directorio es donde crea la estructura de archivos que posteriormente voy a levantar con el DATASET
//static const std::string Folder_with_Processed_pictures = "C:/Users/User/Proyectos/data/Segmentation";
//static std::string Folder_with_Processed_pictures = "C:/Users/User/Proyectos/data/Segmentation";
//std::string Folder_with_Processed_pictures = "C:/Users/User/Proyectos/data/Segmentation";
//Folder_with_Processed_pictures
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


