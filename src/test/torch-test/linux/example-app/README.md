# Torch and CMakeList
[Combining CMakeLists.txt of Libtorch and CMakeLists.txt of ROS package](https://answers.ros.org/question/347885/combining-cmakeliststxt-of-libtorch-and-cmakeliststxt-of-ros-package/)

## General

### Entorno
```
folder/
    example-app.cpp
    CMakeLists.txt
```

### Build
```
mkdir build
cd build
cmake -DCMAKE_PREFIX_PATH=/absolute/path/to/libtorch ..
cmake --build . --config Release
```

## Google Colab

#!wget https://download.pytorch.org/libtorch/cu102/libtorch-shared-with-deps-1.5.0.zip
#!unzip libtorch-shared-with-deps-1.5.0.zip -d /content

#!wget https://download.pytorch.org/libtorch/cu92/libtorch-shared-with-deps-1.5.0%2Bcu92.zip
#!unzip libtorch-shared-with-deps-1.5.0+cu92.zip -d /content

!wget https://download.pytorch.org/libtorch/cu101/libtorch-shared-with-deps-1.5.0%2Bcu101.zip
!unzip libtorch-shared-with-deps-1.5.0+cu101.zip -d /content



### Entorno, Build y ejecución
Secuencia de comandos para ejecutar exampleGPU-app

```
from google.colab import drive
drive.mount("/content/drive")
```

```
%cd /content/drive/My\ Drive/Colab
%cd download
!unzip libtorch-shared-with-deps-1.5.0+cpu.zip -d /content
```

```
%mkdir /content/example-app
%cp -r /content/drive/My\ Drive/Colab/example-app/* /content/example-app/
%mkdir /content/example-app/build
```

```
%cd  /content/example-app/build
!cmake -DCMAKE_PREFIX_PATH="/content/libtorch" ..
!cmake --build . --config Release
!./exampleGPU-app
```

### GPU

GPU test in python
```python
import tensorflow as tf
tf.test.gpu_device_name()
```
Si el GPU está habilitado (ver Configuración de la Notebook -> Aceleración de Hardware) el resultado debería ser:
```
'/device:GPU:0'
```

Usando torch
```python
import torch
torch.cuda.set_device(0)
torch.cuda.is_available()
print(torch.version.cuda)
```
Si el GPU está habilitado (ver Configuración de la Notebook -> Aceleración de Hardware) el resultado debería ser:
```
True
10.1
```

[Google Colab Free GPU Tutorial - 3. Which GPU Am I Using?](https://medium.com/deep-learning-turkey/google-colab-free-gpu-tutorial-e113627b9f5d)
```python
from tensorflow.python.client import device_lib
device_lib.list_local_devices()
```python

## Referencias
[First, WTF is Google Colab?](https://jovianlin.io/pytorch-with-gpu-in-google-colab/)

[Programmming PyTorch for Deep Learning](https://books.google.com.ar/books?id=udCwDwAAQBAJ&pg=PA156&lpg=PA156&dq=enable+gpu+google+colab+pytorch+cpp&source=bl&ots=ImnBsdKXw7&sig=ACfU3U34Fu9qVBjQORuFO_u2PQ7ZP9Iqtw&hl=es-419&sa=X&ved=2ahUKEwjGjvPK3cPpAhVzKLkGHRKUAbYQ6AEwDHoECAoQAQ#v=onepage&q=enable%20gpu%20google%20colab%20pytorch%20cpp&f=false)

