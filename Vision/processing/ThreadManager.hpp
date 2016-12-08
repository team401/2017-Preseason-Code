//
// Created by cameronearle on 12/4/16.
//

#ifndef INC_2017_PRESEASON_CODE_THREADS_HPP
#define INC_2017_PRESEASON_CODE_THREADS_HPP

#include <atomic>
#include <string>

using namespace std;

class ThreadManager {
public:
    enum Thread {
        GLOBAL,
        CANNY_DETECTOR,
        FRAME_SENDER,
        DATA_SENDER
    };
    static void set(Thread thread_, bool value_);
    static bool get(Thread thread_);
private:
    static atomic<bool> GLOBAL_RUNNING;
    static atomic<bool> CANNY_DETECTOR_RUNNING;
    static atomic<bool> FRAME_SENDER_RUNNING;
    static atomic<bool> DATA_SENDER_RUNNING;
    static string ld;
};

#endif //INC_2017_PRESEASON_CODE_THREADS_HPP
