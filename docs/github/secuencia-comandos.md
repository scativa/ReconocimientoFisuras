# Secuencia de comandos GITHUB
Secuencia de comandos standar para actualizar la copia local de git hub, generar un branch y subirlo

### Extracto de:
https://gist.github.com/blackfalcon/8428401

#### Al comenzar me pongo al día
```
$ git branch
$ git checkout master
$ git pull origin master
```


*Cuando empiezo un nuevo branch, copia del master en este caso*
```
$ git checkout -b my-new-feature-branch
```

*Luego de agregar, sacar o mover archivos*
```
$ git add --all
$ git commit -m "fixed bug with login feature"
$ git push origin my-new-feature-branch
```


```
$ git checkout master         /* ensure you are on the master branch
$ git pull                                   /* pull the latest from the remote 
$ git checkout my-feature-branch      /* checkout the feature branch
$ git push origin my-feature-branch  /* update your copy in the repo
$ git rebase master              /* rebase on the master branch
$ git push origin my-feature-branch --force   /* force update the remote
```

### Ejemplo secuencias hechas (Seba) para mover unos documentos
Casi lo mismo que lo anterior pero probado

1. Empiezo por bajar lo que hay en el master de servidor*
```
$ git branch
$ git checkout master
$ git pull origin master
```

2. Genero un nuevo branch para trabajar y me paso a al nuevo branch
```
$ git branch organizando-doc
$ git checkout organizando-doc
```

3. Trabajo con los archivos y la estructura de la carpeta: Copio, muevo y borro archivos y carpetas según lo quiera organizar

4. Cuando termino agrego todo al branch y hago el commit
```
$ git add --all /* agrega las modificaciones al index
$ git commit -m "organizando documentacion de martin" /* No me queda claro que es exactamente lo que hace el commit, ya que no lo sube a GitHub.
$ git push origin organizando-doc /* sube al github el branch
```

5. Vuelvo a actualizar el master para estar seguro (no sé por qué usa "rebase" y no "pull origin")...
```
$ git rebase master
$ git push origin organizando-doc --force /* y lo fuerzo a subir (no lo había hecho en el comando anterior??)
```

6. Después desde la página hago el pull request y el merge. En este caso sin esperar la respuesta al pull ya que no hay conflictos

##### Para borrar y actualizar branches remotos
```
git branch -a
git remote update origin --prune
git remote prune origin
git branch -d add-trainingimages-seba
```
