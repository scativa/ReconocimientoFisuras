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
Ver **Anexo I**




## Referencias
[Google Colab: Tips para principiantes](https://medium.com/marvik/google-colab-tips-para-principiantes-e39d6e7051d4)

[Uso de GPU](docs/GPU)

[Configuración de entorno para Pytorch](/docs/torch/README.md)

[First, WTF is Google Colab?](https://jovianlin.io/pytorch-with-gpu-in-google-colab/)

### Referencias Drivesync
[Drivesync - Github](https://github.com/MStadlmeier/drivesync)

[DriveSync – Easy way to Sync files between local and Google Drive from Linux CLI](https://www.2daygeek.com/drivesync-google-drive-sync-client-for-linux/)

[Rsync (Remote Sync): 10 Practical Examples of Rsync Command in Linux](https://www.tecmint.com/rsync-local-remote-file-synchronization-commands/)

## Anexo I
Ejemplo de Daniel Chispa Sanchez usando Drivesync

```sh
# nombre: alanube.sh
# usando el programa rsync hago un bkup cada media hora de la carpeta de la tesis 
# y la mando a mi google drive


#SCRIPT A LA NUBE
# dir script ---- /usr/local/bin/alanube.sh
# usando el programa rsync hago un backup (programado cada media hora) de los que estuve trabajando en la tesis. 
# actualiza los últimos cambios en la carpeta sincronizada con el google drive con el programa ruby
#usuario: XXXX@gmail.com

#!/bin/bash

# hago el backup en la cumpu en la carpeta drive
# sincronizo la carpeta donde tengo los programas del micro (del AVR que uso en wine) y los pongo en el directorio de la tesis
rsync -avh --delete --exclude '/LTspiceXVII/' /home/daniels/.
wine/drive_c/users/daniels/Mis\ Documentos/ /home/daniels/FIUBA/tesis\ SPS/Programas/

# sincronizo la carpeta de la tesis en la carpeta que subo al drive
rsync -avh --delete /home/daniels/FIUBA/ /home/daniels/Documents/drive/FIUBA/

# envio los datos a la nube - drive de la cuenta de gmail -
ruby /home/daniels/drivesync/drivesync.rb
```

