# Google Colab

## Ejemplos
[src/test/torch-test/linux/](src/test/torch-test/linux/README.md)

## Implementaciones
[CementTrainer2](/src/Fisuras/CVNet_CementTrainer2/README.md)

[First, WTF is Google Colab?](https://jovianlin.io/pytorch-with-gpu-in-google-colab/)

## Recomendaciones
- Se recomienda copiar la carpeta del proyecto dentro del *Google Colab* desde el *Google Drive*. Esto se debe por problemas al referenciar carpetas con espacios como "*My Drive*", aunque se debería volver a comprobar esto.
- **Atención** con el uso de '!' y '%'

## Subir archivos
Como subir los archivos al Google Drive 

### Drivesync$ 
```
$ sudo apt install ruby ruby-bundler
$ cd github/
$ git clone https://github.com/MStadlmeier/drivesync.git
$ cd drivesync/
```

```
$ bundle install
$ sudo gem install bundler
$ bundle install
```

```ruby
$ ruby drivesync.rb
```

```
crontab -e
```
Agregar la línea
```
*/1 * * * * ruby /path/to/drivesync/drivesync.rb
```


[Drivesync - Github](https://github.com/MStadlmeier/drivesync)
[DriveSync – Easy way to Sync files between local and Google Drive from Linux CLI](https://www.2daygeek.com/drivesync-google-drive-sync-client-for-linux/)



## Referencias
[Google Colab: Tips para principiantes](https://medium.com/marvik/google-colab-tips-para-principiantes-e39d6e7051d4)
[Uso de GPU](docs/GPU)
[Configuración de entorno para Pytorch](/docs/torch/README.md)

[First, WTF is Google Colab?](https://jovianlin.io/pytorch-with-gpu-in-google-colab/)
