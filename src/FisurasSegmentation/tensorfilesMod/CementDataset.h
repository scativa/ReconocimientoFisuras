//
// Tensorfiles
// CementDataset
//

#pragma once
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

                /// Returns the `Example` at the given `index`.
                Example<> get(size_t index) override;

                /// Returns the size of the dataset.
                optional<size_t> size() const override;

                explicit CementDataset(const std::string& ROOT_FOLDER, std::vector<std::string> CLASSES, const string& PREFIX_FN = "");

            private:
                auto Proccesing_data(const std::string& PATH, std::vector<std::string>);
                auto Get_file_list_from_directory(const std::string& PATH);
                void ShuffleTensors();

            private:
                Tensor images_, targets_;
                string tensor_prefix;
            };
        } // namespace datasets
    } // namespace data
} // namespace torch

