#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;

int main(){


    VideoCapture cap;
    Mat frame;

    if(!cap.open(0))
        return 0;


    for(;;){
        // Passes camera cap to frame
        cap >> frame;

        // If the frame is blank or we hit ESC, break
        if(frame.empty() || waitKey(1) == 27)
            break;


        // Creates the GUI for us
        namedWindow("video", WINDOW_AUTOSIZE);
        imshow("video", frame);
    }
}
