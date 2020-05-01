# PrecompiledHeaders

## Paso a paso
### Project
Debe incluir dos archivos: ```pch.cpp``` y ```pch.h```

#### Configuración
_Project properties_
```
Prepocessor->
-> Preprocess to a file = **Yes (/P)**

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
-> Precompiled Header = Use (/Y**c**)
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
-> Precompiled Header = Use (/Y**u**)
-> Precompiled Header File = pch.h
```

## Referecnias

### The Cherno
[Precompiled Headers in C+](https://www.youtube.com/watch?v=eSI4wctZUto&list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb&index=72)

### https://docs.microsoft.com/
[Precompiled Header Files](https://docs.microsoft.com/en-us/cpp/build/creating-precompiled-header-files?view=vs-2019)

[/Yc (Create Precompiled Header File](https://docs.microsoft.com/en-us/cpp/build/reference/yc-create-precompiled-header-file?view=vs-2019)

