#include "opencv2/videoio.hpp"
#include "boost/thread/thread.hpp"
#include "CannyDetector.hpp"

using namespace std;
using namespace cv;

int main(){


    VideoCapture cap;

    if(!cap.open(1)) {
        return 0;
    }

    CannyDetector cannyDetector(cap, 30, 60);
    boost::thread myThread(boost::bind(&CannyDetector::run, cannyDetector));
    myThread.join();

}
