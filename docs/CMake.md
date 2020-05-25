# CMake
Uso del `CMake` y `Makefiles.txt` para el buil de los proyectos. Hasta ahora usados en Linux y Google Colab, tanto para proyectos propios como para librerías bajadas como __OpenCV__ y __libtorch__.

## Versiones Requeridas
Release 3.?? Para OpenCV y libtorch

Release 3.16 para utilizar precompiled headers

## Instalación - Update
[How do I install the latest version of cmake from the command line?](https://askubuntu.com/questions/355565/how-do-i-install-the-latest-version-of-cmake-from-the-command-line)

1. Uninstall the default version provided by Ubuntu's package manager and configuration by using:
```
sudo apt remove --purge --auto-remove cmake
```
or:
```
sudo apt purge --auto-remove cmake
```
2. Go to the official CMake webpage, then download and extract the latest version. Update the version and build variables in the following command to get the desired version:
```
version=3.16 build=5 
mkdir ~/temp cd ~/temp 
wget https://cmake.org/files/v$version/cmake-$version.$build.tar.gz 
tar -xzvf cmake-$version.$build.tar.gz cd cmake-$version.$build/
```
3. Install the extracted source by running:
```
./bootstrap 
make -j$(nproc) 
sudo make install
```
4. Test your new cmake version.
```
cmake --version
```

*Nota*: En caso de ocurrir el siguiente error _Could **NOT find OpenSSL**, try to set the path to OpenSSL root folder in the system variable OPENSSL_ROOT_DIR_ al ejecutar el comando `./bootstrap`, ejecutar: 
```
sudo apt install libssl-dev
```

## Comandos usados
Buscar dónde está el archivo _Config.cmake_ dentro del código de libtorch
```
$ find /home/seba/libtorch -type f -name "*Config.cmake"
```
Debug CMake
```
Debug flags: -Wdev, --debug-output and --trace
```

## Referencias
[Introduction to CMake by Example](http://derekmolloy.ie/hello-world-introductions-to-cmake/)

[How do I debug CMakeLists.txt files?](https://stackoverflow.com/questions/22803607/how-do-i-debug-cmakelists-txt-files)

[CMake and FIND PACKAGE](http://wiki.icub.org/wiki/CMake_and_FIND_PACKAGE)

[find_package](https://cmake.org/cmake/help/latest/command/find_package.html)

[cmake-variables](https://cmake.org/cmake/help/v3.0/manual/cmake-variables.7.html)

[cmake-env-variables](https://cmake.org/cmake/help/v3.16/manual/cmake-env-variables.7.html)

[CXXFLAGS](https://cmake.org/cmake/help/v3.16/envvar/CXXFLAGS.html)

[message](https://cmake.org/cmake/help/v3.0/command/message.html)

### Referencias - Update
[cmake.org - Download](https://cmake.org/download/)

[cmake.org - Release notes 3.16](https://cmake.org/cmake/help/v3.16/release/3.16.html)

[How do I install the latest version of cmake from the command line?](https://askubuntu.com/questions/355565/how-do-i-install-the-latest-version-of-cmake-from-the-command-line)

[NOT find OpenSSL - stackoverflow.com](https://stackoverflow.com/questions/16248775/cmake-not-able-to-find-openssl-library)
