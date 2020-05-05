# OpenCV & CMake example
Ejemplo que muesta como compilar un código OpenCV utilizando CMake en linux (MINT)

[Instalación OpenCV en Linux](/docs/Instalar Opencv-Linux.md)


## LINUX

### Compile and build
```
mkdir build
cd build
cmake -D OpenCV_DIR=/home/seba/opencv/build ..
cmake --build . --config Release
```

### Test
```
./opencv_example 
```
En la cosola:
```
Built with OpenCV 4.3.0-dev
Capture is opened
```
Y debe aparecer un ventana mostrando lo proyectado por la cámara de la computadora con la leyenda "Hello OpenCV"

## GOOGLE COLAB
### Subir a Google Drive
Se debe subir la carpeta completa (```./torch-test/``` o ```./example-app/```) en la carpeta ```/Colab``` de *Google Drive*. Se muestra el ejemplo de ```./example-app```

Se debe copiar la carpeta del proyecto dentro del *Google Colab* desde el *Google Drive*. Esto se debe por problemas al referenciar carpetas con espacios como "*My Drive*", aunque se debería volver a comprobar esto.

### Compile, link y execute
%cp -r /content/drive/My\ Drive/Colab/example_cmake /content/example_cmake
%cd /content/example_cmake/build/
!cmake -D OpenCV_DIR=/content/opencv/build ..
!cmake --build . --config Release
! ./opencv_example


### Testing
En la cosola:
```
/content/example_cmake/build
Built with OpenCV 4.3.0-dev
[ WARN:0] global /content/opencv/modules/videoio/src/cap_v4l.cpp (893) open VIDEOIO(V4L2:/dev/video0): can't open camera by index
No capture

(Sample:26469): Gtk-WARNING **: 14:29:22.909: cannot open display: 
```

## Referencias

### Configuración de entorno
[OpenCV Install](/docs/opencv/OpenCV-Install.md)
[OpenCV Linux](/docs/opencv/OpenCV-Install-Linux.md)
[OpenCV Google Colab](/docs/opencv/OpenCV-Install-GoogleColab.md)
[Google Colab docs](/docs/GoogleColab.md)

