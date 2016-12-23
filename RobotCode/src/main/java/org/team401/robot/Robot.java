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

import edu.wpi.first.wpilibj.CANTalon;
import edu.wpi.first.wpilibj.IterativeRobot;

import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;
import org.strongback.Strongback;
import org.strongback.components.ui.FlightStick;
import org.strongback.hardware.Hardware;

public class Robot extends IterativeRobot {

    CANTalon talon;
    FlightStick controller;

    @Override
    public void robotInit() {
        Strongback.configure()
                .recordDataToFile("/home/lvuser/")
                .recordEventsToFile("/home/lvuser/", 2097152);

        talon = new CANTalon(9);
        talon.setControlMode(CANTalon.TalonControlMode.Speed.value);
        talon.setPID(1.2, 0, 0);
        talon.configEncoderCodesPerRev(497);
        talon.setFeedbackDevice(CANTalon.FeedbackDevice.QuadEncoder);

        talon.enable();

        controller = Hardware.HumanInterfaceDevices.logitechAttack3D(0);
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
        double target = toRange(controller.getThrottle().read()*-1, -1, 1, 0, 87);
        SmartDashboard.putNumber("Target Speed", target);
        talon.setSetpoint(target*4);
        SmartDashboard.putNumber("Actual Speed", talon.getSpeed());
    }

    @Override
    public void autonomousPeriodic() {

    }

    @Override
    public void disabledInit() {
        Strongback.disable();
    }

    double toRange(double x, double min, double max, double newMin, double newMax) {
        return (newMax - newMin) * (x - min) / (max - min) + newMin;
    }
}
