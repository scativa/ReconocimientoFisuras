#include "pch.h"

auto MODEL = torch::nn::Sequential(
    // Layer 1
    torch::nn::Conv2d(torch::nn::Conv2dOptions(1 /*channel_in */, 32 /*channel_out */, 3 /*kernel_size=*/)),
    //torch::nn::BatchNorm2d(32),
    torch::nn::MaxPool2d(2),
    torch::nn::Functional(torch::relu),
    // Layer 2
    torch::nn::Conv2d(torch::nn::Conv2dOptions(32, 32, 3)),
    //torch::nn::BatchNorm2d(32),
    torch::nn::MaxPool2d(2),
    torch::nn::Functional(torch::relu),
    // Layer 3
    torch::nn::Conv2d(torch::nn::Conv2dOptions(32, 32, 3)),
    //torch::nn::BatchNorm2d(32),
    torch::nn::MaxPool2d(2),
    torch::nn::Functional(torch::relu),
    // Layer 4
    torch::nn::Flatten(),
    torch::nn::Linear(torch::nn::LinearOptions(1152, 100)),
    torch::nn::Functional(torch::relu),
    // Layer 6
    torch::nn::Linear(torch::nn::LinearOptions(100, 1)),
    torch::nn::LogSoftmax(1)
);
