//
// Created by cameronearle on 12/3/16.
//

#ifndef INC_2017_PRESEASON_CODE_CAMERASETTINGS_HPP
#define INC_2017_PRESEASON_CODE_CAMERASETTINGS_HPP

#include "string"

class CameraSettings {
public:
    CameraSettings(char* uri);
    bool finish();

    CameraSettings autoExposure(bool set);
    CameraSettings autoWB(bool set);
private:
    int descriptor;
    bool validity;
    std::string ld = "CameraSettings";
};


#endif //INC_2017_PRESEASON_CODE_CAMERASETTINGS_HPP
