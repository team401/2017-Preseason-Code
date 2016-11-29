//Class CannyDetector by Cameron Earle
//Takes a capture device as an argument, and runs canny
//until esc is pressed


#include "CannyDetector.hpp"
#include "opencv2/opencv.hpp"
#include "CreateShapes.hpp"
#include "NetworkTables.hpp"

using namespace cv;
using namespace std;

void CannyDetector::run() {
    Mat frame; //Set up a Mat for the image from the camera
    Mat edges; //Set up a Mat for the canny image
    Mat hsvFrame;   // Set up a Mat for the hsv frame
    Mat rangeFrame; // Set up a Mat for the thresholded frame
    Mat erosionMat;    // Set up a Mat for the noise reduced frame

    Mat contoursMat; //Set up a Mat for the contour image
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    Scalar lowerThresh(50,115,205);     //Lower bound BGR for the inRange function
    Scalar upperThresh(135,185,255);    //Upper bound BGR for the inRange function

    //Variables for contours
    int area = 0;
    int idx;

    // Variables for math -- TODO should these be doubles?
    float FOV = (60 * 3.141592) / 180;  // FOV is 60 degrees, but we want it in radians
    float cy = (640 / 2) - 0.5; // 640 is the image height
    float cx = (480 / 2) - 0.5; // 480 is the image width
    float focalLength = 480 / (2*tan(FOV/2));

    bool firstCycle = true;

    namedWindow("Original", WINDOW_AUTOSIZE); //Create a window for the original image
    namedWindow("Canny", WINDOW_AUTOSIZE); //Create a window for the canny image
    namedWindow("Contours", WINDOW_AUTOSIZE); //Create a window for showing contours
    //namedWindow("Thresh", WINDOW_AUTOSIZE); //For now this doesn't work, believe it has something to do with
    //                                          not being able to display hsv in its raw form, //TODO Fix this


    for(;;) {
        if(waitKey(1) == 27) { //If ESC is pressed, break the loop
            break;
        }

        cap >> frame; //Grab a Mat frame from the capture stream

        // We don't want to run this every single time TODO(wouldn't that waste memory?)
        if(firstCycle) {
            edges = Mat::zeros(frame.size(), frame.type());
            hsvFrame = Mat::zeros(frame.size(), frame.type());
            rangeFrame = Mat::zeros(frame.size(), frame.type());
            contoursMat = Mat::zeros(frame.size(), frame.type());
            erosionMat = Mat::zeros(frame.size(), frame.type());
            firstCycle = false;
        }

        // Filters everything we don't want
        cvtColor(frame, hsvFrame, CV_BGR2HSV);  // Convert the image stream to HSV
        inRange(hsvFrame, lowerThresh, upperThresh, rangeFrame);        // Filters out everything but the goal
        erode( rangeFrame, erosionMat,  Mat(), Point(-1, -1), 2, 1, 1); // Filters out the unwanted noise
        Canny(erosionMat, edges, thresh1, thresh2); //Get canny image and write the data to it (rangeFrame is already gray)

        // Finds contours and draws shapes
        findContours(edges, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) ); //Find the contours
        //contoursMat = Mat::zeros( edges.size(), CV_8UC3 ); //Initialize the contour Mat TODO Why is this moved

        // Finds the contour with the largest area, & records them.
        for(int i=0; i<contours.size();i++) {
            cv::drawContours(contoursMat, contours, i, Scalar(0,150,255), 2, 8);
            if(area < contours[i].size()){
                idx = i;
            }
        }

        // Draws the square on contoursMat and gets the angles we need to turn the robot
        Point center = CreateShapes::shapes(contoursMat, idx, contours);
        vector<float> angles = CreateShapes::findAngles(cx, cy, focalLength, center);

        // Sends data to the RoboRIO
        NetworkTables::sendData(angles[0], angles[1], angles[2], angles[3]);

        // Writes specific frames to their respective windows
        imshow("Original", frame);
        imshow("Canny", edges);
        imshow("Contours", contoursMat);
        //imshow("Thresh", rangeFrame);
    }
}