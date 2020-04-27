# Ejecutar en Google Colab
Subir el código de pytorch en cpp y ejecutarlo compilado.

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

