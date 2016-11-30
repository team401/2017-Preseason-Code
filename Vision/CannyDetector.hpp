//Class Header CannyDetector by Cameron Earle
//Sets up constructor for the CannyDetector class

#include "opencv2/videoio.hpp"
#include "MathData.hpp"

#ifndef INC_2017_PRESEASON_CODE_CANNY_HPP
#define INC_2017_PRESEASON_CODE_CANNY_HPP

class CannyDetector {
private:
    cv::VideoCapture cap;
    MathData mathData;
    cv::Scalar rangeThreshLower;
    cv::Scalar rangeThreshUpper;
    int thresh1;
    int thresh2;
public:
    CannyDetector(cv::VideoCapture cap_, MathData data_, cv::Scalar rangeThresh1_, cv::Scalar rangeThresh2_, int thresh1_, int thresh2_) {
        cap = cap_;
        mathData = data_;
        rangeThreshLower = rangeThresh1_;
        rangeThreshUpper = rangeThresh2_;
        thresh1 = thresh1_;
        thresh2 = thresh2_;
    }

    void run();
};


#endif //INC_2017_PRESEASON_CODE_CANNY_HPP
