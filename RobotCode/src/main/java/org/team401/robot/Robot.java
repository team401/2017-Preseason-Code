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

import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;
import org.strongback.Strongback;
import org.strongback.components.Motor;
import org.strongback.components.ui.FlightStick;
import org.strongback.drive.TankDrive;
import org.strongback.hardware.Hardware;


public class Robot extends IterativeRobot {

    private FlightStick joysticky;
    private TankDrive allDrive;

    private double output, lastInput;
    private int mode;

    @Override
    public void robotInit() {
        Strongback.configure()
                .recordDataToFile("/home/lvuser/")
                .recordEventsToFile("/home/lvuser/", 2097152);

        SmartDashboard.putBoolean("y this no work", true);

        boolean invert = SmartDashboard.getBoolean("Invert Drive", false);

        Motor leftDrive = Hardware.Motors.talon(0);
        Motor rightDrive = Hardware.Motors.talon(1);

        if (invert)
            rightDrive = rightDrive.invert();
        else
            leftDrive = leftDrive.invert();

        allDrive = new TankDrive(leftDrive, rightDrive);

        joysticky = Hardware.HumanInterfaceDevices.logitechAttack3D(0);
    }

    @Override
    public void teleopInit() {
        Strongback.restart();
    }

    @Override
    public void autonomousInit() {
        Strongback.start();
    }

    @Override
    public void teleopPeriodic() {
        //rate of change in joystick values.
        double input = joysticky.getPitch().read();
        SmartDashboard.putNumber("Input", input);
        double delta = input - lastInput;
        SmartDashboard.putNumber("Delta", delta);

        //is joystick being moved too fast?
        if(delta >= .15)
            mode = 1;
        else if(delta <= -.45)
            mode = -1;
        SmartDashboard.putNumber("Mode", mode);

        //output integration
        switch(mode) {
            case 1: // ramp up
                output += 0.01;
                if (output >= input)
                    mode = 0;
                break;

            case -1: // ramp down
                output -= 0.20;
                if (output <= input)
                    mode = 0;
                break;

            case 0: // nothing
                output = input;
                break;

            default:
                break;
        }
        lastInput = input;
        SmartDashboard.putNumber("Output", output);
        allDrive.arcade(output, joysticky.getRoll().read());
    }

    @Override
    public void autonomousPeriodic() {

    }

    @Override
    public void disabledInit() {
        Strongback.disable();
    }
}