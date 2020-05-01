# Fuentes de los proyectos #

*/test:* Proyectos de pruebas varias, generalmente "hello world" (opencv, torc, procompiled header, etc...)

*/clasificador:* Proyecto que a partir de una imágene y su copia marcada la subdvide en positivos y negativos (con o sin fallas)

*/Fisuras*: Proyecto ya dedicado a la clasificación de fisuras. Actualmente es la vesión modificada por Seba (branch *datasets_generation* al 1-may-2020

*/Fisuras (version inicial de martín).rar*: Versión inicial de *Fisuras* generado por martín. 

*/MNIST:*: Ensayo de NN con las bases de MNIST


# Building #
## Solution Fisuras.sln ##

Solution Configuration: ```Release```
Solution Plataform: ```x64```

## MLP_TORCH_con_librerías ##


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
        opencv_world420.lib
        c10.lib
        caffe2_module_test_dynamic.lib
        clog.lib
        cpuinfo.lib
        libprotobuf.lib
        libprotobuf-lite.lib
        libprotoc.lib;torch.lib

