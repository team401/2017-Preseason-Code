/*
 * MathFunctions created by Liam Lawrence on 12.5.16
 * Returns the distance from the camera to the object
 * Calculates angles robot needs to turn
 *
 */
#include "MathFunctions.hpp"

using namespace std;

// distance = (realWidth * focalLength) / pixelWidth
float MathFunctions::findDistance(float focalLength, Point pt1, Point pt2) {
    float pixelWidth = (pt1.x - pt2.x);

    return (12 * focalLength) / pixelWidth;
}

// Finds the angles the robot needs to turn
std::vector<float> MathFunctions::findAngles(float cx, float cy, float focalLength, cv::Point circleCenter) {
    if (circleCenter.x == -1 && circleCenter.y == -1) {
        return std::vector<float>({0,0,0,0});
    }
    std::vector<float> angles;
    angles.push_back((circleCenter.x - cx) * 0.0890625);   //yaw
    angles.push_back((circleCenter.y - cy) * 0.11875);     //pitch
    //angles.push_back(cx - circleCenter.x);               //xDif
    //angles.push_back(cy - circleCenter.y);               //yDif

    return angles;
}