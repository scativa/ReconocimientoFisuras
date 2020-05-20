# Branches remotos
[3.5 Git Branching - Remote Branches](https://git-scm.com/book/id/v2/Git-Branching-Remote-Branches)

## Fetch
> To synchronize your work, you run a ```git fetch origin``` command. This command looks up which server “origin” is, fetches any data from it that you don’t yet have, and updates your local database, moving your ```origin/master``` pointer to its new, more up-to-date position.
> It’s important to note that when you do a fetch that brings down new remote branches, you don’t automatically have local, editable copies of them. In other words, in this case, you don’t have a new ```serverfix``` branch – you only have an ```origin/serverfix``` pointer that you can’t modify.

## Branches remotos

### Bajar branches remotos que no están locales
Ejemplo para seguir (track) localmente el branch remoto `test_linux_compile`

Listo branches remotos
```
$ git branch -r
  origin/HEAD -> origin/master
  origin/master
  origin/test_linux_compile
```
Lo asocio con uno local (en este caso con el mismo nombre)
```
$ git checkout -b test_linux_compile origin/test_linux_compile
Switched to a new branch 'test_linux_compile'
Branch 'test_linux_compile' set up to track remote branch 'test_linux_compile' from 'origin'.
```
Listo branches locales
```
$ git branch
  master
* test_linux_compile
```

### Para borrar y actualizar branches remotos
Ejemplo para borrar `add-trainingimages-seba`
```
git branch -a
git remote update origin --prune
git remote prune origin
git branch -d add-trainingimages-seba
```

## Pull
> While the ```git fetch``` command will fetch down all the changes on the server that you don’t have yet, it will not modify your working directory at all. It will simply get the data for you and let you merge it yourself. However, there is a command called ```git pull``` which is essentially a ```git fetch``` immediately followed by a git merge in most cases. 




