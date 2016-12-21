//
// Created by cameronearle on 12/3/16.
//
#include "CameraSettings.hpp"
#include <libv4l2.h>
#include <linux/videodev2.h>
#include <fcntl.h>
#include "../dataLogging/Log.hpp"


CameraSettings::CameraSettings(int id) {
    descriptor = v4l2_open(("/dev/video" + std::to_string(id)).c_str(), O_RDWR); //A number that linux uses to reference the camera object
    validity = true; //While our settings are still valid
}

bool CameraSettings::finish() {
    v4l2_close(descriptor); //Close the camera file
    return validity;
}

CameraSettings CameraSettings::set(int setting, int set) {
    if (!validity) { //If previous settings didn't succeed
        Log::w(ld, "Didn't set camera setting " + std::to_string(setting) + " because another setting failed");
        return *this; //We always return an instance of ourself so we can string commands
    }
    v4l2_control c; //A video4linux control that we will use to change a specific setting
    c.id = setting;
    c.value = set;
    if(v4l2_ioctl(descriptor, VIDIOC_S_CTRL, &c) == 0) { //Try to modify the setting and see if it worked
        Log::i(ld, "Modified property " + std::to_string(setting) + " to value " + std::to_string(set));
    } else { //It didn't work
        Log::e(ld, "Failed to modify property " + std::to_string(setting));
        validity = false; //This will break all future settings to make you fix your mistake
    }
    return *this;
}

//Read comments above for structure, it's all exactly the same

CameraSettings CameraSettings::autoExposure(bool set) {
    if (!validity) {
        Log::w(ld, "Didn't set camera setting AUTO_EXPOSURE because another setting failed");
        return *this;
    }
    v4l2_control c;
    c.id = V4L2_CID_EXPOSURE_AUTO;
    if (set) {
        c.value = V4L2_EXPOSURE_AUTO;
    } else {
        c.value = V4L2_EXPOSURE_MANUAL;
    }
    if(v4l2_ioctl(descriptor, VIDIOC_S_CTRL, &c) == 0) {
        Log::i(ld, "Modified property AUTO_EXPOSURE to value " + std::to_string(set));
    } else {
        Log::e(ld, "Failed to modify property AUTO_EXPOSURE");
        validity = false;
    }
    return *this;
}

CameraSettings CameraSettings::autoWB(bool set) {
    if (!validity) {
        Log::w(ld, "Didn't set camera setting AUTO_WHITE_BALANCE because another setting failed");
        return *this;
    }
    v4l2_control c;
    c.id = V4L2_CID_AUTO_WHITE_BALANCE;
    if (set) {
        c.value = V4L2_WHITE_BALANCE_AUTO;
    } else {
        c.value = V4L2_WHITE_BALANCE_MANUAL;
    }
    if(v4l2_ioctl(descriptor, VIDIOC_S_CTRL, &c) == 0) {
        Log::i(ld, "Modified property AUTO WHITE BALANCE to value " + std::to_string(set));
    } else {
        Log::e(ld, "Failed to modify property AUTO WHITE BALANCE");
        validity = false;
    }
    return *this;
}

CameraSettings CameraSettings::autoGain(bool set) {
    if (!validity) {
        Log::w(ld, "Didn't set camera setting AUTO_GAIN because another setting failed");
        return *this;
    }
    v4l2_control c;
    c.id = V4L2_CID_AUTOGAIN;
    c.value = set;
    if(v4l2_ioctl(descriptor, VIDIOC_S_CTRL, &c) == 0) {
        Log::i(ld, "Modified property AUTO_GAIN to value " + std::to_string(set));
    } else {
        Log::e(ld, "Failed to modify property AUTO_GAIN");
        validity = false;
    }
    return *this;
}

CameraSettings CameraSettings::setExposure(int set){
    if (!validity) {
        Log::w(ld, "Didn't set camera setting EXPOSURE because another setting failed");
        return *this;
    }
    v4l2_control c;
    c.id = V4L2_CID_EXPOSURE;
    c.value = set;
    if(v4l2_ioctl(descriptor, VIDIOC_S_CTRL, &c) == 0) {
        Log::i(ld, "Modified property EXPOSURE to value " + std::to_string(set));
    } else {
        Log::e(ld, "Failed to modify property EXPOSURE");
        validity = false;
    }
    return *this;
}

CameraSettings CameraSettings::setSaturation(int set){
    if (!validity) {
        Log::w(ld, "Didn't set camera setting SATURATION because another setting failed");
        return *this;
    }
    v4l2_control c;
    c.id = V4L2_CID_SATURATION;
    c.value = set;
    if(v4l2_ioctl(descriptor, VIDIOC_S_CTRL, &c) == 0) {
        Log::i(ld, "Modified property SATURATION to value " + std::to_string(set));
    } else {
        Log::e(ld, "Failed to modify property SATURATION");
        validity = false;
    }
    return *this;
}

CameraSettings CameraSettings::setContrast(int set){
    if (!validity) {
        Log::w(ld, "Didn't set camera setting CONTRAST because another setting failed");
        return *this;
    }
    v4l2_control c;
    c.id = V4L2_CID_CONTRAST;
    c.value = set;
    if(v4l2_ioctl(descriptor, VIDIOC_S_CTRL, &c) == 0) {
        Log::i(ld, "Modified property CONTRAST to value " + std::to_string(set));
    } else {
        Log::e(ld, "Failed to modify property CONTRAST");
        validity = false;
    }
    return *this;
}

CameraSettings CameraSettings::setGain(int set){
    if (!validity) {
        Log::w(ld, "Didn't set camera setting GAIN because another setting failed");
        return *this;
    }
    v4l2_control c;
    c.id = V4L2_CID_GAIN;
    c.value = set;
    if(v4l2_ioctl(descriptor, VIDIOC_S_CTRL, &c) == 0) {
        Log::i(ld, "Modified property GAIN to value " + std::to_string(set));
    } else {
        Log::e(ld, "Failed to modify property GAIN");
        validity = false;
    }
    return *this;
}