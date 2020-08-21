# Visuras versión Sebastián
Esta es una versión en la que se perdieron cambios debido a un trabajo en paralelo con martín.
Hay modificaciones importantes como:
- ../common/globals
- Uso de librería CmdLineOpt mejorada
- Manejo de excepciones y asserts
- Funcionamiento en Colab
- Tensor utils.cpp
- CMakelist.txt

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