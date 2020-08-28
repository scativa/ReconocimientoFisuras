# Tensor Layers
Soluciones para la definición de los tamaños de las capas Lineales de salida y la relación con el tamaño de la imagen.

Propuesta para el cálculo de de esta capa en forma dinámica ante el cambio de tamaño de la imagen. 

__Keywords__: Module::View

## Problemas
Inconvenientes para el cálculo de la primer capa lineal.
```
Error: shape '[-1, 1152]' is invalid for input of size 768
```
```
Error: size mismatch, m1: [32 x 128], m2: [1152 x 100] at C:\w\b\windows\pytorch\aten\src\TH/generic/THTensorMath.cpp:41
```


__Importante__: Hubo inconvenientes con la configuración puesta por código que no se detectaba. El problema es que al iniciar la ejecución cargaba un modelo guardado en disco `torch::load(net, modelfn);`. Ahí __no sólo_ se almacenan los pesos, también configuración de la red como ser tamaño de las capas y kernels. Habría que ver que otro parámetro de la estructura y cómo controlarlo en tiempo de ejecución. 

## Capa lineal
El cálculo se hace recursivo teniendo en cuenta:
1. Tamaño de las imágenes
2. Por cada capa convolucional
   - kernel
   - pool size
   - input size
3. En este caso __no__ tiene en cuenta el batch
En el ejemplo el kernel, el pool size (=2) se mantienen igual en cada capa. La entrada tiene igula alto=ancho. No se considera el padding, strides, ni otras opciones. 

```cpp
const uint32_t m_batch_size = 16;
uint32_t img_size = 64;
constexpr int kernel_size = 3;
constexpr int cant_layers = 3;

uint32_t rec_fc1_input_size(uint32_t in_size, int k_size, int layer) {
    uint32_t aux_size = (in_size - (k_size - 1)) / 2 /*pool_size*/;
    if (layer == cant_layers)
        return aux_size;
    else
        return rec_fc1_input_size(aux_size, k_size, layer + 1);
}

uint32_t fc1_input_size() {
    uint32_t aux_rec = rec_fc1_input_size(img_size, kernel_size, 1);
    return aux_rec * aux_rec * 32 /*last_layer_out_size*/;
}

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
    }

    torch::Tensor forward(torch::Tensor x) {
        torch::Device device = (torch::cuda::is_available() ? torch::kCUDA : torch::kCPU);
        x = x.to(device);

        x = conv1->forward(x);
        x = torch::max_pool2d(x, 2);
        x = torch::relu(x);

        x = torch::relu(torch::max_pool2d(conv2->forward(x), 2));
        x = torch::relu(torch::max_pool2d(conv3->forward(x), 2));

        int64_t vsize = x.size(1) * x.size(2) * x.size(3); // Capas (channels) x Ancho x Alto
        x = x.view({ -1, vsize });
        x = torch::relu(fc1->forward(x));
        x = fc2->forward(x);
        
        return torch::log_softmax(x, /*dim=*/1);
    }
 };

```
