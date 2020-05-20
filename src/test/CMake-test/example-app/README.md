# CMake
Ejemplo para experimentar con CMake a partir de una CMakelist.txt usando libtorch
Testeado para Linux MINT y Google Colab

# Torch and CMakeList
[Combining CMakeLists.txt of Libtorch and CMakeLists.txt of ROS package](https://answers.ros.org/question/347885/combining-cmakeliststxt-of-libtorch-and-cmakeliststxt-of-ros-package/)

## Entorno
```
folder/
    example-app.cpp
    CMakeLists.txt
```

### Compile, link and execute
```
mkdir build
cd build
cmake -DCMAKE_PREFIX_PATH=/home/seba/libtorch ..
cmake --build . --config Release
./example-app
```

## Testing
El resultado debería ser una salida similar a la siguiente:
```
 0.9234  0.5967  0.6285
 0.5452  0.0881  0.7094
[ CPUFloatType{2,3} ]
```

## Referencias

### Configuración de entorno
[Documentación de entorno](/docs/torch/README.md)
[CMake](/docs/CMake.md)
[Pytorch example](/src/test/torch-test/linux/example-app/README.md)


