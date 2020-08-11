#pragma once
#include "pch.h"

const uint32_t m_batch_size = 32;

struct NetImpl : torch::nn::Module {
    NetImpl() :
        conv1(torch::nn::Conv2dOptions(3, 32, /*kernel_size=*/3)),
        conv2(torch::nn::Conv2dOptions(32, 32, /*kernel_size=*/3)),
        conv3(torch::nn::Conv2dOptions(32, 32, /*kernel_size=*/3)),
        fc1(1152, 100),
        fc2(100, 2) {

        // register_module() is needed if we want to use the parameters() method later on
        register_module("conv1", conv1);
        register_module("conv2", conv2);
        register_module("conv3", conv3);
        register_module("fc1", fc1);
        register_module("fc2", fc2);
    }

    torch::Tensor forward(torch::Tensor x) {
        //std::cout << x.sizes()<<std::endl;
        x = torch::relu(torch::max_pool2d(conv1->forward(x), 2));
        // std::cout << x.sizes() <<  std::endl;
        x = torch::relu(torch::max_pool2d(conv2->forward(x), 2));
        // std::cout << x.sizes() <<  std::endl;
        x = torch::relu(torch::max_pool2d(conv3->forward(x), 2));
        //std::cout << x.sizes() << std::endl;

        x = x.view({ -1, 1152 });
        x = torch::relu(fc1->forward(x));
        x = fc2->forward(x);
        return torch::log_softmax(x, /*dim=*/1);
    }

    torch::nn::Conv2d conv1;
    torch::nn::Conv2d conv2;
    torch::nn::Conv2d conv3;
    torch::nn::Linear fc1;
    torch::nn::Linear fc2;

 };

TORCH_MODULE(Net); // creates module holder for NetImpl
