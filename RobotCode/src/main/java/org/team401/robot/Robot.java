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

import edu.wpi.first.wpilibj.IterativeRobot;
import org.strongback.Strongback;
import org.strongback.components.Motor;
import org.strongback.components.ui.FlightStick;
import org.strongback.drive.TankDrive;
import org.strongback.hardware.Hardware;


public class Robot extends IterativeRobot {

    private FlightStick leftJoysticky;
    private FlightStick rightJoysticky;
    private Motor leftDrive;
    private Motor rightDrive;
    private TankDrive allDrive;

    @Override
    public void robotInit() {

        Strongback.configure()
                .recordDataToFile("/home/lvuser/")
                .recordEventsToFile("/home/lvuser/", 2097152);

        leftDrive = Hardware.Motors.talonSRX(0);
        rightDrive = Hardware.Motors.talonSRX(1);

        allDrive = new TankDrive(leftDrive, rightDrive);

        leftJoysticky = Hardware.HumanInterfaceDevices.logitechAttack3D(0);
        rightJoysticky = Hardware.HumanInterfaceDevices.logitechAttack3D(1);

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
            allDrive.tank(leftJoysticky.getPitch().read(), rightJoysticky.getPitch().read());
    }

    @Override
    public void autonomousPeriodic() {

    }

    @Override
    public void disabledInit() {
        Strongback.disable();
    }
}