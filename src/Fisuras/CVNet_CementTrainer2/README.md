# Cement Trainer
Entrena la red de los archivos del dataset y almacena los pesos sinápticos en un archivos.

### Input
El dataset es generado por otro programa que genera a partir de un lote clasificado de imágenes positivas y negativas. Los archivos por defecto son: `TRAIN_IMAGES.tensor`, `TRAIN_TARGET.tensor`,`TEST_IMAGES.tensor`, `TEST_TARGET.tensor`. Ver [CVNet_DatasetBuilder](ReconocimientoFisuras/src/Fisuras/CVNet_DatasetBuilder)

### Output
Al finalizar la ejecución se obtiene el archivo con los pesos sinápticos generados durante el entrenamiento. Por defecto en el archivo `model.pt`.

## Visual Studio - Windows 

## Linux

## Google Colab
Ver la preparación del entorno en [torch-install-GoogleColab.md](docs/torch/torch-install-GoogleColab.md)

### Google Drive a Colab
```
# Copia los dataset para entrenar y testear a /content
!mkdir /content/5y9wdsg2zt-1
!cp /content/drive/My\ Drive/Colab/5y9wdsg2zt-1/* /content/5y9wdsg2zt-1
```
```
# Copia el src a /content
!mkdir /content/CVNet_CementTrainer2
!mkdir /content/CVNet_CementTrainer2/build
!cp /content/drive/My\ Drive/Colab/CVNet_CementTrainer2/* /content/CVNet_CementTrainer2
```

### Build
```
# Compilación y build del código
%cd /content/CVNet_CementTrainer2/build
!cmake -DCMAKE_PREFIX_PATH=/content/libtorch ..
!cmake --build . --config Release
```
```
# Ejecutar el código
%cd /content/CVNet_CementTrainer2/build
!./CVNet_CementTrainer2 --verbose
```
## Referencias
Entorno Google Colab [torch-install-GoogleColab.md](/docs/torch/torch-install-GoogleColab.md)
Ejemplo PyTorch en Visual Studio, Linux y Google Colab: [torch-test](/src/test/torch-test/)
