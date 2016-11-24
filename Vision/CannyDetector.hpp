//Class Header CannyDetector by Cameron Earle
//Sets up constructor for the CannyDetector class

#include "opencv2/videoio.hpp"

#ifndef INC_2017_PRESEASON_CODE_CANNY_HPP
#define INC_2017_PRESEASON_CODE_CANNY_HPP

class CannyDetector {
private:
    cv::VideoCapture cap;
    int thresh1;
    int thresh2;
public:
    CannyDetector(cv::VideoCapture cap_, int thresh1_, int thresh2_) {
        cap = cap_;
        thresh1 = thresh1_;
        thresh2 = thresh2_;
    }

    void run();
};


#endif //INC_2017_PRESEASON_CODE_CANNY_HPP
