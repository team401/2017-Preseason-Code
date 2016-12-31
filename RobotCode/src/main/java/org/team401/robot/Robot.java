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
import org.strongback.components.Motor;
import org.strongback.components.ui.FlightStick;
import org.strongback.drive.TankDrive;
import org.strongback.hardware.Hardware;

public class Robot extends IterativeRobot {
    Motor leftDrive;
    Motor rightDrive;
    TankDrive tankDrive;
    ScaledRange joyPitch;
    ScaledRange joyRoll;
    float multiplier;

    @Override
    public void robotInit() {
        Strongback.start(); //Start strongback
        multiplier = .8F; //A multiplier to reduce the motor power below max at all times
        leftDrive = Hardware.Motors.talon(1).invert(); //Set up the left motor and invert it
        rightDrive = Hardware.Motors.talon(0); //Set up the right motor
        tankDrive = new TankDrive(leftDrive, rightDrive); //Create a tankdrive to allow easy motor control
        FlightStick joystick = Hardware.HumanInterfaceDevices.logitechAttack3D(0); //Bind the joystick
        joyPitch = new ScaledRange(joystick.getPitch(), multiplier); //Get scaled ranges from the joystick
        joyRoll = new ScaledRange(joystick.getRoll(), multiplier);
    }

    @Override
    public void disabledInit() {
        Strongback.disable(); //Stop strongback when the robot is disabled
    }

    @Override
    public void autonomousInit() {
        Strongback.restart(); //Restart strongback on a mode change
    }

    @Override
    public void teleopInit() {
        Strongback.restart(); //Restart strongback on a mode change
    }

    @Override
    public void autonomousPeriodic() {
        tankDrive.tank(.3, .3); //Drive the robot forward while it's in auto at low speed.
    }

    @Override
    public void teleopPeriodic() {
        tankDrive.arcade(joyPitch.readScaled(), joyRoll.readScaled()); //Arcade the robot scaled to a multiplier
    }
}
