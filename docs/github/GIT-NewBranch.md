## Subiendo un nuevo branch local a GitHub

### push --set-upstream
Uso: 
```
$git push --set-upstream origin <branch_a_subir>
```
y más genericament:
```
git branch --set-upstream-to=origin/<branch> <branch_a_subir>
```

### Ejemplo
Intentos utilizando un nuevo branch: ejemplo *test_linux_compile*

Se muestra la sucesión de pruebas hasta llegar al comando ```$git push --set-upstream origin test_linux_compile```.

```
$ git branch
  master
  old-MINST-folder-organization
  test_linux_compile
```

Intento traer la información desde github estando en el branch local que no existe en GitHub...
```
$ git pull origin
You asked to pull from the remote 'origin', but did not specify
a branch. Because this is not the default configured remote
for your current branch, you must specify a branch on the command line.

git pull
There is no tracking information for the current branch.
Please specify which branch you want to merge with.
See git-pull(1) for details.

    git pull <remote> <branch>

If you wish to set tracking information for this branch you can do so with:

    git branch --set-upstream-to=origin/<branch> test_linux_compile
```
... y lo rechaza diciendo que el branch no está sigendo seguido (track).


Tal como sugiere, le indico (en dos intentos) que siga el branch local ```test_linux_compile``` por el remoto de igual nombre...

```
$git branch --set-upstream-to=origin/test_linux_compile test_linux_compile
error: the requested upstream branch 'origin/test_linux_compile' does not exist
hint: 
hint: If you are planning on basing your work on an upstream
hint: branch that already exists at the remote, you may need to
hint: run "git fetch" to retrieve it.
hint: 
hint: If you are planning to push out a new local branch that
hint: will track its remote counterpart, you may want to use
hint: "git push -u" to set the upstream config as you push.
```

```
$ git push -u
fatal: The current branch test_linux_compile has no upstream branch.
To push the current branch and set the remote as upstream, use

    git push --set-upstream origin test_linux_compile
```

... y lo vuelve a rechazar diciendo que ```test_linux_compile``` no existe como remoto.

Ahora le indico que suba el branch y que lo cree en Github (origin). 
```
$git push --set-upstream origin test_linux_compile

Counting objects: 64, done.
Delta compression using up to 4 threads.
Compressing objects: 100% (61/61), done.
Writing objects: 100% (64/64), 266.11 KiB | 3.09 MiB/s, done.
Total 64 (delta 19), reused 0 (delta 0)
remote: Resolving deltas: 100% (19/19), completed with 3 local objects.
remote: 
remote: Create a pull request for 'test_linux_compile' on GitHub by visiting:
remote:      https://github.com/scativa/ReconocimientoFisuras/pull/new/test_linux_compile
remote: 
To https://github.com/scativa/ReconocimientoFisuras
 * [new branch]      test_linux_compile -> test_linux_compile
Branch 'test_linux_compile' set up to track remote branch 'test_linux_compile' from 'origin'.
```
Este comando funcionó a la perfección.


