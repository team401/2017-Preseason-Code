//
// Created by cameronearle on 12/3/16.
//

#ifndef INC_2017_PRESEASON_CODE_LOG_HPP
#define INC_2017_PRESEASON_CODE_LOG_HPP
#include "string"
#include "iostream"

struct Log {
    static void d(std::string prefix, std::string data) {
        std::cout << "DEBUG: " << prefix << ": " << data << std::endl;
    }

    static void e(std::string prefix, std::string data) {
        std::cout << "ERROR: " << prefix << ": " << data << std::endl;
    }
};

#endif //INC_2017_PRESEASON_CODE_LOG_HPP
