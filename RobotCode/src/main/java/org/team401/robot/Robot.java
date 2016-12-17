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

import com.sun.tools.corba.se.idl.constExpr.ShiftRight;
import edu.wpi.first.wpilibj.IterativeRobot;
import edu.wpi.first.wpilibj.internal.HardwareHLUsageReporting;
import org.strongback.Strongback;
import org.strongback.components.Motor;
import org.strongback.components.ui.FlightStick;
import org.strongback.drive.TankDrive;
import org.strongback.hardware.Hardware;

public class Robot extends IterativeRobot {

    /*
        For this assignment, you need to get the 2016 robot completely driving in
        Java, and be able to switch between low and high gear. You should create
        a new branch off of this one in GitKraken, name it "yourname-drive" without
        quotes, and push it to GitHub for Liam and I to review by this Saturday, 12/10.
            - Zach
     */

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
        //initializing the motors
        Motor leftFront = Hardware.Motors.talonSRX(2);
        Motor leftMiddle = Hardware.Motors.talonSRX(0).invert();
        Motor leftRear = Hardware.Motors.talonSRX(1);
        Motor rightFront = Hardware.Motors.talonSRX(6).invert();
        Motor rightMiddle = Hardware.Motors.talonSRX(7);
        Motor rightRear = Hardware.Motors.talonSRX(5).invert();

        leftDrive = Motor.compose(leftFront, leftMiddle, leftRear);
        rightDrive = Motor.compose(rightFront, rightMiddle, rightRear);

        allDrive = new TankDrive(leftDrive, rightDrive);



        leftJoysticky = Hardware.HumanInterfaceDevices.logitechAttack3D(0);
        rightJoysticky = Hardware.HumanInterfaceDevices.logitechAttack3D(0);

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
        allDrive.tank(leftJoysticky.getPitch().read(), rightJoysticky.getPitch().read());
        //cameronEarle.isTriggered = true
    }

    @Override
    public void autonomousPeriodic() {

    }

    @Override
    public void disabledInit() {
        Strongback.disable();
    }
}
