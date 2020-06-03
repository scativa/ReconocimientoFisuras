// https://pytorch.org/cppdocs/api/structc10_1_1cuda_1_1_c_u_d_a_guard.html#exhale-struct-structc10-1-1cuda-1-1-c-u-d-a-guard 
// https://github.com/pytorch/pytorch/issues/14959
// https://pytorch.org/cppdocs/notes/tensor_creation.html
// torch::randn({3, 4}, torch::dtype(torch::kFloat32).device(torch::kCUDA, 1).requires_grad(true))
  
#include <torch/torch.h>
#include <iostream>


int main() {
    std::cout  << std::endl << "exampleGPU-app start..." << std::endl << std::endl;

    torch::Device device = torch::kCUDA;
    if (torch::cuda::is_available()) {
      std::cout << "CUDA is available!" << std::endl;
      device = torch::kCUDA; 
    } else {
      std::cout << "CUDA does not work." << std::endl;
      device = torch::kCPU; 
    } 

    std::cout << "Device: ";
    if (device == torch::kCUDA) std::cout << "CUDA"; else std::cout << "CPU";
    std::cout << std::endl << std::endl;

 
    at::Tensor w1 = torch::randn({ 10000, 10000 }, device).div(sqrtf(6)).set_requires_grad(true);
    at::Tensor r = torch::mm(w1,w1);

    std::cout << "Force CPU..." << std::endl;
    at::Tensor w2 = w1.to(torch::kCPU);
    at::Tensor r2 = torch::mm(w2,w2);


    std::cout << std::endl << "exampleGPU-app end." << std::endl;
}
