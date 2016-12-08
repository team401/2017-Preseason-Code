//
// Created by cameronearle on 12/5/16.
//

#ifndef INC_2017_PRESEASON_CODE_LOG_HPP
#define INC_2017_PRESEASON_CODE_LOG_HPP

#include <string>
#include <mutex>
#include <fstream>

using namespace std;

class Log {
public:
    enum Level {
        DEBUG=0,
        INFO=1,
        WARNING=2,
        ERROR=3,
        EXCEPTION=4
    };
    static void init(Level level_, bool useFile_, std::string filePath_="vision.log");
    static void d(string ld_, std::string data_); //DEBUG
    static void i(string ld_, std::string data_); //INFO
    static void w(string ld_, std::string data_); //WARNING
    static void e(string ld_, std::string data_); //ERROR
    static void x(string ld_, std::string data_); //EXCEPTION
    static void wtfomgy(string ld_, string data_); //WHAT THE FRICK, OH MY GOD WHY?
    static void close();
private:
    static string getDateTime();
    static void writeToFile(string outString_);
    static bool useFile;
    static Level useLevel;
    static mutex fileLock;
    static ofstream file;
};


#endif //INC_2017_PRESEASON_CODE_LOG_HPP
