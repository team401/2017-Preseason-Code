//
// Created by cameronearle on 12/3/16.
//
#include "CameraSettings.hpp"
#include <libv4l2.h>
#include <linux/videodev2.h>
#include <fcntl.h>
#include "dataLogging/Log.hpp"


CameraSettings::CameraSettings(char *uri) {
    descriptor = v4l2_open(uri, O_RDWR);
    validity = true;
}

bool CameraSettings::finish() {
    v4l2_close(descriptor);
    return validity;
}

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