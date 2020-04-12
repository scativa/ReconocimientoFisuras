#pragma once
#include "pch.h"
#include "C:\Proyectos\Fisuras\CVNet_Cement\Net.h"
#include <windows.h>

using namespace std;
using namespace cv;

//string Folder_with_JPGs = "C:\\Repositories\\CementCrack\\5y9wdsg2zt-1\\Positive";
string Folder_with_JPGs = "C:\\Repositories\\CementCrack\\SDNET2018\\POSITIVE";
 // tamano en pixel que toma la RED a la entrada 64x64 pixels
#define CUADSIZE 64

auto Get_file_list_from_directory(const string& PATH) {
    std::vector<std::string> VEC;
    HANDLE hFind;
    WIN32_FIND_DATA data;

    hFind = FindFirstFile(string( PATH + "\\*.jpg").c_str(), &data);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            VEC.push_back(data.cFileName);
        } while (FindNextFile(hFind, &data));
        FindClose(hFind);
    }
    return VEC;
};

bool Has_a_fracture(const Mat& PICTURE, Net NET) {
    if (PICTURE.size() != Size2i(CUADSIZE, CUADSIZE)) exit(-1);

    //------------------------------------------------------------------------------------------------
    // La imagen viene en 64x64 RGB, cada pixel es de 8bit, tengo que separar los canales para que la 
    // entrada en la RED sea 1x3x64x64, ademas los valores tienen que ser float en un rango <0,1>.
    std::vector<cv::Mat> rgb;
    cv::split(PICTURE, rgb);

    auto m_images = torch::zeros({ 1 ,3 , CUADSIZE, CUADSIZE }).to(at::kByte);
    m_images[0][0] = torch::from_blob(rgb[0].data, { CUADSIZE, CUADSIZE }, at::kByte);
    m_images[0][1] = torch::from_blob(rgb[1].data, { CUADSIZE, CUADSIZE }, at::kByte);
    m_images[0][2] = torch::from_blob(rgb[2].data, { CUADSIZE, CUADSIZE }, at::kByte);
    //------------------------------------------------------------------------------------------------
    auto prediction = NET->forward(m_images.to(at::kFloat).div_(255));
    return (prediction[0][1].item<float>() > prediction[0][0].item<float>());
};

std::pair<Mat, Mat> Process_picture_with_NET(const string& FILENAME, Net NET) {

    auto image = imread(FILENAME, 1 /* CV_LOAD_IMAGE_COLOR*/);
    if (!image.data) {
        cout << "Could not open or find the image " << std::endl;
        exit(-1);
    }
    //------------------------------------------------------------------------------------------------
    // Tengo que escalar la imagen, para que pueda barrerla con la Red, sin dejar algun espacio afuera.
    //------------------------------------------------------------------------------------------------
    auto m_size_max_cols = (image.cols / CUADSIZE) * CUADSIZE;
    auto m_size_max_rows = (image.rows / CUADSIZE) * CUADSIZE;
    cv::resize(image, image, cv::Size(m_size_max_cols, m_size_max_rows));

    auto mask = image.clone();
     //------------------------------------------------------------------------------------------------
    for (size_t i = 0; i <= image.cols - CUADSIZE; i += CUADSIZE) {
        for (size_t j = 0; j <= image.rows - CUADSIZE; j += CUADSIZE) {
            Rect m_rect(i, j, CUADSIZE, CUADSIZE); // Submatrix: https://stackoverflow.com/questions/27835439/opencv-submatrix-access-copy-or-reference
            if (Has_a_fracture(image(m_rect), NET))
            {
                Mat chunk(mask, m_rect);
                chunk = chunk * 0.5f;
            }
        }
    }

    return { image,mask };
};

void Show_pictures(const std::pair<Mat, Mat>& RES) {
    cv::Mat dst = cv::Mat(RES.first.rows, RES.first.cols * 2, CV_8UC3, cv::Scalar(0, 0, 0));
    cv::Rect roi1(cv::Rect(0, 0, RES.first.cols, RES.first.rows));
    cv::Rect roi2(cv::Rect(0, 0, RES.second.cols, RES.second.rows));
    cv::Mat targetROI = dst(roi1);
    RES.first.copyTo(targetROI);
    targetROI = dst(cv::Rect(RES.first.cols, 0, RES.first.cols, RES.first.rows));
    RES.second.copyTo(targetROI);

    cv::resize(dst, dst, cv::Size(1024, 512));

    cv::namedWindow("Original/Mascara", WINDOW_AUTOSIZE);
    cv::imshow("Original/Mascara", dst);
};

void Test_in_every_jpg_in_the_directory(const string& PATH, Net NET) {
    auto VEC = Get_file_list_from_directory(PATH);

    for (auto m_file : VEC) {
        auto RES = Process_picture_with_NET(Folder_with_JPGs + "\\" + m_file, NET);
        Show_pictures(RES);
        waitKey(0);
    }
}

int main()
{
    //------------------------------------------------------------------------------------------------
    Net net; // auto net = std::make_shared<NetImpl>();
    // es equivalente ya que uso el TORCH_MODULE(Net) para "envolver la definicion" y poder usar la
    // definicion como Net simplemente. explicado en profundidad MUY POCO claro en,
    // https://pytorch.org/tutorials/advanced/cpp_frontend.html
    //------------------------------------------------------------------------------------------------
    // Si existe un entrenamiento previo arranca desde ahi, sino empieza desde cero/
    try {
        torch::load(net, "C:\\Proyectos\\Fisuras\\CVNet_Cement\\model.pt");
        Test_in_every_jpg_in_the_directory(Folder_with_JPGs, net);
    }
    catch (...) {}
}
