# OpenCV Install for Google Colab

## Paso a paso
No todos los pasos son necesarios. Descargas y copias dependen del estado de la Notebook Google Colab

## Entorno 

### Conectar con google drive
```
from google.colab import drive
drive.mount('/content/drive')
```

### Crear entorno Drive
```
%cd /content/drive/My\ Drive
%mkdir Colab
```

### Install linux tools

```
!apt-get install build-essential
!apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
!apt-get install python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libdc1394-22-dev
```
Se quitó *libjasper-dev* por error en el comando original:
```
apt-get install python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev **libjasper-dev** libdc1394-22-dev
```

### Download OpenCV src
Descarga de github en *my_working_directory*=*/content/drive/My\ Drive/Colab/download*
```
%mkdir /content/drive/My\ Drive/Colab/download
%cd /content/drive/My\ Drive/Colab/download
!git clone https://github.com/opencv/opencv.git
!git clone https://github.com/opencv/opencv_contrib.git
```

```
%cd /content/drive/My Drive/Colab/download/opencv/build
%cd /content
!mv /content/drive/My\ Drive/Colab/download/opencv /content
```

```
%cd /content/opencv/build
!cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local -DBUILD_DOCS=TRUE -D BUIL_EXAMPLES=TRUE ..
!make -j7
```


Si las fuentes de OpenCV se encuentra en una carpeta de Drive surge el siguiente error, por lo que hay se tuvo que mover antes de linkear y compilar a una carpeta local de Google Colab (i.e. */content/opencv*). Esto se debe a incompatibilidad de Google Drive con *hardlinks*.

```
[ 28%] Linking CXX shared library ../../lib/libopencv_core.so
CMake Error: cmake_symlink_library: System Error: Operation not supported
CMake Error: cmake_symlink_library: System Error: Operation not supported
modules/core/CMakeFiles/opencv_core.dir/build.make:1599: recipe for target 'lib/libopencv_core.so.4.3.0' failed
make[2]: *** [lib/libopencv_core.so.4.3.0] Error 1
make[2]: *** Deleting file 'lib/libopencv_core.so.4.3.0'
CMakeFiles/Makefile2:1348: recipe for target 'modules/core/CMakeFiles/opencv_core.dir/all' failed
make[1]: *** [modules/core/CMakeFiles/opencv_core.dir/all] Error 2
Makefile:162: recipe for target 'all' failed
make: *** [all] Error 2
```


### Testing
```
%cp -r /content/drive/My\ Drive/Colab/example_cmake /content/example_cmake
%cd /content/example_cmake/build/
!cmake -D OpenCV_DIR=/content/opencv/build ..
!cmake --build . --config Release
```
```
%cd /content/example_cmake/build/
! ./opencv_example
```

```
/content/example_cmake/build
Built with OpenCV 4.3.0-dev
[ WARN:0] global /content/opencv/modules/videoio/src/cap_v4l.cpp (893) open VIDEOIO(V4L2:/dev/video0): can't open camera by index
No capture

(Sample:26469): Gtk-WARNING **: 14:29:22.909: cannot open display: 
```




## Notas
**Atención** con el uso de '!' y '%'.
> The issue is that each of the !-prefixed commands runs in its own subshell -- so the ```!cd``` starts a new shell, switches directories, and then kills that shell. The ```!ls``` then starts anew in the current directory. Doing ```!cd``` ```SwitchFrequencyAnalysis && ls``` would have worked, but using python's ```os.chdir``` is the cleaner approach here.



