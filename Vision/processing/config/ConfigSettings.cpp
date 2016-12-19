//
// Created by cameronearle on 12/9/16.
//
#include "ConfigSettings.hpp"
#include "../camera/CameraSettings.hpp"
#include "../dataLogging/Log.hpp"
#include "../ThreadManager.hpp"

#include <string>

using namespace std;

bool ConfigSettings::setCamera() {
    return CameraSettings(getDeviceNumber())
            .autoExposure(autoExposure)
            .autoWB(autoWB)
            .autoGain(autoGain)
            .setExposure(exposure)
            .setSaturation(saturation)
            .setContrast(contrast)
            .setGain(gain)
            .finish();
}

cv::VideoCapture ConfigSettings::getCapture() {
    cv::VideoCapture cap;
    cap.open(deviceNumber);
    if (!cap.isOpened()) {
        Log::x(ld, "Couldn't open device number " + to_string(deviceNumber));
        ThreadManager::set(ThreadManager::Thread::GLOBAL, false); //Stop the global thread, this should happen before any threads start, but just in case
        exit(0xDEADBEEF); //Dead Beef is the best beef
    }
    return cap;
}