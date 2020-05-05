# OpenCV Test
Test opencv para Linux y Google Colab

```cpp
int main() {
	Mat image = Mat::zeros(300, 600, CV_8UC3);
	circle(image, Point(250, 150), 100, Scalar(0, 255, 128), -100);
	circle(image, Point(350, 150), 100, Scalar(255, 255, 255), -100);
	imshow("Display Window", image);
}
```


## GOOGLE COLAB
### Subir a Google Drive
Se debe subir la carpeta completa ```./opencv-test/``` en la carpeta ```/Colab``` de *Google Drive*. Se muestra el ejemplo de ```./example_cmake```

Se debe copiar la carpeta del proyecto dentro del *Google Colab* desde el *Google Drive*. Esto se debe por problemas al referenciar carpetas con espacios como "*My Drive*", aunque se debería volver a comprobar esto.

### Compile, link y execute
```
%cp -r /content/drive/My\ Drive/Colab/opencv-test /content/opencv-test
%cd /content/opencv-test/build/
!cmake -D OpenCV_DIR=/content/opencv/build ..
!cmake --build . --config Release
! ./opencv-test
```

```
CMake Error at CMakeLists.txt:4 (find_package):
  By not providing "FindOpenCVGen.cmake" in CMAKE_MODULE_PATH this project
  has asked CMake to find a package configuration file provided by
  "OpenCVGen", but CMake did not find one.

  Could not find a package configuration file provided by "OpenCVGen" with
  any of the following names:

    OpenCVGenConfig.cmake
    opencvgen-config.cmake

  Add the installation prefix of "OpenCVGen" to CMAKE_PREFIX_PATH or set
  "OpenCVGen_DIR" to a directory containing one of the above files.  If
  "OpenCVGen" provides a separate development package or SDK, be sure it has
  been installed.

-- Configuring incomplete, errors occurred!
See also "/content/opencv-test/build/CMakeFiles/CMakeOutput.log".
make: *** No targets specified and no makefile found.  Stop.
/bin/bash: ./opencv-test: No such file or directory
```
## Referencias

### Configuración de entorno
[OpenCV Install](/docs/opencv/OpenCV-Install.md)
[OpenCV Linux](/docs/opencv/OpenCV-Install-Linux.md)
[OpenCV Google Colab](/docs/opencv/OpenCV-Install-GoogleColab.md)
[Google Colab docs](/docs/GoogleColab.md)

