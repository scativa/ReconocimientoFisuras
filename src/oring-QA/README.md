# O-Ring QA Test
Verfica el cumplimento de calidad de los o-rings de goma

```
## LINUX

### Compile and build
```
mkdir build
cd build
cmake -D OpenCV_DIR=/home/seba/opencv/build ..
cmake --build . --config Release
```

### Test
```
./test-top
```
En la cosola:
```
```


## GOOGLE COLAB
### Subir a Google Drive
Se debe copiar la carpeta del proyecto dentro del *Google Colab* desde el *Google Drive*. Esto se debe por problemas al referenciar carpetas con espacios como "*My Drive*", aunque se debería volver a comprobar esto.

### Compile, link y execute
```
### Testing
```

## Ejemplos y datos

### Morfología Matemática
[Labeling - OpenCV](https://answers.opencv.org/question/120698/drawning-labeling-components-in-a-image-opencv-c/)



### CUDA
[Makefiles with CUDA - Github](https://gist.github.com/kosongduadua/716b18362ad1a1053004)
https://medium.com/@bnarasapur/compile-opencv-with-cuda-from-the-source-1b98e9108a59
https://www.nvidia.com/docs/IO/116711/sc11-cuda-c-basics.pdf

```
cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D WITH_CUDA=ON -D ENABLE_FAST_MATH=1 -D CUDA_FAST_MATH=1 -D WITH_CUBLAS=1 -D INSTALL_PYTHON_EXAMPLES=ON -D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib-3.4.0/modules -D BUILD_EXAMPLES=ON -DBUILD_opencv_cudacodec=OFF ..
```



## Referencias
#### OpenCV Morfología matemática
https://docs.opencv.org/3.4/examples.html
https://docs.opencv.org/2.4/doc/tutorials/imgproc/threshold/threshold.html
https://docs.opencv.org/3.4/df/d5e/samples_2cpp_2tutorial_code_2ImgProc_2Morphology_1_8cpp-example.html
https://docs.opencv.org/3.4/d3/dbe/tutorial_opening_closing_hats.html
#### Librbos 
https://la.mathworks.com/academia/books/digital-image-processing-using-matlab-gonzalez.html
#### CUDA
https://docs.opencv.org/2.4/modules/gpu/doc/gpu.html
https://docs.opencv.org/2.4/modules/gpu/doc/introduction.html
https://opencv.org/platforms/cuda/

### Configuración de entorno
 
