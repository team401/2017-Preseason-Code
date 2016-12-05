//
// Created by cameronearle on 12/5/16.
//

#include "ThreadManager.hpp"

std::atomic<bool> ThreadManager::GLOBAL_RUNNING(true);
std::atomic<bool> ThreadManager::CANNY_DETECTOR_RUNNING(true);
std::atomic<bool> ThreadManager::FRAME_SENDER_RUNNING(true);

void ThreadManager::set(Thread thread_, bool value_) {
    switch (thread_) {
        case GLOBAL:
            GLOBAL_RUNNING = value_;
            break;
        case CANNY_DETECTOR:
            CANNY_DETECTOR_RUNNING = value_;
            break;
        case FRAME_SENDER:
            FRAME_SENDER_RUNNING = value_;
            break;
    }
}

bool ThreadManager::get(Thread thread_) {
    switch (thread_) {
        case GLOBAL:
            return GLOBAL_RUNNING;
        case CANNY_DETECTOR:
            return (GLOBAL_RUNNING && CANNY_DETECTOR_RUNNING);
        case FRAME_SENDER:
            return (GLOBAL_RUNNING && FRAME_SENDER_RUNNING);
    }
}