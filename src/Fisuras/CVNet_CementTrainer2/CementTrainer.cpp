#include "pch.h"
#include "CementTrainer.h"

#include "../common/globals.h"
#include "Tensor_utils.h"

using namespace std;

constexpr auto DSEP = "/";

#define _FULLNAME(ROOT_FOLDER,PREFIX_FN,MODE,FTYPE) ROOT_FOLDER + DSEP + PREFIX_FN + str_mode[(int) MODE] + FTYPE + ".tensor"
#define IMG_FNAME(ROOT_FOLDER,PREFIX_FN,MODE) _FULLNAME (ROOT_FOLDER,PREFIX_FN,MODE,"IMAGES")
#define TRG_FNAME(ROOT_FOLDER,PREFIX_FN,MODE) _FULLNAME (ROOT_FOLDER,PREFIX_FN,MODE,"TARGET")

namespace torch {
    namespace data {
        namespace datasets {
            enum type { POSITIVE = 0, NEGATIVE = 1 };
            enum mode { TRAIN = 0, TEST = 1 };
            std::string str_type[] = { "Positive", "Negative" };
            std::string str_mode[] = { "TRAIN_", "TEST_" };

            // float Percentage_of_pictures_used_to_train = 0.015f;
            uint32_t Image_rows_to_resize_picture = 64;
            uint32_t Image_column_to_resize_picture = 64;
            uint32_t Number_of_pictures_that_use_to_train;
            uint32_t Number_of_pictures_that_use_to_test;
            uint32_t TrainImageSize;

            Device device = (torch::cuda::is_available() ? torch::kCUDA : torch::kCPU);


            std::pair<Tensor, Tensor> ShuffleTensors(at::Tensor& IMAGES, at::Tensor& TARGETS) {
                std::cout << "Cement::ShuffleTensors()" << std::endl;
                auto MIXED_IMAGES = torch::zeros({ IMAGES.sizes() }, device).to(torch::kByte);
                auto MIXED_TARGETS = torch::zeros({ TARGETS.sizes() }, device).to(torch::kByte);

                auto IDX = torch::randperm(IMAGES.size(0), device).to(at::kInt);

                for (unsigned int idx = 0; idx < IDX.size(0); idx++) {
                    MIXED_IMAGES[idx] = IMAGES[IDX[idx]];
                    MIXED_TARGETS[idx] = TARGETS[IDX[idx]];
                };

                return std::pair<Tensor, Tensor>(MIXED_IMAGES, MIXED_TARGETS);
            };

            Cement::Cement(const std::string& ROOT_FOLDER, const std::string& PREFIX_FN, const Mode& MODE) {
                if (globals::verbose_mode) cout << endl << "Cement::Cement()" << endl;
                string images_fn = IMG_FNAME(ROOT_FOLDER, PREFIX_FN, MODE);
                string targets_fn = TRG_FNAME(ROOT_FOLDER, PREFIX_FN, MODE);

                try {
                    if (globals::verbose_mode) cout << "Cargando " << images_fn << " ...";
                    torch::load(images_, images_fn);
                    if (globals::verbose_mode) cout << "Listo!" << endl;
                    if (globals::verbose_mode) cout << "Cargando " << targets_fn << " ...";
                    torch::load(targets_, targets_fn);
                    if (globals::verbose_mode) cout << "Listo!" << endl;
                }
                catch (const std::exception& e) {
                    cerr << endl << e.what() << endl
                        << "Error al cargar archivos:" << endl
                        << "Path: " << ROOT_FOLDER << endl
                        << "Prefix:" << PREFIX_FN << endl;
                    throw(e);
                }

                if (globals::verbose_mode) {
                    cout << endl << "images_.to pre: " << endl;
                    print_opt(images_);
                    cout << "targets_.to pre: " << endl;
                    print_opt(targets_);
                }

                images_ = images_.to(device);
                targets_ = targets_.to(device);

                if (globals::verbose_mode) {
                    cout << "images_.to post images_ = images_.to(device); : " << endl;
                    print_opt(images_);
                    cout << "targets_.to post targets_ = targets_.to(device); : " << endl;
                    print_opt(targets_);
                }

                // cout << images_.device()
                if (globals::verbose_mode) cout << endl;
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
