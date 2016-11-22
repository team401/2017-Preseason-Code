/* Author: Liam Lawrence
 * Date: 11.14.16
 *
 * Vision file written in VIM to show Cameron
 * that he needs to actually install OpenCV
 */

#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "network.h"
#include "boost/thread/thread.hpp"
//This is a test header for testing objects
#include "iostream"
//We also need this (Liam why did you not import this and java does this for you so rip C++)

using namespace std;
using namespace cv;

int main(){

    Network myNetwork(123); //This should make our object
    cout << myNetwork.getTestInt() << endl; //Print our instance var

    boost::thread myThread(boost::bind(&Network::run, myNetwork));

    VideoCapture cap;
    Mat frame;

    if(!cap.open(0))
        return 0;

    // Cameron doesn't know how to do this
    // Testing github....--sorry zach and preston

    //Hi it's Cameron

    //cap.set(CV_CAP_PROP_FRAME_WIDTH,320);
    //cap.set(CV_CAP_PROP_FRAME_HEIGHT,240);
    //cap.set(CV_CAP_PROP_FRAME_WIDTH,176);
    //cap.set(CV_CAP_PROP_FRAME_HEIGHT,144);

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
