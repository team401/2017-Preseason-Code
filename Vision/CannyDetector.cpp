//Class CannyDetector by Cameron Earle
//Takes a capture device as an argument, and runs canny
//until esc is pressed


#include "CannyDetector.hpp"
#include "opencv2/opencv.hpp"

using namespace cv;

void CannyDetector::run() {
    Mat frame; //Set up a Mat for the image from the camera
    Mat edges; //Set up a Mat for the canny image

    namedWindow("Original", WINDOW_AUTOSIZE); //Create a window for the original image
    namedWindow("Canny", WINDOW_AUTOSIZE); //Create a window for the canny image

    for (;;) {
        if(waitKey(1) == 27) { //If ESC is pressed, break the loop
            break;
        }

        cap >> frame; //Grap a Mat frame from the capture stream

        cvtColor(frame, edges, CV_BGR2GRAY); //Convert the image to greyscale

        Canny(edges, edges, thresh1, thresh2); //Get canny image and write the data to it

        imshow("Original", frame); //Write the original frame to the Original window
        imshow("Canny", edges); //Write the canny frame to the Canny window
    }
}
