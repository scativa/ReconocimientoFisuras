# Torch C++ en linux
START LOCALL
https://pytorch.org/get-started/locally/

INSTALLING C++ DISTRIBUTIONS OF PYTORCH
https://pytorch.org/cppdocs/installing.html

### Instrucciones
Partiendo de la carpeta raiz: ```./torch-test/``` o ```./example-app/``` según corresponda.
Se considera que las librerías torch están en ```/home/usuario/Repositories/libtorch```

```
mkdir build
cd build
cmake -DCMAKE_PREFIX_PATH=/home/usuario/Repositories/libtorch ..
cmake --build . --config Release
```

## Configuración de entorno
Ver: [Documentación de entorno](/docs/Environment.md)
