#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

#include<iostream>

using namespace cv;
using namespace std;

int main()
{
    String imgloc = "F:\\upendra\\projects\\iitj.png"; // Give your image location here
    Mat image;
    image= imread(imgloc);                          // Read the file
    if(image.empty() )                              // Check for invalid input
    {
       cout <<  "Could not open or find the image" << endl ;
       return -1;
    }
    namedWindow( "Display window" );    // Create a window for display.
    imshow( "Display window", image );                   // Show our image inside it.

    waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
}
