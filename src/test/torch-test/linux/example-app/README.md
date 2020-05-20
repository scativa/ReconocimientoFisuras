# Torch and CMakeList
[Combining CMakeLists.txt of Libtorch and CMakeLists.txt of ROS package](https://answers.ros.org/question/347885/combining-cmakeliststxt-of-libtorch-and-cmakeliststxt-of-ros-package/)

## Entorno
```
folder/
    example-app.cpp
    CMakeLists.txt
```

## Compilación
```
mkdir build
cd build
cmake -DCMAKE_PREFIX_PATH=/absolute/path/to/libtorch ..
cmake --build . --config Release
```


