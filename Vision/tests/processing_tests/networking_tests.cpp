//
// Created by cameronearle on 12/19/16.
//

#include <boost/thread/thread.hpp>
#include "gtest/gtest.h"
#include "zhelpers.hpp"

#include "../../processing/src/networking/Heartbeat.hpp"
#include "../../processing/src/ThreadManager.hpp"
#include "../../processing/src/networking/DataSender.hpp"
#include "../../processing/src/networking/FrameSender.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>

void dataAdder(int identity, bool valid, bool run) {
    if (identity == 0) {
        if (valid) {
            while (run) {
                DataSender::addToQueue(vector<float>({-1, -1, -1}));
                boost::this_thread::sleep(boost::posix_time::seconds(1));
            }
        } else {
            while (run) {
                DataSender::addToQueue(vector<float>({-1, -1}));
                boost::this_thread::sleep(boost::posix_time::seconds(1));
            }
        }
    } else if (identity == 1) {
        cv::Mat imageMat = cv::Mat::zeros(640, 480, CV_8UC3);
        while (run) {
            FrameSender::addToQueue(imageMat);
            boost::this_thread::sleep(boost::posix_time::seconds(1));
        }
    }
}

TEST(networking_tests, heartbeat_test) {
    ThreadManager::set(ThreadManager::Thread::HEARTBEAT, true);
    Heartbeat heartbeat(5800);
    boost::thread heartbeatThread(boost::bind(&Heartbeat::run, heartbeat));

    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_SUB);
    socket.setsockopt(ZMQ_RCVTIMEO, 10000);
    socket.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    socket.connect("tcp://127.0.0.1:5800");
    ASSERT_EQ(s_recv(socket), "1");
    socket.close();
    ThreadManager::set(ThreadManager::Thread::HEARTBEAT, false);
    heartbeatThread.join();
}

TEST(networking_tests, data_sender_bad_data_test) {
    ThreadManager::set(ThreadManager::Thread::DATA_SENDER, true);
    DataSender dataSender(5800);
    boost::thread dataSenderThread(boost::bind(&DataSender::run, dataSender));

    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_SUB);
    socket.setsockopt(ZMQ_RCVTIMEO, 10000);
    socket.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    socket.connect("tcp://127.0.0.1:5800");
    bool addFlag = true;
    boost::thread dataAdderThread(boost::bind(&dataAdder, 0, false, &addFlag));
    ASSERT_EQ(s_recv(socket), "");
    addFlag = false;
    socket.close();
    ThreadManager::set(ThreadManager::Thread::DATA_SENDER, false);
    dataSenderThread.join();
}

TEST(networking_tests, data_sender_good_data_test) {
    ThreadManager::set(ThreadManager::Thread::DATA_SENDER, true);
    DataSender dataSender(5800);
    boost::thread dataSenderThread(boost::bind(&DataSender::run, dataSender));

    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_SUB);
    socket.setsockopt(ZMQ_RCVTIMEO, 10000);
    socket.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    socket.connect("tcp://127.0.0.1:5800");
    bool addFlag = true;
    boost::thread dataAdderThread(boost::bind(&dataAdder, 0, true, &addFlag));
    ASSERT_EQ(s_recv(socket), "-1.000000,-1.000000,-1.000000");
    addFlag = false;
    socket.close();
    ThreadManager::set(ThreadManager::Thread::DATA_SENDER, false);
    dataSenderThread.join();
}


TEST(networking_tests, frame_sender_test) {
    ThreadManager::set(ThreadManager::Thread::FRAME_SENDER, true);
    FrameSender frameSender(5800);
    boost::thread frameSenderThread(boost::bind(&FrameSender::run, frameSender));

    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_SUB);
    socket.setsockopt(ZMQ_RCVTIMEO, 10000);
    socket.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    socket.connect("tcp://127.0.0.1:5800");
    bool addFlag = true;
    boost::thread dataAdderThread(boost::bind(&dataAdder, 1, true, &addFlag));
    string recvData = s_recv(socket);
    addFlag = false;
    vector<uchar> buff(recvData.begin(), recvData.end());
    cv::Mat decodedData = cv::imdecode(buff, 0);
    ASSERT_EQ(decodedData.at<cv::Vec3b>(10,10)[0], 0);
    ASSERT_EQ(decodedData.at<cv::Vec3b>(10,10)[1], 0);
    ASSERT_EQ(decodedData.at<cv::Vec3b>(10,10)[2], 0);
    socket.close();
    ThreadManager::set(ThreadManager::Thread::FRAME_SENDER, false);
    frameSenderThread.join();
}