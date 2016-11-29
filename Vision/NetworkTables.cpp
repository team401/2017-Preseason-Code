/*
 * Class NetworkTables.hpp created by Liam Lawrence on 11.29.16
 * Header for NetworkTables.cpp
 */

#include "NetworkTables.hpp"
//#include "networktables/NetworkTable.h"   TODO build binaries for this (need ARM)

// Sends the data from the Jetson to the RoboRIO
void NetworkTables::sendData(float xDif, float yDif, float yaw, float pitch){
    NetworkTable::SetClientMode();  // Should we do this only once?
    NetworkTable::SetTeam(401);     // Maybe put in initialization of CannyDetector?

    auto table = NetworkTable::GetTable("visionTable");
    table->PutNumber("xDif", xDif);
    table->PutNumber("yDif", yDif);
    table->PutNumber("yaw", yaw);
    table->PutNumber("pitch", pitch);
}