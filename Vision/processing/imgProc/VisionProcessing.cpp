//Class CannyDetector by Cameron Earle
//Takes a capture device as an argument, and runs canny
//until esc is pressed


#include "VisionProcessing.hpp"
#include "opencv2/opencv.hpp"
#include "CreateShapes.hpp"
#include "../networking/FrameSender.hpp"
#include "../MathData.hpp"
#include "../ThreadManager.hpp"
#include "../MathFunctions.hpp"
#include "../networking/DataSender.hpp"

using namespace cv;

void VisionProcessing::run() {
    //Initialize all the mats that we will use throughout the program
    Mat frame;       //Original from camera
    Mat edges;       //Canny binary
    Mat hsvFrame;    //HSV converted
    Mat rangeFrame;  //Mask binary
    Mat erosionMat;  //Noise filtered binary
    Mat maskedMat;   //Masked RGB from original
    Mat contoursMat; //Contours display

    vector<vector<Point>> contours; //List of contours
    vector<Vec4i> hierarchy; //Hierarchy of contours

    //Variables for contours
    int currentArea = -1;
    int largestArea = -1;
    int idx = -1;

    if (settings.getDebugMode()) {
        namedWindow("Original", WINDOW_AUTOSIZE); //Create a window for the original image
        namedWindow("Canny", WINDOW_AUTOSIZE); //Create a window for the canny image
        namedWindow("Contours", WINDOW_AUTOSIZE); //Create a window for showing contours
        namedWindow("HSV", WINDOW_AUTOSIZE);
        namedWindow("Masked", WINDOW_AUTOSIZE); //Create a window for showing a masked image
    }

    bool firstCycle = true;

    while (ThreadManager::get(ThreadManager::Thread::CANNY_DETECTOR)) {
        if(waitKey(1) == 27) { //If ESC is pressed, break the loop
            break;
        }

        cap >> frame; //Grab a Mat frame from the capture stream
        FrameSender::addToQueue(frame); //Add the camera frame to the network queue

        //Initialize "dynamic" mats
        if (settings.getDebugMode()) { //Only if we need to, we don't have to draw anything on these if we don't need to see them
            contoursMat = Mat::zeros(frame.size(), frame.type());
            maskedMat = Mat::zeros(frame.size(), frame.type());
        }

        //Initialize "static" mats
        if (firstCycle) {
            edges = Mat::zeros(frame.size(), frame.type());
            hsvFrame = Mat::zeros(frame.size(), frame.type());
            rangeFrame = Mat::zeros(frame.size(), frame.type());
            erosionMat = Mat::zeros(frame.size(), frame.type());
            firstCycle = false;
        }

        cvtColor(frame, hsvFrame, CV_BGR2HSV);  //Convert the original image to HSV, and write it to hsvFrame
        inRange(hsvFrame, rangeThreshLower, rangeThreshUpper, rangeFrame); //Get a binary mask of our desired colors, and write it to rangeFrame
        erode( rangeFrame, erosionMat,  Mat(), Point(-1, -1), 1, 0, 1); //Filter noise from the rangeFrame and write it to erosionMat
        Canny(erosionMat, edges, thresh1, thresh2); //Run canny on our eroded frame, and write the binary to edges

        findContours(edges, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) ); //Find the contours from the canny data, and get list and hierarchy info

        //Loop through our contours
        currentArea = -1;
        largestArea = -1;
        idx = -1;
        for(int i=0; i<contours.size();i++) {
            currentArea = contours[i].size(); //Store the area of the current contour
            if (currentArea > largestArea) { //If the area of the current contour is greater than the area of the largest contour
                largestArea = currentArea; //Make the area of the largest contour the area of the current contour
                idx = i; //Store the index of the current largest contour for later use
            }
            if (settings.getDebugMode()) {
                cv::drawContours(contoursMat, contours, i, Scalar(0,150,255), 2, 8); //Draw each contour
            }
        }

        if (settings.getDebugMode()) {
            frame.copyTo(maskedMat, rangeFrame); //Create a "masked" frame containing original frame data, only matching a certain color
        }

        // Draws the square on contoursMat and gets the angles we need to turn the robot
        vector<Point> shapePoints = CreateShapes::shapes(contoursMat, idx, contours);
        Point center = shapePoints[0];   // Grabs the circle center point

        // Finds the angles that we need to turn in order to turn the robot
        vector<float> angles = MathFunctions::findAngles(mathData, center);

        // calculates distance from camera to the goal
        float distance = MathFunctions::findDistance(mathData, shapePoints[1], shapePoints[2]);


        DataSender::addToQueue(vector<float>{angles[0], angles[1], distance}); //Add the math data to the network queue


        // Writes specific frames to their respective windows if debug mode is enabled, as well as print debug info
        if (settings.getDebugMode()) {
            cout << "YAW:" << angles[0] << " | PITCH:" << angles[1] << " | DISTANCE:" << distance << "\n";
            imshow("Original", frame);
            imshow("Canny", edges);
            imshow("Contours", contoursMat);
            imshow("HSV", hsvFrame);
            imshow("Masked", maskedMat);
        }
    }
}