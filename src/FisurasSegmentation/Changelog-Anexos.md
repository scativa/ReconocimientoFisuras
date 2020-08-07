# Changelog - Anexos

## Anexo I - 22/07/2020
Detalle de cambios puntos 4) y 5)

### 4) Problemas precompilación de headers
Problema: Ante la modificación en alguno de los archivos siguientes recompilaba todas las librerías (particularmente la libtorch).

- Config.h
- CementDataset.cpp
- Serialize.cpp

#### Solución
##### Archivos fuentes
En los archivos 
- CementDataset.cpp
- Serialize.cpp

Se mueve la línea `#include "pch.h"` del `.h` al `.cpp` (nota, el `pch.h` debe ser el primer include en cada caso).

##### Propiedades de los archivos
Se cambia la configuración en _Configuration properties_-> _C/C++_->
```
Precompiled Headers->
	- Precompiled Header: 
	- Precompiled Header File: stdafx.h
```
por
```
Precompiled Headers->
	- Precompiled Header: Use (/Yc)
	- Precompiled Header File: pch.h
```

##### Configuración de proyecto
Siquiendo las instrucciones del PCH se ajusta la configuración del proyecto, aunque de todas formas funcionaba sin esta modificación.

_Configuration properties_-> _C/C++_->
```
Prepocessor->
	- Preprocess to a file = Yes (/P)

Precompiled Headers->
	- Precompiled Header: Use (/Yc)
	- Precompiled Header File: pch.h
```

A pesar de lo indicado en las instrucciones generales del PCH se configuró _C/C++_-> Prepocessor -> Preprocess to a file: **NO**_
Si se usa "Yes" da el siguiente error: `LNK1181 cannot open input file 'x64\Release\Segmentation.obj'`

### 5) Librerías

#### Actualización librerías
Debido a la actulización de `OpenCV 4.2.0` a `4.3.0` y `Pytorch 1.4` a `1.5`

Se cambia en _Linker -> Input -> Additional dependencies_:
- `opencv420.lib` por `opencv430.lib`
- `torch.lib` por `torch_cpu.lib`


#### Depuración de librerías e include
__Configuratios properties__

Se quitan las líneas
1. *VC++ Directories*->
   - __*Include Directories:*__
	 - $(VC_IncludePath)
	 - $(WindowsSDK_IncludePath)
   - __*Library Directories:*__
	 - $(VC_LibraryPath_x64)
	 - $(WindowsSDK_LibraryPath_x64)
2. *Linker*->*Input*->  
   - __*Additional Denpendencies:*__        
     - `kernel32.lib; user32.lib; gdi32.lib; winspool.lib; comdlg32.lib; advapi32.lib; shell32.lib; ole32.lib; oleaut32.lib; uuid.lib; odbc32.lib; odbccp32.lib`

En ambas opciones se tilda `Inherit from parent or project defaults`

#### Configuración final
Debe quedar de la siguiente forma, teniendo en cuenta la ubicación local de las librerías en cada equipo.

__Configuratios properties__


1. _C/C++_->
	- Prepocessor->
	  - Preprocess to a file: NO
	- Precompiled Headers->
	  - Precompiled Header: Use (/Yc)
	  - Precompiled Header File: pch.h
2. *VC++ Directories*->
   - __*Include Directories:*__
     - C:\Repositories\opencv\build\include
     - C:\Repositories\libtorch\include
     - C:\Repositories\libtorch\include\torch\csrc\api\include
   - __*Library Directories:*__
     - C:\Repositories\opencv\build\x64\vc15\lib
     - C:\Repositories\libtorch\lib
[X] Inherit from parent or project defaults
3. *Linker*->*Input*->  
   - __*Additional Denpendencies:*__        
     - `opencv_world430d.lib`
	 - `torch_cpu.lib`
	 - `c10.lib`
	 
[X] Inherit from parent or project defaults
