//
// Created by and3212 on 11/28/16.
//

#include "opencv2/videoio.hpp"
#include "opencv2/opencv.hpp"
#include "CreateShapes.hpp"

using namespace std;

// Draws a bounding circle
void CreateShapes::circle(cv::Mat &frame) {
    cv::Point center;
    Point pt1, pt2;
    center.x = (pt1.x + pt2.x) / 2;
    center.y = (pt1.y + pt2.y) / 2;
    cv::circle(frame, center, 5, Scalar(255,204,0), 2);
}

// Draws a bounding rectangle onto the frame
void CreateShapes::square(cv::Mat &frame, int idx, vector<vector<Point>> contours) {
    cv::Rect rect = boundingRect(contours[idx]);
    cv::Point pt1, pt2;
    pt1.x = rect.x;
    pt1.y = rect.y;
    pt2.x = rect.x + rect.width;
    pt2.y = rect.y + rect.height;
    cv::rectangle(frame, pt1, pt2, Scalar(255,204,0), 2);
}