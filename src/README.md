# Desarrollo para detectar fisuras
Código fuente del desarrollo con sus versiones y enfoque y sus ensayos preliminares

## Index
*/clasificador:* Proyecto que a partir de una imágene y su copia marcada la subdvide en positivos y negativos (con o sin fallas)

*/MNIST:*: Ensayo de NN con las bases de MNIST

*/Fisuras*: Proyecto ya dedicado a la clasificación de fisuras.

*/Fisuras (version inicial de martín).rar*: Versión inicial de *Fisuras* generado por martín. 

*/FisurasSegmentation*: Implemntacion de una red de segmentación (tiramisu) para detectar las fisuras


### Configuración para Visual Studio
Informción desactualizada. 
Usar como fuente más confiable la documentación y test del repositorio Github [dev-tools](https://github.com/scativa/dev-tools)

**Solution Fisuras.sln**

Solution Configuration: ```Release```
Solution Plataform: ```x64```

*Configuratios properties*->

	C/C++ Directories->
  
		Include Directories:
      C:\opencv\build\include
			C:\Repositories\libtorch\include\torch\csrc\api\include
			C:\Repositories\libtorch\include

		Library Directories:
			C:\Repositories\libtorch\lib
		
	Linker->
		Additional Library Directories:
			C:\Repositories\libtorch\lib
			C:\opencv\build\x64\vc15\lib
      
    Input->  
		  Additional Denpendcies:       
        opencv_world420.lib ó opencv_world430.lib
        c10.lib
		torch.lib ó torch_cpu.lib ó torch_gpu.lib

