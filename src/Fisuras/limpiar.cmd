@echo off
echo Borraran todos los archivos que no son fuentes del proyecto y subdirectorios en:
CD
echo
echo ctrl+C para detener u otra tecla para continuar.
pause
del /F /S /Q .\x64\*.*
del /F /S /Q .\.vs\*.*
del /F /S /Q .\CVNet_Cement\x64\*.*
del /F /S /Q .\Visualizacion_Fracturas\x64\*.*
del /F /S /Q .\CVNet_DatasetBuilder\x64\*.*
del /F /S /Q .\CVNet_CementTrainer\x64\*.*

echo Limpieza realizada
pause
