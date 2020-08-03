# Fisuras Segmentation
Implementación de una red de segmentación para detección de fisuras

Se partió del projecto *Segementation* que realiza todas las operación, desde las imágenes originales hasta el entrenamiento y visualzación.

Luego se modularizó con entradas y salidas de cada módulo para bajar la complejidad. Entre otras cosas permite el entrenamiento en Google Colabs sin utilizar las librerías OpenCV.

Durante la modularización se realizaron cambios en la implementación documentadas aparte.

### Segmentation
Proyecto original completo. Realiza todas las etapas de los módulos que se describen a continuación
### SerializeMod
Parte de las imágenes crudas, las procesa y serializa.

**Entrada**: `Folder_with_RAW_pictures` (ej. *C:/Users/User/Proyectos/data/Samples_Segmentation*)

**Resultado**: `Folder_with_Procceced_pictures` (ej. *C:/Users/User/Proyectos/data/Segmentation*)

### tensorfilesMod
A partir de las imágenes serializadas genera los archivos .tensor para el entrenamiento.

**Entrada**: `Folder_with_Procceced_pictures` (ej. *C:/Users/User/Proyectos/data/Segmentation*)

**Resultado**: Archivos `.tensor`. (ej. *C:/Users/User/Proyectos/data/Segmentation/IMG.tensor* y *C:/Users/User/Proyectos/data/Segmentation/MASK.tensor*)

### TrainingMod
Entrena la red utilizando los tensores y genera el archivo con los pesos sinápticos

**Entrada**: Archivos `.tensor`. (ej. *C:/Users/User/Proyectos/data/Segmentation/IMG.tensor* y *C:/Users/User/Proyectos/data/Segmentation/MASK.tensor*)

**Resultado**: Model (ej. `model.pt`)

### VisualizeMod
Utilizad los pesos sinápticos del entrenamiento `model.pt` para analizar todas las imágenes de la carpeta indicada.

**Entrada**: `Folder_with_JPGs` (ej. *C:/Users/User/Proyectos/data/Positive*)

**Resultado**: Visualización partida de las imágenes analizadas y su resultado con las fracturas detectadas marcadas.

## Librerías
### OptCmdLine
Librería desarrollada para los argumentos por línea de comandos [link en Github](https://github.com/scativa/cmdlineopt).

### Libtorch
Versiones 1.4 y 1.5. Detalles, instalación y configuración consultar en el proyecto [dev-tools - Github](https://github.com/scativa/dev-tools)
- [Documentación - Github](https://github.com/scativa/dev-tools/tree/master/docs/torch) 
- [Test src - Github](https://github.com/scativa/dev-tools/tree/master/src/torch-test)
### OpenCV
Versiones 4.20 y 4.30. Detalles, instalación y configuración consultar en el proyecto [dev-tools - Github](https://github.com/scativa/dev-tools)
- [Documentación - Github](https://github.com/scativa/dev-tools/tree/master/docs/opencv) 
- [Test src - Github](https://github.com/scativa/dev-tools/tree/master/src/opencv-test)

## Notas

**Archivos comunes**
- _../commons/globals.cpp_: Variables globales al proyectos y los archivos de los mismos. Actualmente se usa `verbose_mode`.
- _./pch.h_: Header precopilado. **Nota**: Cambia según el módudo ya que no todos utilizan las mismas librerías.
- _./Config.h_: Configuraciones del módulo. Ver cómo unificarlo en el futuro y reducir todo lo que se pueda a línea de comandos.
