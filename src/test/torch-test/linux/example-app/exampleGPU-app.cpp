#include <torch/torch.h>
#include <iostream>


int main() {
    std::cout  << std::endl << "exampleGPU-app start..." << std::endl << std::endl;

/*
    torch::Device device = (torch::cuda::is_available() ? torch::kCUDA : torch::kCPU);
    
    std::cout << "Device: ";
    if (device == torch::kCUDA) std::cout << "CUDA"; else std::cout << "CPU";
    std::cout << std::endl;
    
    torch::Tensor tensor = torch::rand({2, 3});
    std::cout << tensor << std::endl;
*/

    // Place this somewhere at the top of your training script.
    // torch::Device device(torch::kCPU);
        
       
    torch::Device device = torch::kCUDA;
    if (torch::cuda::is_available()) {
      std::cout << "CUDA is available!" << std::endl;
      device = torch::kCUDA; 
//      torch::set_default_tensor_type(torch::cuda::FloatTensor);
    } else {
      std::cout << "CUDA does not work." << std::endl;
      device = torch::kCPU; 
//      torch::set_default_tensor_type(torch::FloatTensor);
    } 

    std::cout << "Device: ";
    if (device == torch::kCUDA) std::cout << "CUDA"; else std::cout << "CPU";
    std::cout << std::endl << std::endl;

  // .to(torch::Device(torch::kCUDA, 1))
  // .to(torch::kCUDA);
 
// https://pytorch.org/cppdocs/api/structc10_1_1cuda_1_1_c_u_d_a_guard.html#exhale-struct-structc10-1-1cuda-1-1-c-u-d-a-guard 
// https://github.com/pytorch/pytorch/issues/14959
//    c10::cuda::current_device(device);  
  
  //  if (torch::cuda::is_available()) {
  //      std::cout << "Running in GPU..." << std::endl;
        at::Tensor w1 = torch::randn({ 10000, 10000 }, device).div(sqrtf(6)).set_requires_grad(true);
//        at::Tensor w1 = torch::randn({ 10000, 10000 }).div(sqrtf(6)).set_requires_grad(true).cuda();
//        at::Tensor w1 = w0.to(torch::kCUDA);
        at::Tensor r = torch::mm(w1,w1);
//    }

    std::cout << "Force CPU..." << std::endl;
//    at::Tensor w1 = torch::randn({ 10000, 10000 }).div(sqrtf(6)).set_requires_grad(true);
//    at::Tensor w1 = torch::randn({ 10000, 10000 }).div(sqrtf(6)).set_requires_grad(true).to(device);
    at::Tensor w2 = w1.to(torch::kCPU);
    at::Tensor r2 = torch::mm(w2,w2);

    // https://pytorch.org/cppdocs/notes/tensor_creation.html
    // torch::randn({3, 4}, torch::dtype(torch::kFloat32).device(torch::kCUDA, 1).requires_grad(true))
    

    std::cout << std::endl << "exampleGPU-app end." << std::endl;
}
