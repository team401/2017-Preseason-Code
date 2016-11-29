//
// Created by Liam Lawrence on 11.28.16
//

#include "opencv2/videoio.hpp"
#ifndef INC_2017_PRESEASON_CODE_CREATESSHAPES_HPP
#define INC_2017_PRESEASON_CODE_CREATESSHAPES_HPP
using namespace cv;
using namespace std;

struct CreateShapes {
    static void circle(Mat &frame);
    static void square(Mat &frame, int idx, vector<vector<Point>> contours);
};


#endif //INC_2017_PRESEASON_CODE_CREATESSHAPES_HPP
