# Entorno en Google Colab
Keywords: Pytorch, Google Colab, Google Drive

Instrucciones para generar el entorno de trabajo para *pytorch* en *Google Colab*.

## Paso a paso
No todos los pasos son necesarios. Descargas y copias dependen del estado de la Notebook Google Colab

### Conectar con Google Drive
```
from google.colab import drive
drive.mount('/content/drive')
```

### Crear entorno Drive
```
%cd /content/drive/My\ Drive
%mkdir Colab
```

### Descargar libtorch 
```
%cd /content/drive/My\ Drive/Colab
%mkdir download
%cd download
!wget https://download.pytorch.org/libtorch/cpu/libtorch-shared-with-deps-1.5.0%2Bcpu.zip
!unzip libtorch-shared-with-deps-1.5.0+cpu.zip -d /content
```

## Test
[Torch test proyects](/src/test/torch-test/linux/README.md)

## Notas
**Atención** con el uso de '!' y '%'

### Entorno
La versión de pytorch descargada se corresponde a una que ejecuta en CPU. Cambiar el nombre del archivo, tanto a descargar como al descomprimir según la versión deseada. [Ver](https://pytorch.org/get-started/locally/). 

## Referencias
(Google Colab: Tips para principiantes)[https://medium.com/marvik/google-colab-tips-para-principiantes-e39d6e7051d4]



















## OLD VERSION



### Instrucciones paso a paso 
- crear una nueva Notebook en Google Colab 
- instalar el pytorch a usar
- subir el código example-app.cpp
- compilarlo y ejecutarlo.

### 1) Preparar entorno
```
!wget https://download.pytorch.org/libtorch/cpu/libtorch-shared-with-deps-1.5.0%2Bcpu.zip
!unzip libtorch-shared-with-deps-1.5.0+cpu.zip
!mkdir example-app
%cd example-app
```

### 2) Subir código e instrucciones de compilación
Subir al directorio /content/example-app:
- ```example-app.cpp```
- ```CMakefiles.txt```

### 3) Compilación, build y ejecución
```
!mkdir build
%cd build
!cmake -DCMAKE_PREFIX_PATH=/content/libtorch ..
!cmake --build . --config Release
!./example-app
```

### Salida
El resultado debería ser una salida similar a la siguiente:
```
 0.9234  0.5967  0.6285
 0.5452  0.0881  0.7094
[ CPUFloatType{2,3} ]
```

### Notas
## Entorno
La versión de pytorch descargada se corresponde a una que ejecuta en CPU. Cambiar el nombre del archivo, tanto a descargar como al descomprimir según la versión deseada.
Según: https://pytorch.org/get-started/locally/. 
Configuración utilizada: [Documentación de entorno](/docs/Environment.md)

## Estructura de directorios
![Estructura del directorio en Google Colab](/docs/GoogleColab.png)

