#include "pch.h"
#include "Dataset.h"
#include "cmdlineopt.h"

constexpr auto DSEP = "/";
#define IMG_FNAME(ROOT_FOLDER,PREFIX_FN) ROOT_FOLDER + DSEP + PREFIX_FN + "IMAGES.tensor"
#define TRG_FNAME(ROOT_FOLDER,PREFIX_FN) ROOT_FOLDER + DSEP + PREFIX_FN + "TARGET.tensor"
// ^-- Concernientes a la implementaci�n, no a la declaraci�n. No va en el .h


auto Dataset::get_file_or_directory_structure(
    const size_t& TYPE,
    const std::string& PATH,
    const std::string& EXT = "")
{
    WIN32_FIND_DATA data;
    HANDLE hFind = FindFirstFile(std::string(PATH + DSEP + "*." + EXT).c_str(), &data);

    std::vector<std::string> VEC;
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (data.dwFileAttributes == TYPE) 
                VEC.push_back(data.cFileName);
        } while (FindNextFile(hFind, &data));
    }

    FindClose(hFind);
    return VEC;
};

auto Dataset::get_image_from_directory(
    const std::string& PATH,
    const std::string& EXT, 
    const uint32_t& SIZE)
{
    std::vector<torch::Tensor> IMG;

    auto FILES = get_file_or_directory_structure(FILE_ATTRIBUTE_ARCHIVE, PATH, EXT);
    for (const auto& filename : FILES) {
        //---------------------------------------------------------------------
        // Pre-tratamiento de cada imagen con OpenCV.
        cv::Mat aux = cv::imread(PATH + DSEP + filename);
        std::vector<cv::Mat> rgb;
        cv::resize(aux, aux, cv::Size(SIZE, SIZE));
        cv::split(aux, rgb);
        //---------------------------------------------------------------------
        auto m_images = torch::zeros({ 3,SIZE,SIZE }, torch::kByte);
        m_images[0] = torch::from_blob(rgb[0].data, { SIZE, SIZE }, torch::kByte);
        m_images[1] = torch::from_blob(rgb[1].data, { SIZE, SIZE }, torch::kByte);
        m_images[2] = torch::from_blob(rgb[2].data, { SIZE, SIZE }, torch::kByte);

        IMG.push_back(m_images);
    }

    return torch::stack(torch::TensorList(IMG), 0);
};

Dataset::Pair Dataset::proccesing_data(
    const std::string& PATH,
    const std::string& EXT,
    const uint32_t& SIZE)
{
    std::vector<torch::Tensor> IMG;
    std::vector<torch::Tensor> TRG;

    if (CmdLineOpt::verbose) std::cout << "Procesando Estructura de: " << PATH << std::endl;
    auto DIR = get_file_or_directory_structure(FILE_ATTRIBUTE_DIRECTORY, PATH);
    assert(DIR.size() > 0);

    if (CmdLineOpt::verbose) std::cout << "Procesando Directorios." << std::endl;
    int count = 0;
    for (const auto& dirname : DIR) {
        if (dirname != "." && dirname != "..") {
            std::string STR = PATH + DSEP + dirname;
            if (CmdLineOpt::verbose) std::cout << STR << std::endl;
            IMG.push_back(get_image_from_directory(STR, "jpg",SIZE));
            TRG.push_back(torch::full({ IMG[count].size(0) }, count).to(at::kByte));
            count++;
        }
    };

    return { torch::cat(torch::TensorList(IMG)) ,torch::cat(torch::TensorList(TRG)) };
}

Dataset::Dataset(
    const std::string& ROOT_FOLDER,
    const std::string& PREFIX_FN,
    uint32_t IMAGE_SIZE)
{
    Dataset::Pair T = proccesing_data(ROOT_FOLDER, "jpg", IMAGE_SIZE);

    if (CmdLineOpt::verbose) std::cout << "Mezclando y Guardando." << std::endl;
    auto IDX = torch::randperm(T.first.size(0)).to(torch::kLong);

    if (CmdLineOpt::verbose) {
        std::cout << "Guardando IMAGE en.";
        std::cout << IMG_FNAME(ROOT_FOLDER, PREFIX_FN) << std::endl;
        std::cout << "Guardando TARGET en.";
        std::cout << TRG_FNAME(ROOT_FOLDER, PREFIX_FN) << std::endl;
    }

    torch::save(torch::index_select(T.first, 0, IDX), IMG_FNAME(ROOT_FOLDER, PREFIX_FN));
    torch::save(torch::index_select(T.second, 0, IDX), TRG_FNAME(ROOT_FOLDER, PREFIX_FN));
}