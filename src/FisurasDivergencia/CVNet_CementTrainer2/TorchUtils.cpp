#include "pch.h"
#include "TorchUtils.h"

namespace torch_utils {

    using namespace std;

    void print_opt(at::Tensor t) {
        auto optt = t.options();

        cout // << "Tensor options: " << endl
            << "Device: " << optt.device() << "(" << optt.device_index() << "); "
            << "Dtype: " << optt.dtype() << endl
            << "Size: " << t.sizes() 
            << "; Strides: " << t.strides() << endl
            << endl;
    }

    void print_opt(torch::Device device, torch::Dtype dtype) {
        auto optd = torch::TensorOptions(device).dtype(dtype);

        cout << "Device options: " << endl
            << "Device: " << optd.device() << "(" << optd.device_index() << "); "
            << "Dtype: " << optd.dtype() << endl << endl;

    }

    void print_opt(torch::nn::Linear l) {
        print_opt(l->weight);
    }

    void ConvOptionsLayer::Print() {
        cout << "Channels: " << in_channels << "->" << out_channels << ". Kernel: " << kernel_size << ". Pool: " << pool_size << endl;
    };

    torch::nn::Conv2dOptions ConvOptionsLayer::Conv2dOptions() { 
        return torch::nn::Conv2dOptions(in_channels, out_channels, kernel_size); 
    };

    uint32_t SecConvOptions::NextLinearLayer_InputSize() {
        uint32_t aux_rec = recLastLayer_OutputSize(img_size, 1);
        uint32_t aux_res = aux_rec * aux_rec * 32 /*last_layer_out_size*/;
        // cout << "recLastLayer_OutputSize = " << aux_rec << endl;
        // cout << "NextLinearLayer_InputSize = " << aux_res << endl;
        return aux_res;
    };
    
    void SecConvOptions::Print() {
        if (layers_opts.empty())
            cout << "Empty" << endl;
        else {
            cout << "Layers: " << Cant_ConvLayers() << ". Image(CxWxH): " << layers_opts[0].in_channels << img_size << "x" << img_size << "x"<< endl;
            for (auto op : layers_opts) {
                op.Print();
            };
        }
    };

    uint32_t SecConvOptions::recLastLayer_OutputSize(uint32_t in_size, int layer) {
        int64_t kernel_size = layers_opts[layer - 1].kernel_size;
        int64_t pool_size = layers_opts[layer - 1].pool_size;

        uint64_t aux_size = (in_size - (kernel_size - 1)) / pool_size;
        // cout << "recLastLayer_OutputSize(" << in_size << "," << kernel_size << "," << layer << ") = " << aux_size << endl;
        if (layer == kernel_size)
            return aux_size;
        else
            return recLastLayer_OutputSize(aux_size, layer + 1);
    };
}
