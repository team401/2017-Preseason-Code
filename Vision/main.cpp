#include "opencv2/videoio.hpp"
#include "boost/thread/thread.hpp"
#include "CannyDetector.hpp"
#include "MathData.hpp"

using namespace std;
using namespace cv;
int main(){


    VideoCapture cap;

    if(!cap.open(1)) {
        return 0;
    }

    MathData mathData;
    mathData.setFOV((57 * 3.141592) / 180);
    mathData.setCy((480 / 2) - 0.5);
    mathData.setCx((640 / 2) - 0.5);
    mathData.setFocalLength(480 / (2*tan(mathData.getFOV()/2)));

    CannyDetector cannyDetector(cap, mathData, Scalar(50,250,40), Scalar(70,255,160), 30, 60);
    boost::thread myThread(boost::bind(&CannyDetector::run, cannyDetector));
    myThread.join();

}
