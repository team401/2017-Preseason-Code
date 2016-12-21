#include "ThreadManager.hpp"
#include "dataLogging/Log.hpp"

using namespace std;

//Atomic booleans to store whether or not the threads are running
std::atomic<bool> ThreadManager::GLOBAL_RUNNING(true);
std::atomic<bool> ThreadManager::CANNY_DETECTOR_RUNNING(true);
std::atomic<bool> ThreadManager::FRAME_SENDER_RUNNING(true);
std::atomic<bool> ThreadManager::DATA_SENDER_RUNNING(true);
std::atomic<bool> ThreadManager::HEARTBEAT_RUNNING(true);
//Log descriptor so the logger knows what class this is
std::string ThreadManager::ld = "ThreadManager";

/* Function set
 * Argument [Thread thread_]: The thread to change
 * Argument [bool value_]: The value to set the thread to
 * Description: Sets the thread flags to the given value
 */
void ThreadManager::set(Thread thread, bool value_) {
    switch (thread) { //Which thread are we given
        /* case THREAD_NAME: //The thread we want to change
         *     THREAD_NAME = value_; //Set the given thread to the value
         *     Log::d(...) //Log the event
         *     break;
         */
        case GLOBAL:
            GLOBAL_RUNNING = value_;
            Log::d(ld, "Set thread GLOBAL to " + to_string(value_));
            break;
        case CANNY_DETECTOR:
            CANNY_DETECTOR_RUNNING = value_;
            Log::d(ld, "Set thread CANNY_DETECTOR to " + to_string(value_));
            break;
        case FRAME_SENDER:
            FRAME_SENDER_RUNNING = value_;
            Log::d(ld, "Set thread FRAME_SENDER to " + to_string(value_));
            break;
        case DATA_SENDER:
            DATA_SENDER_RUNNING = value_;
            Log::d(ld, "Set thread DATA_SENDER to " + to_string(value_));
            break;
        case HEARTBEAT:
            HEARTBEAT_RUNNING = value_;
            Log::d(ld, "Set thread HEARTBEAT to " + to_string(value_));
            break;

    }
}

/* Function get
 * Argument [Thread thread]: The thread to get
 * Description: Gets a standard boolean for the status of the given thread, mixed with the global value if applicable
 * Returns [bool]: The value for the given thread
 */
bool ThreadManager::get(Thread thread) {
    switch (thread) { //Which thread are we given
        /* case THREAD_NAME:
         *     return (GLOBAL_RUNNING && THREAD_NAME_RUNNING) //Return the and operation between the global thread and the given thread
         */
        case GLOBAL:
            return GLOBAL_RUNNING;
        case CANNY_DETECTOR:
            return (GLOBAL_RUNNING && CANNY_DETECTOR_RUNNING);
        case FRAME_SENDER:
            return (GLOBAL_RUNNING && FRAME_SENDER_RUNNING);
        case DATA_SENDER:
            return (GLOBAL_RUNNING && DATA_SENDER_RUNNING);
        case HEARTBEAT:
            return (GLOBAL_RUNNING && HEARTBEAT_RUNNING);
    }
}