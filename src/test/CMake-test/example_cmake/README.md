# OpenCV & CMake example
Ejemplo que muesta como compilar un código OpenCV utilizando CMake en linux (MINT)

[Instalación OpenCV en Linux](/docs/Instalar Opencv-Linux.md)


## Compile and build
```
mkdir build
cd build
cmake -D OpenCV_DIR=/home/seba/opencv/build ..
cmake --build . --config Release
```

## Test
```
./opencv_example 
```
En la cosola:
```
Built with OpenCV 4.3.0-dev
Capture is opened
```
Y debe aparecer un ventana mostrando lo proyectado por la cámara de la computadora con la leyenda "Hello OpenCV"

