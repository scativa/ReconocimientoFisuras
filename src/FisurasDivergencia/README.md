# Visuras versión Sebastián
Esta es una versión en la que se perdieron cambios debido a un trabajo en paralelo con martín.
Hay modificaciones importantes como:
- ../common/globals
- Uso de librería CmdLineOpt mejorada
- Manejo de excepciones y asserts
- Funcionamiento en Colab
- TorchUtils.cpp
- CMakelist.txt

Luego de la divergencia del desarrollo se utiliza para analizar la estructura y respuesta de la red, así como el desarrollo de herramientas. Por ejemplo el cálculo de la primera capa lineal dependiente, entre otros parámetros del tamaño de la imagen de entrada.
```cpp
  namespace torch_utils
  class ConvOptionsLayer
  class SecConvOptions
```

Está planifiicado descartar _FisurasDivergencias_ del master una vez desarrolladas las características propuestas y realizadas las pruebas necesarias.

## Capa lineal
El cálculo se hace recursivo teniendo en cuenta:
1. Tamaño de las imágenes
2. Por cada capa convolucional
   - kernel
   - pool size
   - input size
3. En este caso __no__ tiene en cuenta el batch
En el ejemplo el kernel, el pool size (=2) se mantienen igual en cada capa. La entrada tiene igula alto=ancho. No se considera el padding, strides, ni otras opciones. 
Ver [TensorLayer.md](https://github.com/scativa/ReconocimientoFisuras/blob/newCVNet/docs/CVNet_CementTrainer/TensorLayers.md)

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
```

## Changelog
### Adecuación para compilar en Linux - 20200518

====
copiar en el la carpeta del proyecto ```cxxopts.hpp```
```cmdlineopt.h:```
cambiar: 
```cpp
#include <cxxopts.hpp> por #include "cxxopts.hpp"
```
====
```cpp
error: ‘struct torch::optim::AdamOptions’ has no member named ‘beta1’; did you mean ‘betas’?
 tim::Adam optimizer(net->parameters(), torch::optim::AdamOptions(2e-4).beta1(0.5));
https://github.com/pytorch/examples/pull/765/files
```

====
```cpp
for (int epoch = 0; epoch < N_EPOCH_TO_TRAIN; epoch++)
for (size_t epoch = 0; epoch < N_EPOCH_TO_TRAIN; epoch++)
```

====
```cpp
std::printf("Accuracy: %.3f% \r\n", ACCURACY);
std::printf("Accuracy: %.3f \r\n", ACCURACY);
```

### Preparativos para pasarlo a linux - 20200517

En propiedades del proyecto (para más detalle ver las documentacion sobre OpenCV en VS)
- Quito los path hacia las librerías e includes de OpenCV
- Quito la inclusion de las librerías de OpenCV


- En CementTrainer.cpp
-- Cambio el tipo uint por unsigned int usado en 
-- Borro la línea using namespace cv;

En el Código
- pch.h
Quito `#include de OpenCV`

También los .h siguientes. Creo que no da error porque deben estar incluídas en los .h de torch.
```cpp
//#include <stdint.h>
//#include <cstddef>
//#include <fstream>
//#include <iostream>
//#include <string>
//#include <vector>
//#include <stdlib.h>
//#include <tchar.h>
//#include <stdio.h>
```
