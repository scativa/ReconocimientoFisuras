#pragma once
#include "pch.h"

using namespace std;

namespace torch {
    namespace data {
        namespace datasets {

            ///
            void Create_tensor_files_from_images(const std::string& ROOT_FOLDER, const std::string& PREFIX_FN,
                float Percentage_of_pictures_used_to_train, pair<uint32_t, uint32_t> resizerc, bool overwrite);

            /// The CEMENT dataset.
            class Cement : public Dataset<Cement> {
            public:
                /// The mode in which the dataset is loaded.
                enum class Mode { Train, Test };

                explicit Cement(const string& ROOT_FOLDER, const string& PREFIX_FN, const Mode& MODE);

                /// Returns the `Example` at the given `index`.
                Example<> get(size_t index) override;

                /// Returns the size of the dataset.
                optional<size_t> size() const override;

                /// Returns true if this is the training subset.
                bool is_train() const noexcept;

                /// Returns all images stacked into a single tensor.
                const Tensor& images() const;

                /// Returns all targets stacked into a single tensor.
                const Tensor& targets() const;

                const IntArrayRef sizes() const;

            private:
                Tensor images_, targets_;
            };
        } // namespace datasets
    } // namespace data
} // namespace torch
