#include <opencv2/videoio/videoio_c.h>
#include <boost/lexical_cast.hpp>
#include "opencv2/videoio.hpp"
#include "boost/thread/thread.hpp"
#include "src/imgProc/VisionProcessing.hpp"
#include "src/networking/FrameSender.hpp"
#include "src/networking/DataSender.hpp"
#include "src/networking/Heartbeat.hpp"
#include "src/ThreadManager.hpp"
#include "src/dataLogging/Log.hpp"
#include "src/config/ConfigParser.hpp"

using namespace std;

int main(int argc, char *argv[]){
    Log::init(Log::Level::INFO, true); //Initialize the logger to only store INFO messages, and to write to file
    string ld = "main"; //Log descriptor, used to identify this class in the log file
    Log::i(ld, "Vision Processor Starting!");

    ConfigSettings configSettings = ConfigParser(vector<string>(argv+1, argv + argc)).getSettings(); //Parse the config and inject command line arguments
    Log::setDoDebug(configSettings.getDebugMode()); //Tell the logger whether or not it should waste time even dealing with debug log messages
    configSettings.setCamera(); //Set up the camera using the device number found in the config

    cv::VideoCapture cap; //Capture device holder
    //cap = configSettings.getCapture(); //Get the capture device from the list in the config

    cap.open("/home/cameronearle/Desktop/goal.mov");

    cap.set(CV_CAP_PROP_FPS, 30); //Set the camera FPS //TODO: Change this to 60 once Cameron gets a real laptop

    MathData mathData; //Calculation value holder
    mathData.setFOV((57 * 3.141592) / 180);
    mathData.setCy((480 / 2) - 0.5);
    mathData.setCx((640 / 2) - 0.5);
    mathData.setFocalLength(480 / (2*tan(mathData.getFOV()/2)));

    //Initialize instances of threaded objects
    VisionProcessing visionProcessor(configSettings, cap, mathData); //Initialize the vision processing code

    //Heartbeat heartbeat(configSettings.getNetworkHeartbeatPort()); //Initialize the heartbeat sender
    FrameSender frameSender(configSettings.getNetworkImagePort()); //Initialize the camera view sender
    DataSender dataSender(configSettings.getNetworkDataPort()); //Initialize the network data sender

    Log::i(ld, "Setup complete, starting threads");

    boost::thread processorThread(boost::bind(&VisionProcessing::run, visionProcessor)); //Start the vision processor
    //boost::thread heartbeatThread(boost::bind(&Heartbeat::run, heartbeat)); //Start the heartbeat
    boost::thread frameSenderThread(boost::bind(&FrameSender::run, frameSender)); //Start the camera view sender
    boost::thread dataSenderThread(boost::bind(&DataSender::run, dataSender)); //Start the network data sender
    processorThread.join(); //Join the control thread so we know when to stop
    ThreadManager::set(ThreadManager::Thread::GLOBAL, false); //The control thread has stopped, signal all threads to stop

    Log::i(ld, "Program finished, exiting!");
    Log::close(); //Close the log file
}
