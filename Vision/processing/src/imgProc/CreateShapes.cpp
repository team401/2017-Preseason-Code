/* Class CreatesShapes by Liam Lawrence on 11.28.16
 * Takes a frame and draws a specified shape on the largest contour
 */

#include "opencv2/videoio.hpp"
#include "opencv2/opencv.hpp"
#include "CreateShapes.hpp"
#include "iostream"

using namespace std;

string CreateShapes::ld = "CreateShapes";

/* Function shapes
 * Argument [Mat &frame]: A reference to the original image, so we can draw right on it
 * Argument [int idx]: The index of the largest contour
 * Argument [vector<vector<Point>> contours]: The list of contours
 * Argument [bool drawShapes=true]: Whether or not we should actually draw the shapes (performance improvement)
 * Description: Draws shapes on the given mat, and returns data about the shapes
 * Returns [vector<Point>]: A group of information about the shapes
 */
vector<cv::Point> CreateShapes::shapes(cv::Mat &frame, int idx, vector<vector<cv::Point>> contours, bool drawShapes) {
    if (contours.size() <= 0) {
        return vector<cv::Point>{cv::Point(-1, -1),cv::Point(-1, -1),cv::Point(-1, -1)}; //VERY VERY IMPORTANT!!! If there are no contours, just return a blank point!!!
    }

    cv::Point center;
    cv::Point pt1, pt2;
    vector<cv::Point> points;

    // Draws a bounding rectangle on the frame
    cv::Rect rect = boundingRect(contours[idx]);
    pt1.x = rect.x;
    pt1.y = rect.y;
    pt2.x = rect.x + rect.width;
    pt2.y = rect.y + rect.height;
    if (drawShapes) {
        cv::rectangle(frame, pt1, pt2, cv::Scalar(255,204,0), 2);
    }

    // Draws a bounding circle in the center of the rectangle
    center.x = (pt1.x + pt2.x) / 2;
    center.y = (pt1.y + pt2.y) / 2;
    if (drawShapes) {
        cv::circle(frame, center, 2, cv::Scalar(255,204,10), 2);
    }

    points.push_back(center);
    points.push_back(pt1);
    points.push_back(pt2);
    return points;
}