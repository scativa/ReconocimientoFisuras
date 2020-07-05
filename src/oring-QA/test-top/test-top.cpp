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

Mat src, erosion_dst, dilation_dst, src_gray, src_bw, out, capimg;

/// Global variables

int threshold_value = 0;
int threshold_type = 3;;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;

int erosion_elem = 2;
int erosion_size = 25;


char fname[80];


void Erosion2( int, void* );



int main( int argc, char** argv )
{
    CommandLineParser parser( argc, argv, "{@input | LinuxLogo.jpg | input image}" );
    src = imread( samples::findFile( parser.get<String>( "@input" ) ), IMREAD_COLOR );
    if( src.empty() ) {
        cout << "Could not open or find the image!\n" << endl;
        cout << "Usage: " << argv[0] << " <Input image>" << endl;
        return -1;
    }

    VideoCapture capture;
    capture.open(0);
    
    bool capok = capture.isOpened();
    
    if(capok)
        cout << "Capture is opened" << endl;
    else
        cout << "No capture" << endl;

  for (int i = 0; i < 100*20; i++) {

    src = imread( samples::findFile( parser.get<String>( "@input" ) ), IMREAD_COLOR );

    if (capok) 
        capture >> src;

    //cout << "Size R: " << src.rows << " C:" << src.cols << endl;
    
    /*
    rbase int = 400; int cbase = 10;
    Rect crop( cbase, rbase , cols - cbase -1 , rows - rbase - 1);
    Mat rez = src(crop);	
    */
    
  /// Convert the image to Gray
  //cout << cvtColor << endl;
  cvtColor( src, src_gray, cv::COLOR_BGR2GRAY );

  /* 0: Binary
     1: Binary Inverted
     2: Threshold Truncated
     3: Threshold to Zero
     4: Threshold to Zero Inverted
   */

  int threshold_value = 47;
  int threshold_type = 1;
  
  threshold( src_gray, src_bw, threshold_value, max_BINARY_value,threshold_type );
  
    //erosion_size += 2;
    //cout << "Erosion..." << erosion_size << endl;
    Erosion2( 0, 0 );
    
    sprintf(fname,"./out.jpg");
    imwrite(fname,src_bw);

  }
  //src_gray, src_bw = erosion_dst;
  

/*
  imshow( "", dst );

  while(true)
  {
    int c;
    c = waitKey( 20 );
    if( (char)c == 27 )
      { break; }
   }
   return(0);
   */
}

void Erosion2( int, void* )
{
  int erosion_type = 0;
  if( erosion_elem == 0 ){ erosion_type = MORPH_RECT; }
  else if( erosion_elem == 1 ){ erosion_type = MORPH_CROSS; }
  else if( erosion_elem == 2) { erosion_type = MORPH_ELLIPSE; }
  
  int size =  2*erosion_size + 1;
  //cout << "Erosion size: " << size << endl;
  
  Mat element = getStructuringElement( erosion_type,
                       Size(size, size),
                       Point( erosion_size, erosion_size ) );
                       

  //cout << "Eroding..." << endl;
  erode( src_gray, erosion_dst, element );
  // imshow( "Erosion Demo", erosion_dst );
}

