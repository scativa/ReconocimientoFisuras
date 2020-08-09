#include "pch.h"
#include "Cement.h"
#include <windows.h>

#include "../common/globals.h"

/*
#if defined(_WIN16) | defined(_WIN32) | defined(_WIN64)
#define SEPERATOR "\\"
#else
#define SEPERATOR "/"
#endif
*/

using namespace std;

constexpr auto DSEP = "/";

#define IMG_FNAME(ROOT_FOLDER,PREFIX_FN,MODE) ROOT_FOLDER + DSEP + PREFIX_FN + str_mode[(int) MODE] + "IMAGES.tensor"
#define TRG_FNAME(ROOT_FOLDER,PREFIX_FN,MODE) ROOT_FOLDER + DSEP + PREFIX_FN + str_mode[(int) MODE] + "TARGET.tensor"

namespace torch {
    namespace data {
        namespace datasets {
            enum type { POSITIVE=0, NEGATIVE=1 };
            enum mode { TRAIN=0, TEST=1};
            string str_type[] = { "Positive", "Negative" };
            string str_mode[] = { "TRAIN_", "TEST_" };

            // float Percentage_of_pictures_used_to_train = 0.015f;
            uint32_t Image_rows_to_resize_picture = 0; //64
            uint32_t Image_column_to_resize_picture = 0; //64
            uint32_t Number_of_pictures_that_use_to_train;
            uint32_t Number_of_pictures_that_use_to_test;
            uint32_t TrainImageSize;

            Device device = (torch::cuda::is_available() ? torch::kCUDA : torch::kCPU);


            auto Get_file_list_from_directory(const string& PATH) {
                vector<string> VEC;
                HANDLE hFind;
                WIN32_FIND_DATA data;

                hFind = FindFirstFile(string(PATH + "*.jpg").c_str(), &data);
                if (hFind != INVALID_HANDLE_VALUE) {
                    do {
                        VEC.push_back(data.cFileName);
                    } while (FindNextFile(hFind, &data));
                    FindClose(hFind);
                }
                return VEC;
            };

            pair<Tensor, Tensor> ShuffleTensors(at::Tensor& IMAGES, at::Tensor& TARGETS) {
                auto MIXED_IMAGES = torch::zeros({ IMAGES.sizes() }, device).to(torch::kByte);
                auto MIXED_TARGETS = torch::zeros({ TARGETS.sizes() }, device).to(torch::kByte);

                auto IDX = torch::randperm(IMAGES.size(0), device).to(at::kInt);

                for (uint idx = 0; idx < IDX.size(0); idx++) {
                    MIXED_IMAGES[idx] = IMAGES[IDX[idx]];
                    MIXED_TARGETS[idx] = TARGETS[IDX[idx]];
                };

                return pair<Tensor, Tensor>(MIXED_IMAGES, MIXED_TARGETS);
            };

            pair<Tensor, Tensor> PreProccesingData(const string& ROOT_FOLDER, const type& TYPE) {
                string m_path = DSEP + string(str_type[(int)TYPE]) + DSEP;

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
                        vector<cv::Mat> rgb;
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
                return pair<Tensor, Tensor>(m_images, m_target);
            };
                        
