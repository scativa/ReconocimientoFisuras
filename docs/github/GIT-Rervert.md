# Revert to previous status
Cómo revertir cambios a un estado de commit anterior. En este caso modifiqué archivos que no quería hacer (no al menos en el ```branch master```)
En las referencias hay una explicación interesante del comando  ```rebase```.

## Reset
Considerar lo comando alternativo ```revert``` y las opciones para ```reset```: ```hard```,  ```soft``` y ```mixed```.
Los archivos ```CVNet_CementTrainer2.vcxproj``` y ```pch.h``` fueron modificados. Todavía no fueron pasados al ```stage area```.
```
D:\github\ReconocimientoFisuras>git status
On branch master
Your branch is up to date with 'origin/master'.

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   src/Fisuras/CVNet_CementTrainer2/CVNet_CementTrainer2.vcxproj
        modified:   src/Fisuras/CVNet_CementTrainer2/pch.h

no changes added to commit (use "git add" and/or "git commit -a")
```

Muestra el log para buscar el hash del último commit: ```9b93e8```
```
D:\github\ReconocimientoFisuras>__git log --oneline_
__9b93e8__ (src_CEMENT) Separacion de Generador de Datasets (CVNet_DatasetBuilder) y Entrenado (CVNET_CementTrainer) Esta funcionando el precompiled header (suele fallar al incorporar proyectos) CementTrainer2 sin "windows-h" Comando batch de limpieza de archivos de VS (limpiar.cmd)
01a0424 Update PrecompiledHeaders.md
ff5feeb 16may Comienzo de trabajo: Crear CementTrainer
c2ac27d eand
6ad26c7 Update torch-env.md
```

Ejecuto el comando ```git reset hard``` (vero las opciones de ```soft``` y ```mixed```) para volver __todo__ al punto de commit ```3f9ca88```
```
D:\github\ReconocimientoFisuras>git reset --hard 3f9ca88
HEAD is now at 3f9ca88 Merge branch 'src_CEMENT'
```

Compruebo con ```git status``` que volvió al punto anterior
```
D:\github\ReconocimientoFisuras>git status
On branch master
Your branch is up to date with 'origin/master'.

nothing to commit, working tree clean
```

## Referencias
[How to reset, revert, and return to previous states in Git](https://opensource.com/article/18/6/git-reset-revert-rebase-commands)
