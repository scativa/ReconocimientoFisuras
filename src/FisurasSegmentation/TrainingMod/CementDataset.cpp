// 
// TrainingMod
// CementDataset
//

#include "pch.h"
#include "CementDataset.h"
#include "../common/globals.h"


using namespace std;

constexpr auto DSEP = "/";

#define _FULLNAME(ROOT_FOLDER,FTYPE) ROOT_FOLDER + DSEP + tensor_prefix + FTYPE + ".tensor"
#define IMG_FULLNAME(ROOT_FOLDER) _FULLNAME(ROOT_FOLDER,"IMG")
#define MASK_FULLNAME(ROOT_FOLDER) _FULLNAME(ROOT_FOLDER,"MASK")

namespace torch {
    namespace data {
        namespace datasets {
            /*
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
            */

            auto  CementDataset::Load_tensors_from_disk(const std::string& PATH) {
                if ((images_.numel() == 0)) {
                    if (globals::verbose_mode) cout << "Load_tensors_from_disk  " << ((mode == Mode::Train) ? "Train" : "Test") << endl;
                    if (globals::verbose_mode) cout << IMG_FULLNAME(PATH) << endl << MASK_FULLNAME(PATH) << endl;
                    torch::load(images_, IMG_FULLNAME(PATH));
                    torch::load(targets_, MASK_FULLNAME(PATH));
                    cout << "Done!." << endl;
                }
              
                auto imagen_patition = images_.split(size_t(images_.size(0) * Percentage_of_pictures_used_to_train));
                auto mask_patition = targets_.split(size_t(targets_.size(0) * Percentage_of_pictures_used_to_train));

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

            CementDataset::CementDataset(const std::string& PATH, const Mode& MODE, const string& PREFIX_FN) : mode(MODE) {
                Load_tensors_from_disk(PATH);
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

