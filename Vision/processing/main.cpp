#include <opencv2/videoio/videoio_c.h>
#include "opencv2/videoio.hpp"
#include "boost/thread/thread.hpp"
#include "CannyDetector.hpp"
#include "iostream"
#include "MathData.hpp"
#include "CameraSettings.hpp"
#include "FrameSender.hpp"
#include "zmq.hpp"
#include "ThreadManager.hpp"
#include "Log.hpp"

using namespace std;
using namespace cv;

int main(){
    Log::init(Log::Level::INFO, true);
    std::string ld = "main";
    Log::i(ld, "Vision Processor Starting!");
    CameraSettings("/dev/video0").autoExposure(false).autoWB(false).finish();

    VideoCapture cap;

    if(!cap.open(0)) {
        return 0;
    }

    cap.set(CV_CAP_PROP_FPS, 30); //TODO: Change this to 60 once Cameron gets a real laptop
    cap.set(CAP_PROP_HUE, 0);
    cap.set(CAP_PROP_SATURATION, 255);
    cap.set(CAP_PROP_CONTRAST, 0);
    cap.set(CAP_PROP_EXPOSURE, 15);
    cap.set(CAP_PROP_GAIN, 20);

    MathData mathData;
    mathData.setFOV((57 * 3.141592) / 180);
    mathData.setCy((480 / 2) - 0.5);
    mathData.setCx((640 / 2) - 0.5);
    mathData.setFocalLength(480 / (2*tan(mathData.getFOV()/2)));

    CannyDetector cannyDetector(cap, mathData, Scalar(50,250,40), Scalar(70,255,160), 30, 60);

    FrameSender frameSender(5800);

    boost::thread cannyThread(boost::bind(&CannyDetector::run, cannyDetector));
    boost::thread frameSenderThread(boost::bind(&FrameSender::run, frameSender));
    cannyThread.join();
    ThreadManager::set(ThreadManager::Thread::GLOBAL, false);
}
