# Environment
Librerías utilizadas, configuración e instalación

### REVISAR Y COMPATIBILIZAR CON EL README DE SRC/TORCH-TEST
### REVISAR NOMBRE TAMIBÉN

## PyTorch
### Install
Download: [PyTorch](https://pytorch.org/get-started/locally/)

#### Windows
PyTorch Build: ```Stable (1.4)```

Your SO: ```Windows```

Packge: ```LibTorch```

Language: ```C++/Java```

CUDA: ```None```

#### Linux
PyTorch Build: ```Stable (1.5)```

Your SO: ```Linux```

Packge: ```Pip```

Language: ```C++/Java```


### Windows - Visual Studio 2019
Template: ```Console App```

Copiar en la carpeta donde se encuetra el proyecto librerías dinámicas de pytorch en la carpeta del proyecto:
```xcopy C:\Repositories\libtorch\.dll %PATHTOPROJECT%\torch-test\torch-test\```
Para este projecto específico sólo se están precisando: ```c10.dll``` ```torch.dll``` ```libiomp5md.dll```

Para no tener que realizar la copia DLL se debe agregar la variable de entorno de windows PATH el camino a la librería (ej. C:\Repositories\libtorch\lib). 

Opencv utiliza este modalidad [+ ver más detalles](/docs/opencv/OpenCV-Install-Windows.md). 
Tiene la ventaja de no andar moviendo para compartir el proyecto, ni duplicando DLL en cada proyecto. Evita ocupar espacio y hacer pesada la solución y simplifica una actualización de DLL.

Si no se modifica la variable de entorno PATH es preciso copiar en la carpeta donde se encuetra el proyecto librerías dinámicas de pytorch en la carpeta del proyecto: ```xcopy C:\Repositories\libtorch\*.dll %PATHTOPROJECT%\torch-test\torch-test\```
Para este projecto específico sólo se están precisando: ```c10.dll``` ```torch.dll``` ```libiomp5md.dll```

__Importante__: No es necesario bajo ningún motivo copiar los ```.lib``` 

### Configuración
Configuration manager: 
Solution Configuration: ```Release```
Active solution plataform: ```x64```

*Configuratios properties*->

__C/C++ Directories->__

__Include Directories:__
* ```C:\Repositories\libtorch\include\torch\csrc\api\include```
* ```C:\Repositories\libtorch\include```

__Library Directories:__
* ```C:\Repositories\libtorch\lib```

__Input->__  
__Additional Denpendencies:__       
* ```c10.lib```
* ```torch.lib```

*Nota: Para este ejemplo __no__ es necesario ni copiar ni agregar a las dependencias el resto de las librería, pero puede ser necesario para otros*
* ```caffe2_module_test_dynamic.lib```
* ```clog.lib```
* ```cpuinfo.lib```
* ```libprotobuf.lib```
* ```libprotobuf-lite.lib```
* ```libprotoc.lib```


### Notas:
1. Se considera que la librería de pytorch está ubicada en ```C:\Repositories\libtorch```

CUDA: ```None```

Run this Command: ```pip install torch==1.5.0+cpu torchvision==0.6.0+cpu -f https://download.pytorch.org/whl/torch_stable.html```


#### Google Colab
PyTorch Build: ```Stable (1.5)```

Your SO: ```Linux```

Packge: ```LibTorch```

Language: ```C++/Java```

CUDA: ```None```

Run this Command:
```
Download here (Pre-cxx11 ABI):
https://download.pytorch.org/libtorch/cpu/libtorch-shared-with-deps-1.5.0%2Bcpu.zip

Download here (cxx11 ABI):
https://download.pytorch.org/libtorch/cpu/libtorch-cxx11-abi-shared-with-deps-1.5.0%2Bcpu.zip
```

