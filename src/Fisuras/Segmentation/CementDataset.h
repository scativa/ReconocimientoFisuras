#pragma once
#include "pch.h"
#include "Config.h"

    //. Estuctura de Archivos donde levanta las imagenes.
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

namespace torch {
    namespace data {
        namespace datasets {
            /// The CEMENT dataset.
            class CementDataset : public Dataset<CementDataset> {
            public:
                /// The mode in which the dataset is loaded.
                enum class Mode { Train, Test };

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

                explicit CementDataset(const std::string& ROOT_FOLDER, std::vector<std::string> CLASSES, const Mode&);
                auto Proccesing_data(const std::string& PATH, std::vector<std::string>);
                auto Get_file_list_from_directory(const std::string& PATH);
                auto Load_tensors_from_disk(const std::string& PATH, const Mode& MODE);
                void ShuffleTensors();

            private:
                Tensor images_, targets_;
                Mode mode;
            };
        } // namespace datasets
    } // namespace data
} // namespace torch

