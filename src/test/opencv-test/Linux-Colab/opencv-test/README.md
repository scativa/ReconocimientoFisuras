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
./opencv-test 
```
En la cosola:
```
```
Debe aparecer un ventana mostrando dos círculos no concéntricos, uno blanco y otro verde claro.


## GOOGLE COLAB
### Subir a Google Drive
Se debe subir la carpeta completa ```./opencv-test/``` en la carpeta ```/Colab``` de *Google Drive*. Se muestra el ejemplo de ```./opencv-test```

Se debe copiar la carpeta del proyecto dentro del *Google Colab* desde el *Google Drive*. Esto se debe por problemas al referenciar carpetas con espacios como "*My Drive*", aunque se debería volver a comprobar esto.

### Compile, link y execute
```
%cp -r /content/drive/My\ Drive/Colab/opencv-test /content/opencv-test
%cd /content/opencv-test/build/
!cmake -D OpenCV_DIR=/content/opencv/build ..
!cmake --build . --config Release
! ./opencv-test
```
### Testing
En la cosola:
```
(Display Window:14907): Gtk-WARNING **: 13:38:44.857: cannot open display:
```
## Referencias

### Configuración de entorno
[OpenCV Install](/docs/opencv/OpenCV-Install.md)
[OpenCV Linux](/docs/opencv/OpenCV-Install-Linux.md)
[OpenCV Google Colab](/docs/opencv/OpenCV-Install-GoogleColab.md)
[Google Colab docs](/docs/GoogleColab.md)

