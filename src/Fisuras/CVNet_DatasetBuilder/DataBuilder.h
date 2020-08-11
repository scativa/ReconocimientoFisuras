#pragma once
#include "pch.h"

using namespace std;

namespace torch {
    namespace data {
        namespace datasets {

            void Create_tensor_files_from_images(const std::string& ROOT_FOLDER, const std::string& PREFIX_FN,
                float Percentage_of_pictures_used_to_train, pair<uint32_t, uint32_t> resizerc, bool overwrite);
        } // namespace datasets
    } // namespace data
} // namespace torch
