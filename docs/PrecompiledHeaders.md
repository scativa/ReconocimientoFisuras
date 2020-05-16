# PrecompiledHeaders

## Paso a paso
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

## Problemas experimentados
Puede suceder que a pesar de poner la configuración indicada, producto de pruebas intermedias continúe complilándose el código completo. Esto se soluciona borrando todos los archivos de las carpetas ```/x64``` (si esa es la plataforma elegida), tanto del proyecto en particular como de la solución de Visual Studio. NO SE PUDO SOLUCIONAR. Desconozco porqué vuelve a recompilar el pch.h


## Referencias

### The Cherno
[Precompiled Headers in C+](https://www.youtube.com/watch?v=eSI4wctZUto&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=72)

### https://docs.microsoft.com/
[Precompiled Header Files](https://docs.microsoft.com/en-us/cpp/build/creating-precompiled-header-files?view=vs-2019)
[/Yc (Create Precompiled Header File](https://docs.microsoft.com/en-us/cpp/build/reference/yc-create-precompiled-header-file?view=vs-2019)

### No Visual Studio
[How to Optimize Compilation Times with Precompiled Headers (PCH Files)](https://www.codeproject.com/Articles/1188975/How-to-Optimize-Compilation-Times-with-Precompil)




