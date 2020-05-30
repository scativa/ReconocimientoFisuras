#include "pch.h"
#include "CementTrainer.h"

#define _VERBOSE_MODE_

#define DSEP "/"

#define IMG_FNAME(ROOT_FOLDER,PREFIX_FN,MODE) ROOT_FOLDER + DSEP + PREFIX_FN + str_mode[(int) MODE] + "IMAGES.tensor"
#define TRG_FNAME(ROOT_FOLDER,PREFIX_FN,MODE) ROOT_FOLDER + DSEP + PREFIX_FN + str_mode[(int) MODE] + "TARGET.tensor"

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
                std::cout << "Cement::Cement()" << std::endl;
                string images_fn = IMG_FNAME(ROOT_FOLDER, PREFIX_FN, MODE);
                string targets_fn = TRG_FNAME(ROOT_FOLDER, PREFIX_FN, MODE);

                std::cout << "Cargando " << images_fn << " ...";
                torch::load(images_, images_fn);
                std::cout << "Listo!" << std::endl;
                std::cout << "Cargando " << targets_fn << " ...";
                torch::load(targets_, targets_fn);
                std::cout << "Listo!" << std::endl;

                images_.to(device);
                targets_.to(device);
            };

            Example<> Cement::get(size_t index) {
                return { images_[index], targets_[index] };
            }

            optional<size_t> Cement::size() const {
                std::cout << "Cement::size()" << std::endl;
                return images_.size(0);
            }

            bool Cement::is_train() const noexcept {
                std::cout << "Cement::is_train()" << std::endl;
                return images_.size(0) == TrainImageSize;
            }

            const Tensor& Cement::images() const {
                std::cout << "Cement::images()" << std::endl;
                return images_;
            }

            const Tensor& Cement::targets() const {
                std::cout << "Cement::targets()" << std::endl;
                return targets_;
            }

            const IntArrayRef Cement::sizes() const {
                std::cout << "Cement::sizes()" << std::endl;
                return images_.sizes();
            }

        } // namespace datasets
    } // namespace data
}// namespace torch
