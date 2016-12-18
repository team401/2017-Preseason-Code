/*
 * MathFunctions.hpp created by Liam Lawrence on 12.5.16
 * Header files for the MathFunctions.cpp file
 *
 */

#ifndef INC_2017_PRESEASON_CODE_MATHFUNCTIONS_HPP
#define INC_2017_PRESEASON_CODE_MATHFUNCTIONS_HPP

#include <vector>
#include "opencv2/core.hpp"
#include "MathData.hpp"

using namespace cv;

struct MathFunctions {
    static float findDistance(MathData mathData, Point pt1, Point pt2);
    static std::vector<float> findAngles(MathData mathData, Point circleCenter);
};


#endif //INC_2017_PRESEASON_CODE_MATHFUNCTIONS_HPP
