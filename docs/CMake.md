# CMake
Uso del `CMake` y `Makefiles.txt` para el buil de los proyectos. Hasta ahora usados en Linux y Google Colab, tanto para proyectos propios como para librerías bajadas como __OpenCV__ y __libtorch__.

# Comandos usados
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
