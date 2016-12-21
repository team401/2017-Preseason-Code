//
// Created by cameronearle on 12/20/16.
//

#include "gtest/gtest.h"
#include "../../processing/src/MathData.hpp"
#include "../../processing/src/MathFunctions.hpp"

TEST(math_tests, find_distance_bad_data_test) {
    MathData mathData;
    cv::Point point1;
    cv::Point point2;
    point1.x = -1;
    point1.y = -1;
    point2.x = -1;
    point2.y = -1;
    ASSERT_EQ(MathFunctions::findDistance(mathData, point1, point2), -1);
}

TEST(math_tests, find_distance_good_data_test) {
    MathData mathData;
    mathData.setFOV((57 * 3.141592) / 180);
    mathData.setCy((480 / 2) - 0.5);
    mathData.setCx((640 / 2) - 0.5);
    mathData.setFocalLength(480 / (2*tan(mathData.getFOV()/2)));
    cv::Point point1;
    cv::Point point2;
    point1.x = 100;
    point2.x = 10;
    point1.y = 0;
    point2.y = 0;
    ASSERT_EQ(MathFunctions::findDistance(mathData, point1, point2), (12*mathData.getFocalLength()) / 90);
}

TEST(math_tests, find_angles_bad_data_test) {
    MathData mathData;
    cv::Point point;
    point.x = -1;
    point.y = -1;
    ASSERT_EQ(MathFunctions::findAngles(mathData, point), std::vector<float>({-1, -1}));
}

TEST(math_tests, find_angles_good_data_test) {
    MathData mathData;
    mathData.setFOV((57 * 3.141592) / 180);
    mathData.setCy((480 / 2) - 0.5);
    mathData.setCx((640 / 2) - 0.5);
    mathData.setFocalLength(480 / (2*tan(mathData.getFOV()/2)));
    cv::Point point;
    point.x = 50;
    point.y = 70;
    std::vector<float> result = MathFunctions::findAngles(mathData, point);
    ASSERT_FLOAT_EQ(result[0], (point.x - mathData.getCx()) * 0.0890625);
    ASSERT_FLOAT_EQ(result[1], (point.y - mathData.getCy()) * 0.11875);
}