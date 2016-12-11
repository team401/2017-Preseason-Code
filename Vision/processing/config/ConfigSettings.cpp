//
// Created by cameronearle on 12/9/16.
//
#include "ConfigSettings.hpp"
#include "../camera/CameraSettings.hpp"

#include <string>

using namespace std;

bool ConfigSettings::setCamera(char* descriptor) {
    CameraSettings(descriptor)
            .autoExposure(autoExposure)
            .autoWB(autoWB)
            .autoGain(autoGain)
            .setExposure(exposure)
            .setSaturation(saturation)
            .setContrast(contrast)
            .setGain(gain)
            .finish();
}