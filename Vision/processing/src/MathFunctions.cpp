/*
 * MathFunctions created by Liam Lawrence on 12.5.16
 * Returns the distance from the camera to the object
 * Calculates angles robot needs to turn
 *
 */
#include "MathFunctions.hpp"

using namespace std;

/* Function findDistance
 * Argument [MathData mathData]: The object containing the focal length of the camera
 * Argument [Point pt1]: The first point of an image
 * Argument [Point pt2]: The second point of an image
 * Description: Finds the distance between two points of an image
 * Returns [float]: The distance between the two points
 */
float MathFunctions::findDistance(MathData mathData, cv::Point pt1, cv::Point pt2) {
    if (pt1.x == -1 && pt1.y == -1 && pt2.x == -1 & pt2.y == -1) { //If any of the values from the input points is invalid
        return -1; //Return our invalid number
    }
    float pixelWidth = (pt1.x - pt2.x); //The distance in pixels from each point

    return (12 * mathData.getFocalLength()) / pixelWidth; //The actual distance accounting for focal length
}

/* Function findAngles
 * Argument [MathData mathData]: The numbers that are used to make calculations
 * Argument [Point circleCenter]: The centerpoint of the circle where the goal is
 * Description: Finds the angles that the robot needs to turn
 * Returns [vector<float>]: Returns a group of angles {yaw, pitch}
 */
vector<float> MathFunctions::findAngles(MathData mathData, cv::Point circleCenter) {
    if (circleCenter.x == -1 && circleCenter.y == -1) { //If the values from the circle center are invalid
        return std::vector<float>({-1,-1}); //Return our invalid pair
    }
    vector<float> angles;
    // The thing we multiply is degrees per pixel in each direction
    angles.push_back((circleCenter.x - mathData.getCx()) * 0.0890625);   //yaw
    angles.push_back((circleCenter.y - mathData.getCy()) * 0.11875);     //pitch

    return angles; //The angles the robot needs to turn
}