# Instalación OpenCV en Linux (MINT)

[OpenCV docs - Installation in Linux](https://docs.opencv.org/master/d7/d9f/tutorial_linux_install.html)


## Pasos realizados

### Install tools
```
sudo apt-get install build-essential
sudo apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
sudo apt-get install python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libdc1394-22-dev
```
Se quitó *libjasper-dev* por error (*E: No se ha podido localizar el paquete libjasper-dev#.*) en el comando original:
```
apt-get install python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev **libjasper-dev** libdc1394-22-dev
```

### Download OpenCV src
Descarga de github en *my_working_directory*=*opencv/*

```
cd ~/<my_working_directory>
git clone https://github.com/opencv/opencv.git
git clone https://github.com/opencv/opencv_contrib.git
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local -DBUILD_DOCS=TRUE -D BUIL_EXAMPLES=TRUE ..
make -j7
```
 
## Log
./Instalacion OpenCV-Linux.log.md

## Referencias
[OpenCV.or Installation in Linux](https://docs.opencv.org/master/d7/d9f/tutorial_linux_install.html)


