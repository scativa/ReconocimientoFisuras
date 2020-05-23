# GPU

## Testing
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
```python
from tensorflow.python.client import device_lib
device_lib.list_local_devices()
```

## Referencias
[Google Colab Free GPU Tutorial - 3. Which GPU Am I Using?](https://medium.com/deep-learning-turkey/google-colab-free-gpu-tutorial-e113627b9f5d)
