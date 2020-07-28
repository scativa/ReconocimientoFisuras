// 
// TrainingMod
// Config
//

#pragma once
#include "pch.h"

// Comentar si solo quiero visualizar los resultados de un modelo previamente entranado
//#define TRAIN_NET true 

//--------------------------------------------------------------------------------------------------
// la RED tendra una entrada de image_size*image_size con 8bit por pixel.(escala de grises)
constexpr size_t image_size = 96; 

//--------------------------------------------------------------------------------------------------
// CONSTANTES PARA LA CLASE DATASET
//--------------------------------------------------------------------------------------------------
constexpr size_t train_batch_size = 4;
constexpr size_t test_batch_size  = 4;

const float Percentage_of_pictures_used_to_train = 0.85f;
//float Percentage_of_pictures_used_to_train = 0.85f;

const torch::DeviceType running_into = torch::cuda::is_available() ? torch::kCUDA : torch::kCPU;


//--------------------------------------------------------------------------------------------------
// Directorio donde estan los PNG y/o los JPG que quiero analizar.-----------------------------
static const std::string Folder_with_JPGs = "C:/Users/User/Proyectos/data/Positive";
//static const std::string Folder_with_JPGs = "C:\\Repositories\\CementCrack\\5y9wdsg2zt-1\\Positive";
//static const std::string Folder_with_JPGs = "C:\\Repositories\\Samples_Segmentation\\img";
//static const std::string Folder_with_JPGs = "C:\\Repositories\\CementCrack\\SDNET2018\\POSITIVE";


