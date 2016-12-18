//
// Created by cameronearle on 12/17/16.
//

#include "Heartbeat.hpp"
#include "zhelpers.hpp"
#include "boost/thread/thread.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "../ThreadManager.hpp"

void Heartbeat::run() {
    zmq::context_t context(1); //Create a context to store our socket
    zmq::socket_t socket(context, ZMQ_PUB); //Create a publisher socket to send data
    socket.bind("tcp://*:" + std::to_string(port)); //Bind the socket to all interfaces
    while (ThreadManager::get(ThreadManager::Thread::HEARTBEAT)) { //While the threadmanager says this thread should run
        s_send(socket, "1"); //Send the data out
        boost::this_thread::sleep(boost::posix_time::seconds(5)); //Send a heartbeat every 5 seconds
    }
}