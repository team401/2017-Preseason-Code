//
// Created by cameronearle on 12/17/16.
//

#ifndef INC_2017_PRESEASON_CODE_HEARTBEAT_HPP
#define INC_2017_PRESEASON_CODE_HEARTBEAT_HPP


class Heartbeat {
public:
    Heartbeat(int port_) {
        port = port_;
    }
    void run();
private:
    int port;
};


#endif //INC_2017_PRESEASON_CODE_HEARTBEAT_HPP
