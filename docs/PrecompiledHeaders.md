# PrecompiledHeaders

## Requerimientos
* Linux: CMake 3.16 o superior

## VISUAL STUDIO Paso a paso
### Project
Debe incluir dos archivos: ```pch.cpp``` y ```pch.h```

#### Configuración
_Project properties_
```
Prepocessor->
-> Preprocess to a file = Yes (/P)

Precompiled Headers"->
-> Precompiled Header = Use (/Yu)
-> Precompiled Header File = pch.h
```
### pch.cpp
#### Código
Sólo una línea
```#include "pch.h"```

#### Configuración
```
Prepocessor->
-> Preprocess to a file = No
Precompiled Headers->
-> Precompiled Header = Use (/Yc)
-> Precompiled Header File = pch.h
```

### Archivos cpp que usan precompiled headers
#### Código
Al comenzar el código
```#include "pch.cpp"```

#### Configuración
```
Prepocessor->
-> Preprocess to a file = No

Precompiled Headers"->
-> Precompiled Header = Use (/Yu)
-> Precompiled Header File = pch.h
```

## Linux
Usando el mísmo código que Visual Studio, sólo se quitaron dos includes de `pch.h`
```cpp
//#include <tchar.h>
// Windows API 
// #include <Windows.h>
```

Compilar `Main.cpp` midiendo tiempos SIN precompilas headers
```
$ time g++ -std=c++11 Main.cpp

real	0m0,506s
user	0m0,387s
sys	0m0,082s
```
Precompiliar `pch.h`
```
$ time g++ -std=c++11 pch.h
pch.h:1:9: warning: #pragma once in main file
 #pragma once
         ^~~~

real	0m0,661s
user	0m0,565s
sys	0m0,096s
```
Compilar `Main.cpp` nuevamente con el header precompilador
```
$ time g++ -std=c++11 Main.cpp

real	0m0,139s
user	0m0,113s
sys	0m0,026s
```

### CMake
[target_precompile_headers - cmake.org](https://cmake.org/cmake/help/git-stage/command/target_precompile_headers.html)

[pch unity cmake](https://onqtam.com/programming/2019-12-20-pch-unity-cmake-3-16/)

[pre-compiled-headers-gcc-clang-cmake](http://mochan.info/c++/2019/11/12/pre-compiled-headers-gcc-clang-cmake.html)

## Problemas experimentados
* Visual Studio: Puede suceder que a pesar de poner la configuración indicada, producto de pruebas intermedias continúe complilándose el código completo. Esto se soluciona borrando todos los archivos de las carpetas ```/x64``` (si esa es la plataforma elegida), tanto del proyecto en particular como de la solución de Visual Studio. NO SE PUDO SOLUCIONAR. Desconozco porqué vuelve a recompilar el pch.h
* CMake: No reconoce el comando `target_precompile_headers`. El preciso actualizar CMake a una versión 3.16 o superior

## Referencias

[The Cherno - Precompiled Headers in C+](https://www.youtube.com/watch?v=eSI4wctZUto&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=72)

[microsoft.com - Precompiled Header Files](https://docs.microsoft.com/en-us/cpp/build/creating-precompiled-header-files?view=vs-2019)

[microsoft.com - /Yc (Create Precompiled Header File](https://docs.microsoft.com/en-us/cpp/build/reference/yc-create-precompiled-header-file?view=vs-2019)


[How to Optimize Compilation Times with Precompiled Headers (PCH Files)](https://www.codeproject.com/Articles/1188975/How-to-Optimize-Compilation-Times-with-Precompil)




