# Changelog
Registro de los cambios más importantes del proyecto

## 22/07/2020 - Modificaciones a la versión inicial
1. Separación entre directorios, uso de `/` en lugar de `\\` dado que sirvte tanto para Windows como para Linux y es posible utilizarlos mezclados.
2. Uso de la macro `_WIN64` para saber si se está compilando en Visual Studio para Windows.
3. Uso de argumentos por línea de comandos para evitar la recompilación y poder ejecutar de línea de comandos. Se utiliza la librería [CmdLineOpt](https://github.com/scativa/cmdlineopt)
4. Problemas precompilación de headers. Se corrigió la configuración del PCH. [Anexo I](./Changelog-Anexos.md#4-problemas-precompilaci%C3%B3n-de-headers)
5. Librerías. Limpieza de librerías e includes. Actualización a versiones nuevas de OpenCV y libtorch. [Anexo I](./Changelog-Anexos.md#5-librer%C3%ADas)

## Modularización
Se partió del projecto *Segementation* que realiza todas las operación, desde las imágenes originales hasta el entrenamiento y visualzación. Cada módulo trabaja con con entradas y salidas para bajar la complejidad. Entre otras cosas permite el entrenamiento en Google Colabs sin utilizar las librerías OpenCV.

### Módulos
- SerializeMod
- tensorfilesMod
- TrainingMod
- VisualizeMod

### Archivos comunes
- Se utiliza la carpeta `./common/` con archivos que comparten código, macros y variables globales entre los distintos módulos. Actualmente usa la variable global `verbose_mode`.
- Queda por implementar el uso compartido de `Net.h` y `Tiramisu.h` entre los módulos de entrenamiento y visualización. Hay un problema con el `pch.h` que utiliza cada uno, ya que el primero no incluye las librerías de OpenCV y el segundo sí.
- También hay que ver del uso común de `Config.h` o su eliminación si es que no queda configuración común. Eso puede pasar si se parametriza por línea de comando en general y los de la red queda solucionada en el punto anterior.


