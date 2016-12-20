//
// Created by cameronearle on 12/8/16.
//

#ifndef INC_2017_PRESEASON_CODE_CONFIGSETTINGS_HPP
#define INC_2017_PRESEASON_CODE_CONFIGSETTINGS_HPP

#include <string>
#include <opencv2/opencv.hpp>
#include "opencv2/core.hpp"

//This class follows the "JavaBean" format

using namespace std;

class ConfigSettings {
private:
    string ld = "ConfigSettings";
    //DECLARATIONS
    bool autoExposure;
    bool autoWB;
    bool autoGain;
    int exposure;
    int saturation;
    int contrast;
    int gain;
    int lowerBoundH;
    int lowerBoundS;
    int lowerBoundV;
    int upperBoundH;
    int upperBoundS;
    int upperBoundV;
    int cannyLowerBound;
    int cannyUpperBound;
    bool debugMode;
    int deviceNumber;
    int networkImagePort;
    int networkDataPort;
    int networkHeartbeatPort;
    //END DECLARATIONS
public:
    ConfigSettings(){}
    bool setCamera();
    cv::VideoCapture getCapture();
    ConfigSettings(
                   //CONSTRUCTOR ARGUMENTS
                   bool autoExposure_,
                   bool autoWB_,
                   bool autoGain_,
                   int exposure_,
                   int saturation_,
                   int contrast_,
                   int gain_,
                   int lowerBoundH_,
                   int lowerBoundS_,
                   int lowerBoundV_,
                   int upperBoundH_,
                   int upperBoundS_,
                   int upperBoundV_,
                   int cannyLowerBound_,
                   int cannyUpperBound_,
                   bool debugMode_,
                   int deviceNumber_,
                   int networkImagePort_,
                   int networkDataPort_,
                   int networkHeartbeatPort_
                   //END CONSTRUCTOR ARGUMENTS
    ) {
        //CONSTRUCTOR DECLARATIONS
        autoExposure = autoExposure_;
        autoWB = autoWB_;
        autoGain = autoGain_;
        exposure = exposure_;
        saturation = saturation_;
        contrast = contrast_;
        gain = gain_;
        lowerBoundH = lowerBoundH_;
        lowerBoundS = lowerBoundS_;
        lowerBoundV = lowerBoundV_;
        upperBoundH = upperBoundH_;
        upperBoundS = upperBoundS_;
        upperBoundV = upperBoundV_;
        cannyLowerBound = cannyLowerBound_;
        cannyUpperBound = cannyUpperBound_;
        deviceNumber = deviceNumber_;
        networkImagePort = networkImagePort_;
        networkDataPort = networkDataPort_;
        networkHeartbeatPort = networkHeartbeatPort_;
        //END CONSTRUCTOR DECLARATIONS
    }
    //ACCESSORS
    bool getAutoExposure() { return autoExposure; }
    void setAutoExposure(bool autoExposure_) { autoExposure = autoExposure_; }
    bool getAutoWB() { return autoWB; }
    void setAutoWB(bool autoWB_) { autoWB = autoWB_; }
    bool getAutoGain() { return autoGain; }
    void setAutoGain(bool autoGain_) { autoGain = autoGain_; }
    int getExposure() { return exposure; }
    void setExposure(int exposure_) { exposure = exposure_; }
    int getSaturation() { return saturation; }
    void setSaturation(int saturation_) { saturation = saturation_; }
    int getContrast() { return contrast; }
    void setContrast(int contrast_) { contrast = contrast_; }
    int getGain() { return gain; }
    void setGain(int gain_) { gain = gain_; }
    cv::Scalar getLowerBound() {
        return cv::Scalar(lowerBoundH, lowerBoundS, lowerBoundV);
    }
    cv::Scalar getUpperBound() {
        return cv::Scalar(upperBoundH, upperBoundS, upperBoundV);
    }
    void setLowerBoundH(int lowerBoundH_) { lowerBoundH = lowerBoundH_; }
    void setLowerBoundS(int lowerBoundS_) { lowerBoundS = lowerBoundS_; }
    void setLowerBoundV(int lowerBoundV_) { lowerBoundV = lowerBoundV_; }
    void setUpperBoundH(int upperBoundH_) { upperBoundH = upperBoundH_; }
    void setUpperBoundS(int upperBoundS_) { upperBoundS = upperBoundS_; }
    void setUpperBoundV(int upperBoundV_) { upperBoundV = upperBoundV_; }
    int getCannyLowerBound() { return cannyLowerBound; }
    void setCannyLowerBound(int cannyLowerBound_) { cannyLowerBound = cannyLowerBound_; }
    int getCannyUpperBound() { return cannyUpperBound; }
    void setCannyUpperBound(int cannyUpperBound_) { cannyUpperBound = cannyUpperBound_; }
    bool getDebugMode() { return debugMode; }
    void setDebugMode(bool debugMode_) { debugMode = debugMode_; }
    int getDeviceNumber() { return deviceNumber; }
    void setDeviceNumber(int deviceNumber_) { deviceNumber = deviceNumber_; }
    int getNetworkImagePort() { return networkImagePort; }
    void setNetworkImagePort(int networkImagePort_) { networkImagePort = networkImagePort_; }
    int getNetworkDataPort() { return networkDataPort; }
    void setNetworkDataPort(int networkDataPort_) { networkDataPort = networkDataPort_; }
    int getNetworkHeartbeatPort() { return networkHeartbeatPort; }
    void setNetworkHeartbeatPort(int networkHeartbeatPort_) { networkHeartbeatPort = networkHeartbeatPort_; }
    //END ACCESSORS
};


#endif //INC_2017_PRESEASON_CODE_CONFIGSETTINGS_HPP
