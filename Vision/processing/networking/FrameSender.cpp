//
// Created by cameronearle on 12/4/16.
//
#include "FrameSender.hpp"
#include <opencv2/imgcodecs.hpp>
#include "zhelpers.hpp"
#include "boost/thread/thread.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "../ThreadManager.hpp"


boost::lockfree::spsc_queue<cv::Mat> FrameSender::sendQueue(512); //The queue to hold the incoming images

/* Function run
 * Definition: The function to run when the thread starts
 */
void FrameSender::run() {
    zmq::context_t context(1); //Create a context for our socket
    zmq::socket_t socket(context, ZMQ_PUB); //Create a publisher socket to send images
    socket.bind("tcp://*:" + std::to_string(port)); //Bind the socket to all interfaces
    std::vector<uchar> buff;
    cv::Mat latestFrame;
    while (ThreadManager::get(ThreadManager::Thread::FRAME_SENDER)) { //While the threadmanager says this thread should run
        while (sendQueue.pop(latestFrame)) { //While there is data in the queue
            cv::imencode(".jpg", latestFrame, buff); //Encode the latest image into the JPG format
            s_send(socket, std::string(buff.begin(), buff.end())); //Send the image
            buff.clear(); //Clear the image buffer for the next image
        }
        boost::this_thread::sleep(boost::posix_time::milliseconds(10)); //Keep the CPU load reasonable
    }
    socket.close(); //Disconnect from the socket when we are done with it
}


void FrameSender::addToQueue(cv::Mat frame_) {
    sendQueue.push(frame_); //Add the given image to the threadsafe queue
}