# Torch Linux/Google Colab
Ejemplos para compilar, linkear y ejecutar torch en Linux (MINT/Ubuntu) y Google Colab

## LINUX

### Instrucciones
Partiendo de la carpeta raiz: ```./torch-test/``` o ```./example-app/``` según corresponda.
Se considera que las librerías torch están en ```/home/usuario/Repositories/libtorch```

### Compile, link y execute
```
mkdir build
cd build
cmake -DCMAKE_PREFIX_PATH=/home/usuario/Repositories/libtorch ..
cmake --build . --config Release
```

## GOOGLE COLAB

### Subir a Google Drive
Se debe subir la carpeta completa (```./torch-test/``` o ```./example-app/```) en la carpeta ```/Colab``` de *Google Drive*. Se muestra el ejemplo de ```./example-app```

Se debe copiar la carpeta del proyecto dentro del *Google Colab* desde el *Google Drive*. Esto se debe por problemas al referenciar carpetas con espacios como "*My Drive*", aunque se debería volver a comprobar esto.

```
%mkdir /content/example-app
%cp -r /content/drive/My\ Drive/Colab/example-app/* /content/example-app/
%mkdir /content/example-app/build
```

### Compile, link y execute
```
%cd  /content/example-app/build
%rm -r *
!cmake -DCMAKE_PREFIX_PATH="/content/libtorch" ..
!cmake --build . --config Release
!./example-app
```

## Testing
El resultado debería ser una salida similar a la siguiente:
```
 0.9234  0.5967  0.6285
 0.5452  0.0881  0.7094
[ CPUFloatType{2,3} ]
```


## Referencias

### Configuración de entorno
[Documentación de entorno](/docs/torch/README.md)

### Torch C++ en linux
[START LOCALL](https://pytorch.org/get-started/locally/)
[INSTALLING C++ DISTRIBUTIONS OF PYTORCH](https://pytorch.org/cppdocs/installing.html)