            void Create_tensor_files_from_images(const string& ROOT_FOLDER, const string& PREFIX_FN, 
                float Percentage_of_pictures_used_to_train, pair<uint32_t, uint32_t> resizerc, bool overwrite) {

                Image_rows_to_resize_picture = resizerc.first; //64
                Image_column_to_resize_picture = resizerc.second; //64
                assert(Image_rows_to_resize_picture > 0); 
                assert(Image_column_to_resize_picture > 0);

                if (globals::verbose_mode)
                    cout << "Create tensor files from images:" << endl <<
                    ROOT_FOLDER << endl <<
                    "Prefijo: " << PREFIX_FN << endl <<
                    "Percent to train: " << Percentage_of_pictures_used_to_train << endl <<
                    "Resize to: (" << Image_rows_to_resize_picture << "," << Image_column_to_resize_picture << ")" << endl <<
                    "Overrite" << endl << endl;

                ifstream file;
                
                file.open((IMG_FNAME(ROOT_FOLDER, PREFIX_FN, mode::TRAIN)).c_str(), ios::binary);
                
                if ((!file) || overwrite) {
                    cout << "Creando Base de Imagenes y Tensores..." << endl;

                    if (globals::verbose_mode) cout << "Prepoccesing NEGATIVE" << endl << ROOT_FOLDER << endl;
                    auto m_tensor_negative = PreProccesingData(ROOT_FOLDER, type::NEGATIVE);
                    if (globals::verbose_mode) cout << "Prepoccesing POSITIVE" << endl << ROOT_FOLDER << endl;
                    auto m_tensor_positive = PreProccesingData(ROOT_FOLDER, type::POSITIVE);

                    auto m_tensor_imagen = torch::cat({ m_tensor_negative.first, m_tensor_positive.first }, 0);
                    auto m_tensor_target = torch::cat({ m_tensor_negative.second, m_tensor_positive.second }, 0);

                    pair<Tensor, Tensor> m_tensor_suffle = ShuffleTensors(m_tensor_imagen, m_tensor_target);

                    Number_of_pictures_that_use_to_train = (uint32_t)(m_tensor_imagen.size(0) * Percentage_of_pictures_used_to_train);
                    Number_of_pictures_that_use_to_test = (uint32_t)(m_tensor_imagen.size(0) - Number_of_pictures_that_use_to_train);

                    vector<at::Tensor> m_vec_imagen = m_tensor_suffle.first.split(Number_of_pictures_that_use_to_train);
                    vector<at::Tensor> m_vec_target = m_tensor_suffle.second.split(Number_of_pictures_that_use_to_train);
                    /// Si Number_of_pictures_that_use_to_train < Number_of_pictures_that_use_to_test el tensor de test igual
                    /// al de entrenamiento, descartando el resto de las im�genes
                    /// https://pytorch.org/docs/stable/torch.html#torch.split

                    torch::save(m_vec_imagen[0].to(torch::kFloat32).div_(255),
                        IMG_FNAME(ROOT_FOLDER, PREFIX_FN, mode::TRAIN));
                    torch::save(m_vec_target[0].to(torch::kInt64), 
                        TRG_FNAME(ROOT_FOLDER, PREFIX_FN, mode::TRAIN));
                    torch::save(m_vec_imagen[1].to(torch::kFloat32).div_(255), 
                        IMG_FNAME(ROOT_FOLDER, PREFIX_FN, mode::TEST));
                    torch::save(m_vec_target[1].to(torch::kInt64), 
                        TRG_FNAME(ROOT_FOLDER, PREFIX_FN, mode::TEST));

                    // torch::save(m_tensor_suffle.first.to(torch::kFloat32).div_(255), ROOT_FOLDER + "\\TEST_IMAGES_ALL.tensor");
                    // torch::save(m_tensor_suffle.second.to(torch::kInt64), ROOT_FOLDER + "\\TEST_TARGET_ALL.tensor");

                    file.close();

                    cout << "Train: " << Number_of_pictures_that_use_to_train << "/" << m_tensor_imagen.size(0) << endl;
                    cout << "Test:  " << Number_of_pictures_that_use_to_test << "/" << m_tensor_imagen.size(0) << endl;
                }
                else if (globals::verbose_mode) cout << "Base de Imagenes y Tensores ya creadas previamente." << endl;
             };
            
            Cement::Cement(const string& ROOT_FOLDER, const string& PREFIX_FN, const Mode& MODE) {

                if (globals::verbose_mode) cout << "Cement " << str_mode[(int)MODE] << endl;
                
                if (globals::verbose_mode)
                    cout << "Cement " << str_mode[(int)MODE] << endl <<
                    ROOT_FOLDER << endl <<
                    "Prefijo: " << PREFIX_FN << endl << endl;

                string images_fn = IMG_FNAME(ROOT_FOLDER, PREFIX_FN, MODE);
                string targets_fn = TRG_FNAME(ROOT_FOLDER, PREFIX_FN, MODE);

                cout << "Cargando " << images_fn << " ...";
                torch::load(images_, images_fn);
                cout << "Listo!" << endl;
                cout << "Cargando " << targets_fn << " ...";
                torch::load(targets_, targets_fn);
                cout << "Listo!" << endl;

                if (device.is_cuda()) {
                    images_ = images_.to(device);
                    targets_ = targets_.to(device);
                }
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

