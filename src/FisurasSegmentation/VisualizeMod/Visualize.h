//
// VisualizeMod
// Visualize
//

#pragma once
#include "pch.h"
#include "Config.h"

template <typename Net> 
class Visualize {
public:
    Visualize(const std::string& ADDRESS, Net& NET) {
        m_file_list = Get_file_from_directory(ADDRESS);

        for (auto _FILE : m_file_list) {
            auto RES = Process_entire_picture_with_NET(ADDRESS + "\\" + _FILE, NET);
            Show_pictures(RES);
            waitKey(0);
        }
    };

    at::Tensor Process_chunk_with_NET(const cv::Mat& PICTURE, Net& NET) {
        if (PICTURE.size() != Size2i(image_size, image_size)) exit(-1);

        // La imagen viene en 64x64 RGB, lo transformo a escala de grises.
        cv::Mat aux(PICTURE);
        cv::cvtColor(PICTURE, aux, cv::COLOR_BGR2GRAY);
        auto _IN = torch::from_blob(aux.data, { 1,1, image_size, image_size }, at::kByte);

        // ademas los valores de entrada de la Red Neuronal tiene que ser float en un rango <0,1>.
        return NET->forward(_IN.to(at::kFloat).div_(255));
    };
    
    std::pair<cv::Mat, cv::Mat> Process_entire_picture_with_NET(const std::string& FILENAME, Net& NET) {
        auto image = imread(FILENAME, 1 /* CV_LOAD_IMAGE_COLOR*/);

        // Tengo que escalar la imagen en multiplos del tamaño de la entrada de la RED.
        auto m_size_max_cols = (image.cols / image_size) * image_size;
        auto m_size_max_rows = (image.rows / image_size) * image_size;
        cv::resize(image, image, cv::Size(m_size_max_cols, m_size_max_rows));

        // Voy barriendo por cuadricula y aplicando la RED, luego lo rearmo en una mascara (mask).
        cv::Mat mask(m_size_max_rows, m_size_max_cols, CV_8UC1, cv::Scalar(0));
        for (size_t i = 0; i <= image.cols - image_size; i += image_size) {
            for (size_t j = 0; j <= image.rows - image_size; j += image_size) {
                Rect rect(i, j, image_size, image_size);
                auto result = Process_chunk_with_NET(image(rect), NET);

                // La RED devuelve un Tensor con floats, lo convierto a escala de grises para poder mostrar
                result = (result * 255).to(at::kByte);
                cv::Mat resultImg(image_size, image_size, CV_8UC1, (void*)result.data_ptr());
                resultImg.copyTo(mask(cv::Rect(i, j, image_size, image_size)));
            }
        }

        // Hago MAGIA para pintar en la imagen original el lugar donde la RED detecta Fisura.
        const uint32_t thresshold = 200; // se puede ajustar para la sensibilidad de la red..
        cv::threshold(mask, mask, thresshold, 255, THRESH_BINARY);
        cvtColor(mask, mask, cv::COLOR_GRAY2RGB);
        cv::Mat pink_color(m_size_max_rows, m_size_max_cols, CV_8UC3, cv::Scalar(205, 0, 0));
        mask.copyTo(pink_color, ~mask);
        mask = image + pink_color;

        return { image,mask };
    };
    
    std::vector<std::string> Get_file_from_directory(const std::string& ADDRESS) {
        std::vector<std::string> TYPES = { "png","jpg" };
        std::vector<std::string> FILELIST;
        HANDLE hFind;
        WIN32_FIND_DATA data;

        for (auto datatype : TYPES) {
            hFind = FindFirstFile(std::string(ADDRESS + "\\*." + datatype).c_str(), &data);
            if (hFind != INVALID_HANDLE_VALUE) {
                do {
                    FILELIST.push_back(data.cFileName);
                } while (FindNextFile(hFind, &data));
                FindClose(hFind);
            }
        }
        return FILELIST;
    };

    void Show_pictures(const std::pair<cv::Mat, cv::Mat>& RES) {
        const int MARGIN = 5;
        cv::Mat dst = cv::Mat(RES.first.rows, RES.first.cols * 2 + MARGIN, CV_8UC3, cv::Scalar(100, 100, 100));
        cv::Rect roi1(cv::Rect(0, 0, RES.first.cols, RES.first.rows));
        cv::Rect roi2(cv::Rect(0, 0, RES.second.cols, RES.second.rows));
        cv::Mat targetROI = dst(roi1);
        RES.first.copyTo(targetROI);
        targetROI = dst(cv::Rect(RES.first.cols + MARGIN, 0, RES.first.cols, RES.first.rows));
        RES.second.copyTo(targetROI);

        cv::resize(dst, dst, cv::Size(1024, 512));

        cv::namedWindow("Original/Mascara", WINDOW_AUTOSIZE);
        cv::imshow("Original/Mascara", dst);
    };

private:
    std::vector<std::string> m_file_list;
};