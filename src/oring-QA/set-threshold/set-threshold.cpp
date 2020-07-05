// opencv-test.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat src, erosion_dst, dilation_dst;

/// Global variables

int threshold_value = 0;
int threshold_type = 3;;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;

Mat src_gray, dst;
char* window_name = "Threshold Demo";

char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
char* trackbar_value = "Value";

/// Function headers
void Threshold_Demo( int, void* );



int main()
{
	src = imread("../topview.jpeg");

    /*
    int height = src.size().height;
    int width = src.size().width;
    */
    
    int rows = src.rows;
    int cols = src.cols;
    
    cout << "Size R: " << rows << " C:" << cols << endl;
    int rbase = 400;
    int cbase = 10;
    Rect crop( cbase, rbase , cols - cbase -1 , rows - rbase - 1);
    Mat rez = src(crop);	

/*
	Mat image = rez;
	//Mat::zeros(300, 600, CV_8UC3);
	imshow("Display Window", image);
    imwrite("./res.jpg",image);
*/



  /// Convert the image to Gray
  cvtColor( rez, src_gray, cv::COLOR_BGR2GRAY );

  /// Create a window to display results
  namedWindow( window_name, WINDOW_AUTOSIZE );

  /// Create Trackbar to choose type of Threshold
  createTrackbar( trackbar_type,
                  window_name, &threshold_type,
                  max_type, Threshold_Demo );

  createTrackbar( trackbar_value,
                  window_name, &threshold_value,
                  max_value, Threshold_Demo );

  /// Call the function to initialize
  Threshold_Demo( 0, 0 );

  /// Wait until user finishes program
  while(true)
  {
    int c;
    c = waitKey( 20 );
    if( (char)c == 27 )
      { break; }
   }
   return(0);
}

/**
 * @function Threshold_Demo
 */
void Threshold_Demo( int, void* )
{
  /* 0: Binary
     1: Binary Inverted
     2: Threshold Truncated
     3: Threshold to Zero
     4: Threshold to Zero Inverted
   */

  threshold( src_gray, dst, threshold_value, max_BINARY_value,threshold_type );

  imshow( window_name, dst );
}

