//Class CannyDetector by Cameron Earle
//Takes a capture device as an argument, and runs canny
//until esc is pressed


#include "CannyDetector.hpp"
#include "opencv2/opencv.hpp"
#include "CreateShapes.hpp"

using namespace cv;
using namespace std;

void CannyDetector::run() {
    Mat frame; //Set up a Mat for the image from the camera
    Mat edges; //Set up a Mat for the canny image
    Mat contoursMat; //Set up a Mat for the contour image
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    int area = 0;
    int idx;

    RNG rng(12345);
    Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );

    namedWindow("Original", WINDOW_AUTOSIZE); //Create a window for the original image
    namedWindow("Canny", WINDOW_AUTOSIZE); //Create a window for the canny image
    namedWindow("Contours", WINDOW_AUTOSIZE); //Create a window for showing contours

    for(;;) {
        if(waitKey(1) == 27) { //If ESC is pressed, break the loop
            break;
        }

        cap >> frame; //Grab a Mat frame from the capture stream

        cvtColor(frame, edges, CV_BGR2GRAY); //Convert the image to greyscale

        Canny(edges, edges, thresh1, thresh2); //Get canny image and write the data to it

        findContours(edges, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) ); //Find the contours

        contoursMat = Mat::zeros( edges.size(), CV_8UC3 ); //Initialize the contour Mat

        // Finds the contour with the largest area, draw & record them.

        for(int i=0; i<contours.size();i++) {
            drawContours(frame, contours, i, Scalar(0,150,255), 2, 8);
            if(area < contours[i].size()){
                idx = i;
            }
        }

       // CreateShapes::square(frame, idx, contours);

        imshow("Original", frame); //Write the original frame to the Original window
        imshow("Canny", edges); //Write the canny frame to the Canny window
        imshow("Contours", contoursMat);
    }
}
