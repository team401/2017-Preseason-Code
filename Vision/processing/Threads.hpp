//
// Created by cameronearle on 12/4/16.
//

#ifndef INC_2017_PRESEASON_CODE_THREADS_HPP
#define INC_2017_PRESEASON_CODE_THREADS_HPP

#include <atomic>

enum ThreadName {
    GLOBAL,
    CANNY_DETECTOR,
    FRAME_SENDER
};

namespace VisionThreads {
    static std::atomic<bool> GLOBAL_RUNNING(true);
    static std::atomic<bool> FRAME_SENDER_RUNNING(true);
    static std::atomic<bool> CANNY_DETECTOR_RUNNING(true);

    static void set(ThreadName name, bool value) {
        switch (name) {
            case GLOBAL:
                GLOBAL_RUNNING = value;
                break;
            case CANNY_DETECTOR:
                CANNY_DETECTOR_RUNNING = value;
                break;
            case FRAME_SENDER:
                FRAME_SENDER_RUNNING = value;
                break;
        }
    }

    static bool get(ThreadName name) {
        switch (name) {
            case GLOBAL:
                return GLOBAL_RUNNING;
            case CANNY_DETECTOR:
                return (CANNY_DETECTOR_RUNNING && GLOBAL_RUNNING);
            case FRAME_SENDER:
                return (FRAME_SENDER_RUNNING && GLOBAL_RUNNING);
        }
    }
}

#endif //INC_2017_PRESEASON_CODE_THREADS_HPP
