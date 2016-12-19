#ifndef INC_2017_PRESEASON_CODE_THREADS_HPP
#define INC_2017_PRESEASON_CODE_THREADS_HPP

#include <atomic>
#include <string>

using namespace std;

class ThreadManager {
public:
    enum Thread { //A list of the different threads in our program
        GLOBAL,
        CANNY_DETECTOR,
        FRAME_SENDER,
        DATA_SENDER,
        HEARTBEAT
    };
    static void set(Thread thread, bool value_);
    static bool get(Thread thread);
private:
    static atomic<bool> GLOBAL_RUNNING;
    static atomic<bool> CANNY_DETECTOR_RUNNING;
    static atomic<bool> FRAME_SENDER_RUNNING;
    static atomic<bool> DATA_SENDER_RUNNING;
    static atomic<bool> HEARTBEAT_RUNNING;
    static string ld;
};

#endif //INC_2017_PRESEASON_CODE_THREADS_HPP
