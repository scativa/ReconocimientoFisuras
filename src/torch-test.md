# Torch hello world for VS2019
Contine un proyecto que utiliza pytorch con Visual Studio 2019 y Windows 10. Permite la pruba de librerías instaladas y propipiedades del proyecto.

## Testing

### Configuración
Windows 10 **Home x64 versión 1903**
Visual Studio Community 2019 16.5.1

PyTorch 
Build: ```Stable (1.4)```
Your SO: ```Windows```
Packge: ```LibTorch```
Language: ```C++/Java```
CUDA: ```None```

## Proyecto

### Nuevo proyecto
Template: ```Console App```

Copiar en la carpeta donde se encuetra el proyecto librerías dinámicas de pytorch en la carpeta del proyecto:
```xcopy C:\Repositories\libtorch\.dll %PATHTOPROJECT%\torch-test\torch-test\```

*Importante: No es necesario copiar los *.lib*

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
__Additional Denpendcies:__       
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


## Resultado

```
 0.3577  0.6588 -0.4557  0.2118 -0.0977  0.4034
 0.3433  0.9373  0.0186  0.1569  0.3913 -0.1046
 0.4254  0.0299 -0.3350  0.1844 -0.4758 -0.0110
 0.3136  0.4063 -0.2557  0.4275 -0.5561  0.7601
-0.7681  0.3214  0.1148  0.2971  0.4050 -0.7485
 0.0647  0.2939  0.1041  0.6941 -0.3225  0.3297
[ CPUFloatType{6,6} ]
Hello World!
Presione una tecla para continuar . . .
```
