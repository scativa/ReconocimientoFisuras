# OpenCV test
Proyectos para testear OpenCV sobre Linux y Colab
[Instalación OpenCV en Linux](/docs/Instalar Opencv-Linux.md)


## LINUX

### Compile and build
```
mkdir build
cd build
cmake -D OpenCV_DIR=/absolute/path/to/opencvlib ..
cmake --build . --config Release
```
## GOOGLE COLAB
### Subir a Google Drive
Se debe subir la carpeta completa *<opencvfolder>* ```/Colab``` de *Google Drive*.
Se debe copiar la carpeta del proyecto dentro del *Google Colab* desde el *Google Drive*. Esto se debe por problemas al referenciar carpetas con espacios como "*My Drive*", aunque se debería volver a comprobar esto.

### Compile, link y execute
```
%cp -r /content/drive/My\ Drive/Colab/*<opencvfolder>* /content/*<opencvfolder>*
%cd /content/*<opencvfolder>*/build/
!cmake -D OpenCV_DIR=_/absolute/path/to/opencvlib_ ..
!cmake --build . --config Release
! ./opencv_example
```

