#include "Cement.h"
#include <windows.h>

namespace torch {
    namespace data {
        namespace datasets {
            enum type { POSITIVE, NEGATIVE };
            const float Percentage_of_pictures_used_to_train = 0.75f;
            uint32_t Image_rows_to_resize_picture = 64;
            uint32_t Image_column_to_resize_picture = 64;
            uint32_t Number_of_pictures_that_use_to_train;
            uint32_t Number_of_pictures_that_use_to_test;
            uint32_t TrainImageSize;

            Device device = (torch::cuda::is_available() ? torch::kCUDA : torch::kCPU);


            auto Get_file_list_from_directory(const std::string& PATH) {
                std::vector<std::string> VEC;
                HANDLE hFind;
                WIN32_FIND_DATA data;

                hFind = FindFirstFile(std::string(PATH + "*.jpg").c_str(), &data);
                if (hFind != INVALID_HANDLE_VALUE) {
                    do {
                        VEC.push_back(data.cFileName);
                    } while (FindNextFile(hFind, &data));
                    FindClose(hFind);
                }
                return VEC;
            };

            std::pair<Tensor, Tensor> ShuffleTensors(at::Tensor& IMAGES, at::Tensor& TARGETS) {
                auto MIXED_IMAGES = torch::zeros({ IMAGES.sizes() }, device).to(torch::kByte);
                auto MIXED_TARGETS = torch::zeros({ TARGETS.sizes() }, device).to(torch::kByte);

                auto IDX = torch::randperm(IMAGES.size(0), device).to(at::kInt);

                for (uint idx = 0; idx < IDX.size(0); idx++) {
                    MIXED_IMAGES[idx] = IMAGES[IDX[idx]];
                    MIXED_TARGETS[idx] = TARGETS[IDX[idx]];
                };

                return std::pair<Tensor, Tensor>(MIXED_IMAGES, MIXED_TARGETS);
            };

            std::pair<Tensor, Tensor> PreProccesingData(const std::string& ROOT_FOLDER, const type& TYPE) {
                string m_path = (TYPE == type::POSITIVE) ? "\\Positive\\" : "\\Negative\\";
                auto m_files_vec = Get_file_list_from_directory(ROOT_FOLDER + m_path);
                if (m_files_vec.size() == 0) exit(-1);

                uint32_t m_size = m_files_vec.size();

                auto m_images = torch::zeros({ m_size ,3 , Image_rows_to_resize_picture, Image_column_to_resize_picture }, device).to(torch::kByte);
                auto m_target = torch::full({ m_size }, (TYPE == type::NEGATIVE) ? 0 : 1, device).to(torch::kByte);

                uint32_t count = 0;
                for (auto files : m_files_vec) {
                    cv::Mat aux;
                    aux = cv::imread(ROOT_FOLDER + m_path + files, 1);

                    if (aux.data) {
                        std::vector<cv::Mat> rgb;
                        //----------------------------------------------------------------------------------
                        // Pre tratamiento de cada imagen, aca se podrian agregar filtros si son necesarios.
                        cv::resize(aux, aux, cv::Size(Image_column_to_resize_picture, Image_rows_to_resize_picture));
                        cv::split(aux, rgb);
                        //----------------------------------------------------------------------------------
                        m_images[count][0] = torch::from_blob(rgb[0].data, { Image_rows_to_resize_picture, Image_column_to_resize_picture }, torch::kByte);
                        m_images[count][1] = torch::from_blob(rgb[1].data, { Image_rows_to_resize_picture, Image_column_to_resize_picture }, torch::kByte);
                        m_images[count][2] = torch::from_blob(rgb[2].data, { Image_rows_to_resize_picture, Image_column_to_resize_picture }, torch::kByte);
                        count++;
                    }
                }
                return std::pair<Tensor, Tensor>(m_images, m_target);
            };

            Cement::Cement(const std::string& ROOT_FOLDER, const Mode& MODE) {
                string m_type = (MODE == Mode::Train) ? "TRAIN_" : "TEST_";

                std::ifstream file;
                file.open((ROOT_FOLDER + "\\" + m_type + "IMAGES.tensor").c_str(), std::ios::binary);
                if (!file) {
                    std::cout << "Creando Base de Imagenes y Tensores..." << std::endl;

                    auto m_tensor_negative = PreProccesingData(ROOT_FOLDER, type::NEGATIVE);
                    auto m_tensor_positive = PreProccesingData(ROOT_FOLDER, type::POSITIVE);

                    auto m_tensor_imagen = torch::cat({ m_tensor_negative.first, m_tensor_positive.first }, 0);
                    auto m_tensor_target = torch::cat({ m_tensor_negative.second, m_tensor_positive.second }, 0);

                    std::pair<Tensor, Tensor> m_tensor_suffle = ShuffleTensors(m_tensor_imagen, m_tensor_target);

                    Number_of_pictures_that_use_to_train = (uint32_t)(m_tensor_imagen.size(0) * Percentage_of_pictures_used_to_train);
                    Number_of_pictures_that_use_to_test  = (uint32_t)(m_tensor_imagen.size(0) - Number_of_pictures_that_use_to_train);

                    std::vector<at::Tensor> m_vec_imagen = m_tensor_suffle.first.split(Number_of_pictures_that_use_to_train);
                    std::vector<at::Tensor> m_vec_target = m_tensor_suffle.second.split(Number_of_pictures_that_use_to_train);

                    torch::save(m_vec_imagen[0].to(torch::kFloat32).div_(255), ROOT_FOLDER + "\\TRAIN_IMAGES.tensor");
                    torch::save(m_vec_target[0].to(torch::kInt64), ROOT_FOLDER + "\\TRAIN_TARGET.tensor");
                    torch::save(m_vec_imagen[1].to(torch::kFloat32).div_(255), ROOT_FOLDER + "\\TEST_IMAGES.tensor");
                    torch::save(m_vec_target[1].to(torch::kInt64), ROOT_FOLDER + "\\TEST_TARGET.tensor");

                    file.close();
                }

                switch (MODE) {
                case Mode::Train:
                    std::cout << "Cargando Imagenes para entrenamiento." << std::endl;                 
                    torch::load(images_, ROOT_FOLDER + "\\TRAIN_IMAGES.tensor");
                    torch::load(targets_, ROOT_FOLDER + "\\TRAIN_TARGET.tensor");
                    std::cout << "Listo!." << std::endl;
                    break;
                case Mode::Test:
                    std::cout << "Cargando Imagenes para testeo." << std::endl;
                    torch::load(images_, ROOT_FOLDER + "\\TEST_IMAGES.tensor");
                    torch::load(targets_, ROOT_FOLDER + "\\TEST_TARGET.tensor");
                    std::cout << "Listo!." << std::endl;
                    break;
                };

                images_.to(device);
                targets_.to(device);
            };

            Example<> Cement::get(size_t index) {
                return { images_[index], targets_[index] };
            }

            optional<size_t> Cement::size() const {
                return images_.size(0);
            }

            bool Cement::is_train() const noexcept {
                return images_.size(0) == TrainImageSize;
            }

            const Tensor& Cement::images() const {
                return images_;
            }

            const Tensor& Cement::targets() const {
                return targets_;
            }

            const IntArrayRef Cement::sizes() const {
                return images_.sizes();
            }

        } // namespace datasets
    } // namespace data
}// namespace torch

