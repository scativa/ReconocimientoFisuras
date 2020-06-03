# Precompiled Head
Ejemplo de headers precompilados.

## Linux

### g++
Utiliza heders precompilados `pch.h` utilizando `g++` desde la línea de comandos.
El archivo `Main.cpp` debe incluir explicitamente el header `#include "pch.h"`
Se antepone el comando `time` para que se muestre el tiempo de compilación.
 
#### Comandos
```
time g++ -std=c++11 pch.h
time g++ -std=c++11 Main.cpp
```

#### Test
Compilación `Main.cpp` sin headers precompilados (borrar `pch.h.gch`).
```
$ cd ./
$ rm ./pch.h.gch 
$ time g++ -std=c++11 Main.cpp

real	0m0,739s
user	0m0,705s
sys		0m0,034s
```
tiempo total: **0m1,478s**


Ahora precompilando primero `pch.h`
```
$ time g++ -std=c++11 pch.h

real	0m1,370s
user	0m1,242s
sys		0m0,128s
```
tiempo total: **0m2,740s**


Recompilación `Main.cpp` 
```
$ time g++ -std=c++11 Main.cpp

real	0m0,170s
user	0m0,137s
sys		0m0,033s
```
tiempo total: **0m0,340s**


### CMake
Utiliza heders precompilados `pch.h` utilizando `cmake`.
No es necesario que `Main.cpp` debe incluya el header precompilado.

#### Comandos
```
cd ./build
cmake -S .. -B .
cmake --build . --config Release
```

#### CMakefiles.txt
El CMakefiles.txt debe incluir el comando
```cmake
target_precompile_headers(<your_target> PUBLIC|PRIVATE <header>)


Para que muestre los tiempo de compilación debe incluir alguno de estos comandos
```cmake
set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
set_property(TARGET <your_target> PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
```

#### Test
Compilación sin utilizar el header precompilado
```
$ cd ./build
$ rm -r *
$ cmake -S .. -B .
```
```
$ cmake --build . --config Release
Scanning dependencies of target PrecompiledHeader
[ 50%] Building CXX object CMakeFiles/PrecompiledHeader.dir/Main.cpp.o
Elapsed time: 1 s. (time), 0.000304 s. (clock)
[100%] Linking CXX executable PrecompiledHeader
[100%] Built target PrecompiledHeader
```
tiempo total: **0m1,340s**

Compilación utilizando el header precompilado
```cmake
target_precompile_headers(PrecompiledHeader PUBLIC pch.h)
```
```
$ cd ./build
$ rm -r *
$ cmake -S .. -B .
```
Primer compilación, tanto `Main.cpp` como `pch.h`
```
$ cmake --build . --config Release
Scanning dependencies of target PrecompiledHeader
[ 33%] Building CXX object CMakeFiles/PrecompiledHeader.dir/cmake_pch.hxx.gch
Elapsed time: 1 s. (time), 0.000296 s. (clock)
[ 66%] Building CXX object CMakeFiles/PrecompiledHeader.dir/Main.cpp.o
Elapsed time: 0 s. (time), 0.000255 s. (clock)
[100%] Linking CXX executable PrecompiledHeader
[100%] Built target PrecompiledHeader
```
tiempo total: **0m1,551s**


Ahora sólo se modifica una línea de `Main.cpp` y luego se recompila
```
$ cmake --build . --config Release
Scanning dependencies of target PrecompiledHeader
[ 33%] Building CXX object CMakeFiles/PrecompiledHeader.dir/Main.cpp.o
Elapsed time: 0 s. (time), 0.000282 s. (clock)
[ 66%] Linking CXX executable PrecompiledHeader
[100%] Built target PrecompiledHeader
```
tiempo total: **0m0,282s**


## Referencias
[How to measure compile time per object in CMake?](https://stackoverflow.com/questions/54377926/how-to-measure-compile-time-per-object-in-cmake)


