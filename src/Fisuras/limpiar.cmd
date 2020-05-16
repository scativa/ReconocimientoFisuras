@echo off
echo ========================================
echo Se borraran todos los archivos que no son fuentes del proyecto y subdirectorios en:
CD
echo ========================================
echo Oprima ctrl+C para detener o...
pause
del /F /S /Q .\x64\*.*
del /F /S /Q .\.vs\*.*
del /F /S /Q .\CVNet_Cement\x64\*.*
del /F /S /Q .\Visualizacion_Fracturas\x64\*.*
del /F /S /Q .\CVNet_DatasetBuilder\x64\*.*
del /F /S /Q .\CVNet_CementTrainer2\x64\*.*

echo ========================================
echo Limpieza realizada
echo ========================================
pause
