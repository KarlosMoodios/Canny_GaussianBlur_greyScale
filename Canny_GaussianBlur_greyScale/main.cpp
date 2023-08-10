// OpenCV - Testing Filters/Kernels using openCV-4.5.1

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/videoio.hpp>
#include<iostream>
#include<conio.h>

using namespace cv;
using namespace std;

int main() {
    //VideoCapture capture(0);                          // Declare a VideoCapture object and associate to webcam, 0 => 1st webcam
    VideoCapture capture("Traffic1.mp4", CAP_FFMPEG);   // Declare a VideoCapture object and assign video

    if (capture.isOpened() == false) {                                              // Check if VideoCapture object was associated to webcam successfully
        cout << "Error: Capture not accessed successfully. Check video feed.\n";    // if not, print error message to std out
        _getch();                                                                   // may have to modify this line if not using Windows
        return(0);                                                                  // and exit program
    }

    Mat imgOriginal;        // Input image
    Mat imgGrayscale;       // Grayscale image
    Mat imgBlurred;         // Intermediate blurred image
    Mat imgCanny;           // Canny edge image

    char charCheckForEscKey = 0;

    while (charCheckForEscKey != 27 && capture.isOpened()) {        // While Esc key not pressed, webcam connection lost, video feed ends.
        bool blnFrameReadSuccessfully = capture.read(imgOriginal);  // Get next frame

        if (!blnFrameReadSuccessfully || imgOriginal.empty()) {     // If frame not read successfully
            std::cout << "Error: Frame not read from webcam\n";     // print error message to std out
            break;                                                  // and break out of while loop
        }

        // Define filters / kernels
        cvtColor(imgOriginal, imgGrayscale, COLOR_BGR2GRAY);        // Convert to grayscale
        GaussianBlur(imgOriginal, imgBlurred, Size(5, 5), 1.8);     // Input image, output image, smoothing window (WxH in pixels), sigma value (blur intensity)
        Canny(imgOriginal, imgCanny, 50, 100);                      // Input image, output image, low threshold, high threshold

        // Declare windows
        namedWindow("imgOriginal", WINDOW_AUTOSIZE);                // Note: you can use WINDOW_NORMAL which allows resizing the window
        namedWindow("imgGrayscale", WINDOW_AUTOSIZE);
        namedWindow("imgCanny", WINDOW_AUTOSIZE);                   // or WINDOW_AUTOSIZE for a fixed size window matching the resolution of the image
        namedWindow("imgGaussianBlur", WINDOW_AUTOSIZE);            // WINDOW_AUTOSIZE is the default

        // Show windows                                                   
        imshow("imgOriginal", imgOriginal);
        imshow("imgGrayscale", imgGrayscale);
        imshow("imgCanny", imgCanny);
        imshow("imgGaussianBlur", imgBlurred);

        charCheckForEscKey = waitKey(1);        // Delay (in ms) and get key press, if any
    }   // End while

    return(0);
}