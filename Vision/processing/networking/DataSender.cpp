//
// Created by cameronearle on 12/6/16.
//

#include "DataSender.hpp"

#include <string>
#include "zhelpers.hpp"
#include "boost/thread/thread.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "../ThreadManager.hpp"
#include <iostream>

using namespace std;

boost::lockfree::spsc_queue<std::vector<float>> DataSender::sendQueue(512);

void DataSender::run() {
    zmq::context_t context(1); //Create a context to store our socket
    zmq::socket_t socket(context, ZMQ_PUB); //Create a publisher socket to send data
    socket.bind("tcp://*:" + std::to_string(port)); //Bind the socket to all interfaces
    vector<float> latestData;
    string dataToSend;
    while (ThreadManager::get(ThreadManager::Thread::DATA_SENDER)) { //While the threadmanager says this thread should run
        while (sendQueue.pop(latestData)) { //While there is data in the queue
            if (latestData.size() < 3) { //If the data is not in the correct format
                break; //Skip this data and move on to the next set
            }
            dataToSend = to_string(latestData[0]) + "," + to_string(latestData[1]) + "," + to_string(latestData[2]); //Stage our data in CSV format
            s_send(socket, dataToSend); //Send the data out
        }
        boost::this_thread::sleep(boost::posix_time::milliseconds(10)); //Keep the CPU load reasonable
    }
}


void DataSender::addToQueue(std::vector<float> data_) {
    sendQueue.push(data_); //Add the given data to our threadsafe queue
}