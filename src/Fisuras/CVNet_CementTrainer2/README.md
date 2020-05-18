#

## Google Colab
Ver la preparación del entorno

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

```
%cd /content/CVNet_CementTrainer2/build
!cmake -DCMAKE_PREFIX_PATH=/content/libtorch ..
!cmake --build . --config Release

```
# Ejecutar el código
%cd /content/CVNet_CementTrainer2/build
!./CVNet_CementTrainer2 --verbose
```

