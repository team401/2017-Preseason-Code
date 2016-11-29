/* Class CreateShapes by Liam Lawrence on 11.28.16
 * Sets up constructor for the CreateShapes class
 */

#include "opencv2/videoio.hpp"
#ifndef INC_2017_PRESEASON_CODE_CREATESSHAPES_HPP
#define INC_2017_PRESEASON_CODE_CREATESSHAPES_HPP
using namespace cv;
using namespace std;

struct CreateShapes {
    static cv::Point shapes(Mat &frame, int idx, vector<vector<Point>> contours);
    static std::vector<float> findAngles(float cx, float cy, float focalLength, cv::Point circleCenter);
};


#endif //INC_2017_PRESEASON_CODE_CREATESSHAPES_HPP
