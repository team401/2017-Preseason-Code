//
// Created by cameronearle on 12/5/16.
//

#ifndef INC_2017_PRESEASON_CODE_LOG_HPP
#define INC_2017_PRESEASON_CODE_LOG_HPP

#include <string>


class Log {
public:
    static void init();
    static void d(std::string ld_, std::string data_); //DEBUG
    static void i(std::string ld_, std::string data_); //INFO
    static void w(std::string ld_, std::string data_); //WARNING
    static void e(std::string ld_, std::string data_); //ERROR
    static void x(std::string ld_, std::string data_); //EXCEPTION
    static void wtfomgy(std::string ld_, std::string data_); //WHAT THE F**K, OH MY GOD WHY?
private:
    static std::string getDateTime();
    static void writeToFile(std::string outString_);
    static bool useFile;
};


#endif //INC_2017_PRESEASON_CODE_LOG_HPP
