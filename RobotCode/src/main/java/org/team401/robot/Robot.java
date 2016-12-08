/*
    Quetzalcoatl - Copperhead Robotics 2016 Robot code for FIRST Stronghold
    Copyright (C) 2016 FRC Team 401

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/
package org.team401.robot;

import edu.wpi.first.wpilibj.IterativeRobot;

import org.strongback.Strongback;
import org.strongback.components.Solenoid;
import org.strongback.components.ui.FlightStick;
import org.strongback.hardware.Hardware;

public class Robot extends IterativeRobot {

    private Solenoid solenoidPneumatics;
    private FlightStick joysticky;

    @Override
    public void robotInit() {

        solenoidPneumatics = Hardware.Solenoids.doubleSolenoid(0,1, Solenoid.Direction.RETRACTING);

        joysticky = Hardware.HumanInterfaceDevices.logitechAttack3D(0);

        Strongback.configure()
                .recordDataToFile("/home/lvuser/")
                .recordEventsToFile("/home/lvuser/", 2097152);
    }

    @Override
    public void teleopInit() {
        Strongback.restart();
    }

    @Override
    public void autonomousInit() {

    }

    @Override
    public void teleopPeriodic() {

        //returns a True/False if the joysticky is triggered
        if (joysticky.getTrigger().isTriggered()){
            solenoidPneumatics.extend();
        }
        else{
            solenoidPneumatics.retract();
        }

    }

    @Override
    public void autonomousPeriodic() {

    }

    @Override
    public void disabledInit() {
        Strongback.disable();
    }
}