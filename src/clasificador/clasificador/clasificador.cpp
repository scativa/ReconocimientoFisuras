// opencv-test.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

// Define el umbral a partir de cuando un pixel de la imagen original y de la marcada son distintos. 
#define TH 50

// Define el tamaños de los cuadros en que subdivide la imagen
#define CUADSIZE 50

// Define la cantidad mínima de píxeles que un cuadro tiene que intersecar la máscara para que sea considerado como positivo (con falla). Esto debería ser una proporción de CUADSIZE
#define TH_MASK_PIXELS 100

int main()
{
	char filename_buffer[FILENAME_MAX];


	// class Mat https://docs.opencv.org/2.4/modules/core/doc/basic_structures.html?highlight=class%20rect#mat

	// example from https://docs.opencv.org/2.4/doc/tutorials/introduction/display_image/display_image.html
	Mat image_original, image_marcada;

	// Lectura de las imagenes original y mascara de la carpeta ./input/
	sprintf_s(filename_buffer, FILENAME_MAX, ".\\input\\%s.jpg", "original");
	image_original = imread(filename_buffer, 1 /* CV_LOAD_IMAGE_COLOR*/);   // Read the file
	if (!image_original.data) {                             // Check for invalid input
		cout << "Could not open or find the image "<< filename_buffer << std::endl;
		return -1;
	}

	sprintf_s(filename_buffer, FILENAME_MAX, ".\\input\\%s.jpg", "marcada");
	image_marcada = imread(filename_buffer, 1 /* CV_LOAD_IMAGE_COLOR*/);   // Read the file
	if (!image_marcada.data) {                             // Check for invalid input
		cout << "Could not open or find the image " << filename_buffer << std::endl;
		return -1;
	}

	// Se calcula la máscara...
	Mat mascara_rgb, mascara_grey;
	mascara_rgb = (image_marcada - image_original) > TH; // ... como diferencia entre las dos imágenes de entrada. Se tiene en cuenta que al escribir una imagen jpeg esta puede cambiar aún en pixeles que no fueron modificados
	cvtColor(mascara_rgb, mascara_grey, cv::COLOR_BGR2GRAY); // https://stackoverflow.com/questions/10344246/how-can-i-convert-a-cvmat-to-a-gray-scale-in-opencv
	mascara_grey = mascara_grey > 0; // Se utiliza la máscara en escala de grises y se la normaliza con los valores entre 0 y 256 (en realidad esto es así??? verificar)


	cout << "Input: " << "Cols: " << image_original.cols << "; Rows: " << image_original.rows << endl << endl;
	cout << "Outputs: " << endl;

	//
	// Generación de los cuadros positivos (marcados con fallas) y los negativos. Clasificación
	//
	int count = 0;
	for (int i = 0; i < image_original.cols - CUADSIZE; i += CUADSIZE) {
		for (int j = 0; j < image_original.rows - CUADSIZE;  j += CUADSIZE) {


			// Se toman las submatrices a partir del rectángulo R de tamaño CUADSIZE * CUADSIZE 
			Rect R(i, j, CUADSIZE, CUADSIZE); // Submatrix: https://stackoverflow.com/questions/27835439/opencv-submatrix-access-copy-or-reference
			Mat cuad_original = image_original(R).clone();
			Mat cuad_mascara_grey = mascara_grey(R).clone();

			// Calculo de cuántos píxeles de la máscara intersecan el cuadro. Con esto se define el nombre del archivo con el prefijo "pos" o "neg". Luego se completa el nombre con los límites del cuadro
			Scalar suma = sum(cuad_mascara_grey);
			double intersec = (suma[0] / 256);
			//cout << (suma[0] / 256) << endl;
			// sprintf_s: https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/sprintf-s-sprintf-s-l-swprintf-s-swprintf-s-l?view=vs-2019
			sprintf_s(filename_buffer, FILENAME_MAX, ".\\output\\%s_%i-%i_%i-%i.jpg", (intersec > TH_MASK_PIXELS) ? "pos":"neg", i, j, i + CUADSIZE, j + CUADSIZE);

			// Se escribe en cuadrado en la carpeta ./output/
			cout << count++ << ")" << filename_buffer << endl;
			imwrite(filename_buffer, cuad_original);

			//namedWindow("Display window", WINDOW_NORMAL); // Create a window for display.
			//imshow("Display window", cuad_original);        // Show our image inside it.
		}
	}

	waitKey(0);
	return 0;
}