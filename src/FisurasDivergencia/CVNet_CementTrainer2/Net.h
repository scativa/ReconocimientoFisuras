#pragma once
#include "pch.h"

#include "../common/globals.h"
#include "TorchUtils.h"

using namespace std;

const uint32_t m_batch_size = 16;
uint32_t img_size = 64;
constexpr int kernel_size = 3;
constexpr int cant_layers = 3;

uint32_t rec_fc1_input_size(uint32_t in_size, int k_size, int layer) {
    uint32_t aux_size = (in_size - (k_size - 1)) / 2 /*pool_size*/;
    cout << "rec_fc1_input_size (" << in_size << "," << k_size << "," << layer << ") = " << aux_size << endl;
    if (layer == cant_layers)
        return aux_size;
    else
        return rec_fc1_input_size(aux_size, k_size, layer + 1);
}

uint32_t fc1_input_size() {
    uint32_t aux_rec = rec_fc1_input_size(img_size, kernel_size, 1);
    uint32_t aux_res = aux_rec * aux_rec * 32 /*last_layer_out_size*/;
    cout << "rec_fc1_input_size = " << aux_rec << endl;
    cout << "fc1_input_size = " << aux_res << endl;
    return aux_res;
}


#define IF_PRINT if (globals::verbose_mode && first_time)
#define PRINT_TS(label,t) IF_PRINT cout << label << " tensor size: " << t.sizes() << "; strides: " << t.strides() << endl

struct NetImpl : torch::nn::Module {

    torch::nn::Conv2d conv1;
    torch::nn::Conv2d conv2;
    torch::nn::Conv2d conv3;
    torch::nn::Linear fc1;
    torch::nn::Linear fc2;

    NetImpl() :
        // https://pytorch.org/cppdocs/api/structtorch_1_1nn_1_1_conv_options.html#_CPPv4I_6size_tEN5torch2nn11ConvOptionsE
        conv1(torch::nn::Conv2dOptions(3, 32, kernel_size)), // ConvOptions(int64_t in_channels, int64_t out_channels, ExpandingArray<D> kernel_size)
        conv2(torch::nn::Conv2dOptions(32, 32, kernel_size)),
        conv3(torch::nn::Conv2dOptions(32, 32, kernel_size)),
        fc1(fc1_input_size(), 100),
        fc2(100, 2) {

        // register_module() is needed if we want to use the parameters() method later on
        register_module("conv1", conv1);
        register_module("conv2", conv2);
        register_module("conv3", conv3);
        register_module("fc1", fc1);
        register_module("fc2", fc2);

        bool first_time = true;
        PRINT_TS("fc1 weight", fc1->weight);
        PRINT_TS("fc2 weight", fc2->weight);

        torch_utils::SecConvOptions conv_options(img_size);
        conv_options.layers_opts.push_back(torch_utils::ConvOptionsLayer(3,32,kernel_size,2));
        conv_options.layers_opts.push_back(torch_utils::ConvOptionsLayer(32,32,kernel_size,2));
        conv_options.layers_opts.push_back(torch_utils::ConvOptionsLayer(32,32,kernel_size,2));

        conv_options.Print();

        cout << "NextLinearLayer_InputSize=" << conv_options.NextLinearLayer_InputSize() << endl;
    }

    torch::Tensor forward(torch::Tensor x) {
        static bool first_time = true; 
        torch::Device device = (torch::cuda::is_available() ? torch::kCUDA : torch::kCPU);
        PRINT_TS("fc1 weight", fc1->weight);

        x = x.to(device);
        PRINT_TS("fc1 weight", fc1->weight);



        IF_PRINT{ // Imprime los datos del Tensor SÓLO la primera vez.
            cout << endl << "NetImpl.forward (Net.h) - " << endl;
            PRINT_TS("input tensor",x);
            //print_opt(x);
        }

        IF_PRINT cout << endl << "== Conv1 ==" << endl;
        x = conv1->forward(x);
        PRINT_TS("forward out", x);
        x = torch::max_pool2d(x, 2);
        PRINT_TS("max_pool2d out", x);
        x = torch::relu(x);
        PRINT_TS("relu out", x);

        IF_PRINT cout << endl << "== Conv2 ==" << endl;
        x = torch::relu(torch::max_pool2d(conv2->forward(x), 2));
        PRINT_TS("out tensor size: ", x);

        IF_PRINT cout << endl << "== Conv3 ==" << endl;
        x = torch::relu(torch::max_pool2d(conv3->forward(x), 2));
        PRINT_TS("out tensor size: ", x);

        IF_PRINT cout << endl << "== XView ==" << endl;
        int64_t vsize = x.size(1) * x.size(2) * x.size(3);
        
        //auto xa = x.view({ -1, vsize });
        /*
        auto xb = x.view({ -1, x.size(0) });
        auto xc = x.view({ x.size(0), -1 });
        auto xd = x.view({ -1, x.size(1) * x.size(2) * x.size(3) });
        auto xd = x.view({ -1, x.size(0) });
        */

        x = x.view({ -1, vsize });
        PRINT_TS("out tensor size: ", x);

        //x = x.view({ -1, x.size(0) });
        //x = x.view({ x.size(0), -1 });
        // https://stackoverflow.com/questions/60826846/dimension-mismatch-cnn-libtorch-pytorch

        PRINT_TS("fc1 weight", fc1->weight);

        x = torch::relu(fc1->forward(x));
        PRINT_TS("fc1 out tensor size: ",x);

        x = fc2->forward(x);
        PRINT_TS("fc1 out tensor size: ", x);

        if (first_time) first_time = false;

        return torch::log_softmax(x, /*dim=*/1);
    }


 };

TORCH_MODULE(Net); // creates module holder for NetImpl
