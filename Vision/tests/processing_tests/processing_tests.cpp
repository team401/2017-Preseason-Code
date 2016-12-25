//
// Created by cameronearle on 12/21/16.
//

#include <zmq.hpp>
#include <boost/thread.hpp>
#include <zhelpers.hpp>
#include "gtest/gtest.h"
#include "../../processing/src/imgProc/VisionProcessing.hpp"
#include "../../processing/src/imgProc/CreateShapes.hpp"
#include "../../processing/src/networking/DataSender.hpp"
#include "../../processing/src/ThreadManager.hpp"
#include "../../processing/src/config/ConfigSettings.hpp"

TEST(processing_tests, processing_main_test) {
    ThreadManager::set(ThreadManager::Thread::DATA_SENDER, true);
    ThreadManager::set(ThreadManager::CANNY_DETECTOR, true);
    ThreadManager::set(ThreadManager::Thread::GLOBAL, true);

    ConfigSettings configSettings;
    configSettings.setNetworkDataPort(5800);
    configSettings.setLowerBoundH(50);
    configSettings.setLowerBoundS(250);
    configSettings.setLowerBoundV(40);
    configSettings.setUpperBoundH(70);
    configSettings.setUpperBoundS(255);
    configSettings.setUpperBoundV(254);
    configSettings.setCannyLowerBound(30);
    configSettings.setCannyUpperBound(60);
    configSettings.setDebugMode(false);

    MathData mathData; //Calculation value holder
    mathData.setFOV((57 * 3.141592) / 180);
    mathData.setCy((480 / 2) - 0.5);
    mathData.setCx((640 / 2) - 0.5);
    mathData.setFocalLength(480 / (2*tan(mathData.getFOV()/2)));

    cv::VideoCapture cap;
    cap.open("res/goal.mov");

    VisionProcessing visionProcessing(configSettings, cap, mathData);
    DataSender dataSender(configSettings.getNetworkDataPort());

    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_SUB);
    socket.setsockopt(ZMQ_RCVTIMEO, 10000);
    socket.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    socket.connect("tcp://127.0.0.1:5800");

    boost::thread(boost::bind(&VisionProcessing::run, visionProcessing));
    boost::thread(boost::bind(&DataSender::run, dataSender));


    ASSERT_EQ(s_recv(socket), "-11.889844,-10.984375,-45.335907"); //Alright the yaw is completely screwed

    ThreadManager::set(ThreadManager::Thread::GLOBAL, false);
    socket.close();
    cap.release();
}

TEST(processing_tests, processing_createshapes_bad_data_test) {
    cv::Mat mat;
    vector<cv::Point> result = CreateShapes::shapes(mat, 1, vector<vector<cv::Point>>());
    ASSERT_EQ(result[0], cv::Point(-1, -1));
    ASSERT_EQ(result[1], cv::Point(-1, -1));
    ASSERT_EQ(result[2], cv::Point(-1, -1));
}

TEST(processing_tests, processing_createshapes_good_data_test) {
    cv::Mat mat;
    vector<vector<cv::Point>> contours({{cv::Point(10, 10), cv::Point(20, 20)}});
    vector<cv::Point> result = CreateShapes::shapes(mat, 0, contours, false);
    ASSERT_EQ(result[0], cv::Point(15, 15));
    ASSERT_EQ(result[1], cv::Point(10, 10));
    ASSERT_EQ(result[2], cv::Point(21, 21));
}