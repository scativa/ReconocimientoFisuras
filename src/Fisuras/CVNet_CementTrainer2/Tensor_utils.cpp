#include "pch.h"
#include "Tensor_utils.h"

using namespace std;

void print_opt(at::Tensor t) {
    auto optt = t.options();

    cout << "Tensor options: " << endl
        << "Device: " << optt.device() << "(" << optt.device_index() << ") " << endl
        << "Dtype: " << optt.dtype() << endl << endl;
}

void print_opt(torch::Device device, torch::Dtype dtype) {
    auto optd = torch::TensorOptions(device).dtype(dtype);

    cout << "Device options: " << endl
        << "Device: " << optd.device() << "(" << optd.device_index() << ") " << endl
        << "Dtype: " << optd.dtype() << endl << endl;

}
