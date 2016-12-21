//
// Created by cameronearle on 12/8/16.
//

#ifndef INC_2017_PRESEASON_CODE_CONFIGPARSER_HPP
#define INC_2017_PRESEASON_CODE_CONFIGPARSER_HPP

#include <string>
#include <fstream>
#include <vector>
#include <map>
#include "ConfigSettings.hpp"

using namespace std;

class ConfigParser {
public :
    ConfigParser(vector<string> clargs, string filePath_="config.txt");
    ConfigSettings getSettings();
private:
    vector<string> splitElements(string str, char delimiter='=');
    ifstream file;
    map<string, string> defaults = { //DEFAULTS LIST
            make_pair("autoExposure", "0"),
            make_pair("autoWB", "0"),
            make_pair("autoGain", "0"),
            make_pair("exposure", "20"),
            make_pair("saturation", "255"),
            make_pair("contrast", "0"),
            make_pair("gain", "20"),
            make_pair("lowerBoundH", "50"),
            make_pair("lowerBoundS", "250"),
            make_pair("lowerBoundV", "40"),
            make_pair("upperBoundH", "70"),
            make_pair("upperBoundS", "255"),
            make_pair("upperBoundV", "160"),
            make_pair("cannyLowerBound", "30"),
            make_pair("cannyUpperBound", "60"),
            make_pair("debugMode", "1"),
            make_pair("deviceNumber", "0"),
            make_pair("networkImagePort", "5801"),
            make_pair("networkDataPort", "5802"),
            make_pair("networkHeartbeatPort", "5800")
    };
    map<string, string> finalSettings;
    template <class T>
    T configFind(string key_);
    bool validity;
    string filePath;
    string ld = "ConfigParser";
};


#endif //INC_2017_PRESEASON_CODE_CONFIGPARSER_HPP
