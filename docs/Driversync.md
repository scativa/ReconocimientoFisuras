# Drivesync

Sincroniza con google drive. Lo utilizamos para subir código al drive y luego a usarse en colab.

## Comandos
Revisasr bien estos comandos ya que hubo varios intentos antes de que funcionen
```
cd .drivesync/
ruby drivesync.rb config
xedit config.yml 
sudo apt install ruby ruby-bundler
cd github/
git clone https://github.com/MStadlmeier/drivesync.git
cd drivesync/
sudo gem install bundler
sudo bundle install
bundle --version
bundle-update
gem install bundler
sudo gem install bundler
bundle install
ruby drivesync.rb
4/0QHA6wXOE5MiWbgih9M2m4_klPMNyRsoW2mrsRSHmp3-So9nks6K3-8
crontab -e
ruby drivesync.rb
ruby drivesync.rb reset
```

## Notas
No sincroniza archivos de google.

## Referencias
[drivesync - 2daygeek](https://www.2daygeek.com/drivesync-google-drive-sync-client-for-linux/)

[Rsync (Remote Sync): 10 Practical Examples of Rsync Command in Linux](https://www.tecmint.com/rsync-local-remote-file-synchronization-commands/) 

[Driversync - Github](https://github.com/MStadlmeier/drivesync)

https://www.2daygeek.com/drivesync-google-drive-sync-client-for-linux/


## Archivos

### todrive
Batch que
```
rsync -avh --delete ./ ~/DrivesyncColabSrc/Colab/src/CVNet_CementTrainer2/ 
ruby ~/github/drivesync/drivesync.rb
```

### ~/drivesinc/config.yml

Modificaciones del Original:

`update_conflict_strategy: keep_local`. El sentido de transmisión para este uso es PC->GoogleDrive
`inclusion: whitelist` y `whitelist: [Colab/src/*]`. Trabaja (sincroniza) sólo la carpeta con las funtes para google colab.

``` 
#Path for your local drive folder (absolute path)
drive_path: "~/DrivesyncColabSrc"

#If true, files that have been deleted locally will also be deleted on drive
#Default: true
allow_remote_deletion: true

#Determines what will be done if a file has been edited locally and remotely
#keep_latest => Syncs whichever version has been edited last (default)
#keep_remote => Downloads the remote version and overwrites local changes
#keep_local =>  Uploads the local version and overwrites remote changes
#ignore => Does nothing and keeps both versions
#default: update_conflict_strategy: keep_latest
update_conflict_strategy: keep_local


#Timeout threshold for the service in seconds. If a request takes longer
#than this, it will be cancelled. You might want to increase this if you
#have to transfer large files
#Default: 1200
timeout: 1200

#Number of times the service will retry requests
#Default: 1
retries: 1

#Largest file size in megabytes that this program will handle. Anything 
#larger than this will be ignored. Be careful about increasing this value
#as resumable upload has not been implemented yet. If you have to sync 
#large files you may also need to increase the timeout threshold
#Default: 512
max_file_size: 512

#Determines which files will be synced.
#blacklist => Every file except those included in 'blacklist' below will
#be syced (default)
#whitelist => Only files included in 'whitelist' will be synced
#Original inclusion: blacklist
inclusion: whitelist

#White and blacklist contain file paths relative to Drive root. Which will
#(whitelist) / won't (blacklist) be synced.
#Globs [https://en.wikipedia.org/wiki/Glob_(programming)] are allowed
#Examples: blacklist: ["foo.bar","secret_*.txt","hidden/docs/*"] / whitelist: ["sync/*", "logs.tar.gz"]

blacklist: []
whitelist: [Colab/src/*]

#If true, files that have been shared with you will be synced as well, 
#as long as you added them to your Drive
#Default: false
sync_shared_in_drive: true

#If true, symlinks inside your local drive folder will be followed
#Default: false
follow_symlinks: false

config_version: 1.3
```
