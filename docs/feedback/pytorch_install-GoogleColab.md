# Entorno en Google Colab
Keywords: Pytorch, Google Colab, Google Drive

[Ver ejemplo](/src/test/torch-test/linux/)

Generar el entorno para trabajar con pytorch.

## Paso a paso
No todos los pasos son necesarios. Descargas y copias dependen del estado de la Notebook Google Colab

## Entorno 

### Conectar con google drive
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


