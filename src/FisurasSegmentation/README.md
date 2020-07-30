# Fisuras Segmentation
Implementación de una red de segmentación para detección de fisuras

Se partió del projecto *Segementation* que realiza todas las operación, desde las imágenes originales hasta el entrenamiento y visualzación.

Luego se modularizó con entradas y salidas de cada módulo para bajar la complejidad. Entre otras cosas permite el entrenamiento en Google Colabs sin utilizar las librerías OpenCV.

Durante la modularización se realizaron cambios en la implementación documentadas aparte.

### Segmentation
Proyecto original completo. Realiza todas las etapas de los módulos que se describen a continuación
### SerializeMod
Parte de las imágenes crudas, las procesa y serializa.

Input: Folder_with_RAW_pictures ("C:/Users/User/Proyectos/data/Samples_Segmentation")

Output: Folder_with_Procceced_pictures ( "C:/Users/User/Proyectos/data/Segmentation")

### tensorfilesMod
A partir de las imágenes serializadas genera los archivos .tensor para el entrenamiento.

Input: Folder_with_Procceced_pictures ("C:/Users/User/Proyectos/data/Segmentation")

Output: Archivos .tensor. ("C:/Users/User/Proyectos/data/Segmentation/IMG.tensor" y "C:/Users/User/Proyectos/data/Segmentation/MASK.tensor")

### TrainingMod
Entrena la red utilizando los tensores y genera el archivo con los pesos sinápticos

Input: Archivos .tensor. ("C:/Users/User/Proyectos/data/Segmentation/IMG.tensor" y "C:/Users/User/Proyectos/data/Segmentation/MASK.tensor")

Output: Model ("model.pt")

### VisualizeMod
Utilizad los pesos sinápticos del entrenamiento ("model.pt") para analizar todas las imágenes de la carpeta indicada.

Input: Folder_with_JPGs ("C:/Users/User/Proyectos/data/Positive")

Output: Visualización partida de las imágenes analizadas y su resultado con las fracturas detectadas marcadas.

## Notas
- OptCmdLine: Librería desarrollada para los argumentos por línea de comandos
- /commons/globals.cpp: Variables globales al proyectos y los archivos de los mismos. Actualmente se usa `verbose_mode`
- 
