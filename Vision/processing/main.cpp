#include <opencv2/videoio/videoio_c.h>
#include "opencv2/videoio.hpp"
#include "boost/thread/thread.hpp"
#include "imgProc/visionProcessing.hpp"
#include "iostream"
#include "MathData.hpp"
#include "CameraSettings.hpp"
#include "networking/FrameSender.hpp"
#include "zmq.hpp"
#include "ThreadManager.hpp"
#include "dataLogging/Log.hpp"

using namespace std;
using namespace cv;

int main(){
    Log::init(Log::Level::INFO, true);
    std::string ld = "main";
    Log::i(ld, "Vision Processor Starting!");
    CameraSettings("/dev/video1")
            .autoExposure(false)
            .autoWB(false)
            .autoGain(false)
            .setExposure(20)
            .setSaturation(255)
            .setContrast(0)
            .finish();

    VideoCapture cap;

    if(!cap.open(1)) {
        return 0;
    }

    cap.set(CV_CAP_PROP_FPS, 30); //TODO: Change this to 60 once Cameron gets a real laptop
    //cap.set(CAP_PROP_SATURATION, 255);
    //cap.set(CAP_PROP_CONTRAST, 0);
    //cap.set(CAP_PROP_BRIGHTNESS, 0);
    //cap.set(CAP_PROP_EXPOSURE, 20);
    //cap.set(CAP_PROP_GAIN, 20);

    MathData mathData;
    mathData.setFOV((57 * 3.141592) / 180);
    mathData.setCy((480 / 2) - 0.5);
    mathData.setCx((640 / 2) - 0.5);
    mathData.setFocalLength(480 / (2*tan(mathData.getFOV()/2)));

    CannyDetector cannyDetector(cap, mathData, Scalar(50,250,40), Scalar(70,255,160), 30, 60);

    FrameSender frameSender(5800);

    Log::i(ld, "Setup complete, starting threads");

    boost::thread cannyThread(boost::bind(&CannyDetector::run, cannyDetector));
    boost::thread frameSenderThread(boost::bind(&FrameSender::run, frameSender));
    cannyThread.join();
    ThreadManager::set(ThreadManager::Thread::GLOBAL, false);

    Log::i(ld, "Program finished, exiting!");
}
