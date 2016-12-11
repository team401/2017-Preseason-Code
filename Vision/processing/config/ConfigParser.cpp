//
// Created by cameronearle on 12/8/16.
//

#include "ConfigParser.hpp"

#include <ios>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include "../dataLogging/Log.hpp"

using namespace std;

vector<string> ConfigParser::splitElements(string str, char delimiter) {
    vector<string> internal;
    stringstream ss(str); //This just works, stackoverflow is very convenient
    string tok;

    while(getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }

    return internal;
}

ConfigParser::ConfigParser(vector<string> clargs, string filePath_) {
    vector<string> splitArgs;
    for (string s : clargs) {
        splitArgs = splitElements(s);
        if (splitArgs.size() == 2) {
            Log::i(ld, "Found command line argument [" + splitArgs[0] + "] with value [" + splitArgs[1] + "]");
            finalSettings.insert(make_pair(splitArgs[0], splitArgs[1]));
        }
    }
    Log::d(ld, "Parsing Config");
    filePath = filePath_;
    file.open(filePath_); //Open the config file for reading
    if (!file.good()) { //If the config file doesn't exist
        Log::w(ld, "Config doesn't exist, creating it!");
        ofstream writeFile;
        writeFile.open(filePath_);
        for (pair<string, string> toAppend : defaults) {
            writeFile << toAppend.first << "=" << toAppend.second << "\n"; //Append the default value to the config
        }
        writeFile.close();
        Log::d(ld, "Config created with defaults");
        finalSettings = defaults;
        return;
    }
    string currentLine;
    vector<string> splitLine;
    while (getline(file, currentLine)) { //Iterate the file by lines
        splitLine = splitElements(currentLine);
        if (splitLine.size() == 2) {
            if (finalSettings.find(splitLine[0]) == finalSettings.end()) { //Make sure we aren't overriding command line args
                finalSettings.insert(make_pair(splitLine[0], splitLine[1])); //Put each line into a map
            }
        }
    }
    file.close();
    Log::d(ld, "Config read successfully");
}

template <class T>
T ConfigParser::configFind(string key_) { //We return the lexical type
    if (finalSettings.find(key_) != finalSettings.end()) { //If the key is in the map
        Log::d(ld, "Found value [" + finalSettings[key_] + "] for key [" + key_ + "]");
        /*
        try {
            return boost::lexical_cast<T>(finalSettings[key_]);
        } catch (...) {
            Log::e(ld, "Couldn't lexically cast key [" + key_ + "] to class [" + typeid(T).name() + "]");
            return NULL;
        }
         */

        return boost::lexical_cast<T>(finalSettings[key_]);
    } else {
        Log::w(ld, "Couldn't find value with key [" + key_ + "], using default");
        if (defaults.find(key_) == defaults.end()) {
            Log::wtfomgy(ld, "Couldn't find value with key [" + key_ + "] in defaults. This is a problem!");
            return NULL;
        }
        ofstream writeFile;
        writeFile.open(filePath, ios::app);
        writeFile << key_ << "=" << defaults[key_] << "\n"; //Write the default to the config
        writeFile.close();
        Log::d(ld, "Wrote missing value [" + defaults[key_] + "] for key [" + key_ + "] to the config");
        try {
            return boost::lexical_cast<T>(defaults[key_]);
        } catch (...) {
            Log::e(ld, "Couldn't lexically cast DEFAULT key [" + key_ + "] to class [" + typeid(T).name() + "]");
            return NULL;
        }
    }
}

ConfigSettings ConfigParser::getSettings() {
    ConfigSettings configSettings;
    configSettings.setAutoExposure(configFind<bool>("autoExposure"));
    configSettings.setAutoWB(configFind<bool>("autoWB"));
    configSettings.setAutoGain(configFind<bool>("autoGain"));
    configSettings.setExposure(configFind<int>("exposure"));
    configSettings.setSaturation(configFind<int>("saturation"));
    configSettings.setContrast(configFind<int>("contrast"));
    configSettings.setGain(configFind<int>("gain"));
    configSettings.setLowerBoundH(configFind<int>("lowerBoundH"));
    configSettings.setLowerBoundS(configFind<int>("lowerBoundS"));
    configSettings.setLowerBoundV(configFind<int>("lowerBoundV"));
    configSettings.setUpperBoundH(configFind<int>("upperBoundH"));
    configSettings.setUpperBoundS(configFind<int>("upperBoundS"));
    configSettings.setUpperBoundV(configFind<int>("upperBoundV"));
    configSettings.setCannyLowerBound(configFind<int>("cannyLowerBound"));
    configSettings.setCannyUpperBound(configFind<int>("cannyUpperBound"));

    return configSettings;
}
