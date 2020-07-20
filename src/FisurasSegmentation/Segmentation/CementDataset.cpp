#include "CementDataset.h"

namespace torch {
    namespace data {
        namespace datasets {

            auto CementDataset::Get_file_list_from_directory(const std::string& ADDRESS) {
            #ifdef WINDOWS_COMPILER_VERSION
                std::vector<std::string> TYPES = { "png","jpg" };
                std::vector<std::string> FILELIST;
                HANDLE hFind;
                WIN32_FIND_DATA data;

                for (auto datatype : TYPES) {
                    hFind = FindFirstFile(std::string(ADDRESS + "\\*." + datatype).c_str(), &data);
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
                    std::vector<std::string> PICTS = Get_file_list_from_directory(PATH + "\\" + dir + "\\img");

                    auto IMG  = torch::empty({ (uint32_t)PICTS.size() ,1 , image_size, image_size }, running_into).to(torch::kByte);
                    auto MASK = torch::empty({ (uint32_t)PICTS.size() ,1 , image_size, image_size }, running_into).to(torch::kByte);
                    size_t count = 0;
                    for (auto pict : PICTS) {
                        IMG[count][0] = torch::from_blob(cv::imread(PATH + "\\" + dir + "\\img\\" + pict, 0).data, { image_size, image_size }, torch::kByte);

                        auto A = cv::imread(PATH + "\\" + dir + "\\mask\\" + pict, 0);// .data, { image_size, image_size };
                        cv::Mat B;
                        cv::threshold(A, B, 70, 255, cv::THRESH_BINARY_INV);

                        MASK[count][0] = torch::from_blob(B.data, { image_size, image_size }, torch::kByte);
                        count++;
                    }
                    
                    images_ = (images_.numel() == 0) ? IMG : torch::cat({ images_, IMG }, 0);
                    targets_ = (targets_.numel() == 0) ? MASK : torch::cat({ targets_, MASK }, 0);
                }
                
                ShuffleTensors();
                torch::save(images_, PATH + "\\IMG.tensor");
                torch::save(targets_, PATH + "\\MASK.tensor");
            };

            auto  CementDataset::Load_tensors_from_disk(const std::string& PATH, const Mode& MODE) {
                if ((images_.numel() == 0)) {
                    std::cout << "Load_tensors_from_disk... " << std::endl;
                    torch::load(images_, PATH + "\\IMG.tensor");
                    torch::load(targets_, PATH + "\\MASK.tensor");
                    std::cout << "Done!." << std::endl;
                }
              
                int images_size = images_.size(0);
                int targets_size = targets_.size(0);

                auto imagen_patition = images_.split(size_t(images_size * Percentage_of_pictures_used_to_train));
                auto mask_patition = targets_.split(size_t(targets_size * Percentage_of_pictures_used_to_train));
//                auto imagen_patition = images_.split(size_t(images_.size(0) * Percentage_of_pictures_used_to_train));
//                auto mask_patition = targets_.split(size_t(targets_.size(0) * Percentage_of_pictures_used_to_train));

                switch (mode) {
                case Mode::Train:
                    images_ = imagen_patition[0];
                    targets_ = mask_patition[0];
                    break;
                case Mode::Test:
                    images_ = imagen_patition[1];
                    targets_ = mask_patition[1];
                    break;
                };
            };

            CementDataset::CementDataset(const std::string& PATH, std::vector<std::string> CLASSES, const Mode& MODE) : mode(MODE)
            {
                // Verifico que esten creados los tensores con las imagenes. si no lo estan los crea a partir del PATH
                std::ifstream file;
                file.open((PATH + "\\IMG.tensor").c_str(), std::ios::binary);
                if (!file) Proccesing_data(PATH, CLASSES);
                file.close();

                Load_tensors_from_disk(PATH, MODE);
            };

            Example<> CementDataset::get(size_t index) {
                return { images_[index], targets_[index] };
            }

            optional<size_t> CementDataset::size() const {
                return images_.size(0);
            }

            bool CementDataset::is_train() const noexcept {
                return (Mode::Train == mode);
            }

            const Tensor& CementDataset::images() const {
                return images_;
            }

            const Tensor& CementDataset::targets() const {
                return targets_;
            }

        } // namespace datasets
    } // namespace data
}// namespace torch

