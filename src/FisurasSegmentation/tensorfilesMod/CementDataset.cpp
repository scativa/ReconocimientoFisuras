//
// Tensorfiles
// CementDataset
//

#include "pch.h"
#include "CementDataset.h"

using namespace std;

constexpr auto DSEP = "/";

#define _FULLNAME(ROOT_FOLDER,FTYPE) ROOT_FOLDER + DSEP + tensor_prefix + FTYPE + ".tensor"
#define IMG_FULLNAME(ROOT_FOLDER) _FULLNAME(ROOT_FOLDER,"IMG")
#define MASK_FULLNAME(ROOT_FOLDER) _FULLNAME(ROOT_FOLDER,"MASK")

namespace torch {
    namespace data {
        namespace datasets {

            auto CementDataset::Get_file_list_from_directory(const std::string& ADDRESS) {
            #ifdef _WIN64
                std::vector<std::string> TYPES = { "png","jpg" };
                std::vector<std::string> FILELIST;
                HANDLE hFind;
                WIN32_FIND_DATA data;

                for (auto datatype : TYPES) {
                    hFind = FindFirstFile(std::string(ADDRESS + DSEP + "*." + datatype).c_str(), &data);
                    if (hFind != INVALID_HANDLE_VALUE) {
                        do {
                            FILELIST.push_back(data.cFileName);
                        } while (FindNextFile(hFind, &data));
                        FindClose(hFind);
                    }
                }
                return FILELIST;
            #endif // _WIN64

            #ifndef _WIN64
                std::cout << "Falta version de la funcion equivalente para LINUX." << std::endl;
                std::cout << "auto CementDataset::Get_file_list_from_directory(const std::string& ADDRESS)" << std::endl;
                exit(-1);
            #endif
            };

            void CementDataset::ShuffleTensors() {
                auto IDX = torch::randperm(images_.size(0)).to(at::kInt);

                for (uint idx = 0; idx < IDX.size(0); idx++) {
                    auto aux = images_[idx].clone();
                    images_[idx] = images_[IDX[idx]];
                    images_[IDX[idx]] = aux;
                };
                for (uint idx = 0; idx < IDX.size(0); idx++) {
                    auto aux = targets_[idx].clone();
                    targets_[idx] = targets_[IDX[idx]];
                    targets_[IDX[idx]] = aux;
                };
            };
            
            auto  CementDataset::Proccesing_data(const std::string& PATH, std::vector<std::string> DIRECTORY) {
                for (auto dir : DIRECTORY) {
                    std::vector<std::string> PICTS = Get_file_list_from_directory(PATH + DSEP + dir + DSEP + "img");

                    auto IMG  = torch::empty({ (uint32_t)PICTS.size() ,1 , image_size, image_size }, running_into).to(torch::kByte);
                    auto MASK = torch::empty({ (uint32_t)PICTS.size() ,1 , image_size, image_size }, running_into).to(torch::kByte);
                    size_t count = 0;
                    for (auto pict : PICTS) {
                        IMG[count][0] = torch::from_blob(cv::imread(PATH + DSEP + dir + DSEP + "img" + DSEP + pict, 0).data, { image_size, image_size }, torch::kByte);

                        auto A = cv::imread(PATH + DSEP + dir + DSEP + "mask" + DSEP + pict, 0);// .data, { image_size, image_size };
                        cv::Mat B;
                        cv::threshold(A, B, 70, 255, cv::THRESH_BINARY_INV);

                        MASK[count][0] = torch::from_blob(B.data, { image_size, image_size }, torch::kByte);
                        count++;
                    }
                    
                    images_ = (images_.numel() == 0) ? IMG : torch::cat({ images_, IMG }, 0);
                    targets_ = (targets_.numel() == 0) ? MASK : torch::cat({ targets_, MASK }, 0);
                }
                
                ShuffleTensors(); // Pasar el suffle luego de cargar (o también) los .tensor antes de entrenar
                
                torch::save(images_, IMG_FULLNAME(PATH));
                torch::save(targets_, MASK_FULLNAME(PATH));
            };

            //CementDataset::CementDataset(const std::string& PATH, std::vector<std::string> CLASSES, const Mode& MODE) : mode(MODE)
            CementDataset::CementDataset(const std::string& PATH, std::vector<std::string> CLASSES, const string& PREFIX_FN) : 
                tensor_prefix(PREFIX_FN)
            {
                // Verifico que esten creados los tensores con las imagenes. si no lo estan los crea a partir del PATH
                std::ifstream file;
                file.open((IMG_FULLNAME(PATH)).c_str(), std::ios::binary);
                if (file) {
                    cout << "Sobreescribiendo archivos:" << endl;
                    file.close();
                }
                else {
                    std::cout << "Archivos inexistendes. Creando:" << endl;

                }
                cout << IMG_FULLNAME(PATH) << endl;
                cout << MASK_FULLNAME(PATH) << endl;

                Proccesing_data(PATH, CLASSES);

                // Load_tensors_from_disk(PATH, MODE);
            };

            Example<> CementDataset::get(size_t index) {
                return { images_[index], targets_[index] };
            }

            optional<size_t> CementDataset::size() const {
                return images_.size(0);
            }

        } // namespace datasets
    } // namespace data
}// namespace torch

