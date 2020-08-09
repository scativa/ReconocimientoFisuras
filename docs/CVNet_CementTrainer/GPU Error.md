# CVN_CementTrainer2

## Error NET GPU
Documentación sobre el error que ocurre al ejecuta `CVN_CementTrainer2` corriendo sobre el GPU (hasta ahora problado únicamente en Google Colab) surge un error sobre incompatibilidad de tipos en los tensores. Pareciera se en la clase Net. Esto no sucede con el mismo código utilizando CPU.

# SOLUCIONADO

**Display del error (fragmento)**:
```
terminate called after throwing an instance of 'c10::Error'
  what():  Input type (CPUFloatType) and weight type (CUDAFloatType) should be the same (_convolution at /pytorch/aten/src/ATen/native/Convolution.cpp:696)
frame #1: at::native::_convolution(at::Tensor const&, at::Tensor const&, at::Tensor const&, c10::ArrayRef<long>, c10::ArrayRef<long>, c10::ArrayRef<long>, bool, c10::ArrayRef<long>, long, bool, bool, bool) + 0x3793 (0x7f27b59a4283 in /content/libtorch/lib/libtorch_cpu.so)...
frame #14: torch::nn::Conv2dImpl::_conv_forward(at::Tensor const&, at::Tensor const&) + 0x566 (0x7f27b80a3666 in /content/libtorch/lib/libtorch_cpu.so)
frame #15: torch::nn::Conv2dImpl::forward(at::Tensor const&) + 0x10 (0x7f27b80a38b0 in /content/libtorch/lib/libtorch_cpu.so)
frame #16: NetImpl::forward(at::Tensor) + 0xc6 (0x55de7edfba1e in ./CVNet_CementTrainer2)
frame #17: float test_batch<torch::data::StatelessDataLoader<torch::data::datasets::MapDataset<torch::data::datasets::Cement, torch::data::transforms::Stack<torch::data::Example<at::Tensor, at::Tensor> > >, torch::data::samplers::RandomSampler> >(Net, torch::data::StatelessDataLoader<torch::data::datasets::MapDataset<torch::data::datasets::Cement, torch::data::transforms::Stack<torch::data::Example<at::Tensor, at::Tensor> > >, torch::data::samplers::RandomSampler>&, unsigned long) + 0xf9 (0x55de7ee00ad6 in ./CVNet_CementTrainer2)
```

## Posible camino de solución
>For tensors whose creation is not in our hands, like those coming from the MNIST dataset, we must insert explicit to() calls. This means
```cpp
torch::Tensor real_images = batch.data;
```
>becomes
```cpp
torch::Tensor real_images = batch.data.to(device);
```
>and also our model parameters should be moved to the correct device:
```cpp
generator->to(device);
discriminator->to(device);
```
También estudiar
```cpp
torch::randn({3, 4}, torch::dtype(torch::kFloat32).device(torch::kCUDA, 1).requires_grad(true))
```

## Solución
No eran pasados a la red. Falta probar si también es necesario pasar las imágenes y los targets en `CementTrainer.cpp`


Net.h
```cpp
torch::Tensor forward(torch::Tensor x) {
   ...
   x = x.to(device);
   ...
}
```

CementTrainer.cpp
```cpp
Cement::Cement(const std::string& ROOT_FOLDER, const std::string& PREFIX_FN, const Mode& MODE) {
   ...
   images_ = images_.to(device);
   targets_ = targets_.to(device);
   ...
}
```

### Testing
Ejemplo de código funcionando sobre C++ que utiliza GPU si está disponible y repite la operación forzando el uso de CPU.
[exampleGPU-app.cpp](src/test/torch-test/linux/example-app/exampleGPU-app.cpp)

### Referencias
1. [pytorch.org - USING THE PYTORCH C++ FRONTEND](https://pytorch.org/tutorials/advanced/cpp_frontend.html)
2. [pytorch.org - STRUCT CUDAGUARD](https://pytorch.org/cppdocs/api/structc10_1_1cuda_1_1_c_u_d_a_guard.html#exhale-struct-structc10-1-1cuda-1-1-c-u-d-a-guard)
3. [GitHub - get/set device in c++ #14959](https://github.com/pytorch/pytorch/issues/14959)
4. [TENSOR CREATION API](https://pytorch.org/cppdocs/notes/tensor_creation.html)
