//Class Header CannyDetector by Cameron Earle
//Sets up constructor for the CannyDetector class

#include "opencv2/videoio.hpp"
#include "../MathData.hpp"
#include "../config/ConfigSettings.hpp"

#ifndef INC_2017_PRESEASON_CODE_CANNY_HPP
#define INC_2017_PRESEASON_CODE_CANNY_HPP

using namespace cv;

class VisionProcessing {
public:
    VisionProcessing(ConfigSettings settings_, VideoCapture cap_, MathData data_) {
        settings = settings_;
        cap = cap_;
        mathData = data_;
        rangeThreshLower = settings.getLowerBound();
        rangeThreshUpper = settings.getUpperBound();
        thresh1 = settings.getCannyLowerBound();
        thresh2 = settings.getCannyUpperBound();
    }

    void run();
private:
    ConfigSettings settings;
    VideoCapture cap;
    MathData mathData;
    Scalar rangeThreshLower;
    Scalar rangeThreshUpper;
    int thresh1;
    int thresh2;
    std::string ld = "CannyDetector";
};


#endif //INC_2017_PRESEASON_CODE_CANNY_HPP
