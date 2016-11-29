#include "opencv2/videoio.hpp"
#include "boost/thread/thread.hpp"
#include "CannyDetector.hpp"
#include "MathData.hpp"

using namespace std;
using namespace cv;
int main(){


    VideoCapture cap;

    if(!cap.open(0)) {
        return 0;
    }

    MathData mathData;
    mathData.setFOV((60 * 3.141592) / 180);
    mathData.setCy((640 / 2) - 0.5);
    mathData.setCx((480 / 2) - 0.5);
    mathData.setFocalLength(480 / (2*tan(mathData.getFOV()/2)));

    CannyDetector cannyDetector(cap, mathData, Scalar(50,115,205), Scalar(135,185,255), 30, 60);
    boost::thread myThread(boost::bind(&CannyDetector::run, cannyDetector));
    myThread.join();

}
