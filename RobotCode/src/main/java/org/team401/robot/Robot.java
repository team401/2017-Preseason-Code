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

/*
   Pixy Links:
   -
   -
   -
 */

package org.team401.robot;

import edu.wpi.first.wpilibj.*;
import edu.wpi.first.wpilibj.interfaces.Gyro;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;
import org.strongback.Strongback;
import org.strongback.components.Motor;
import org.strongback.components.ui.FlightStick;
import org.strongback.drive.TankDrive;
import org.strongback.hardware.Hardware;

public class Robot extends IterativeRobot {

    private FlightStick joysticky;
    private TankDrive allDrive;
    //gyro variables
    private Gyro myGyro;
    double kp = 0.1;
    double ki = 0.1;
    double cumulativeError;
    //driving control variables
    private double pitch;
    private double turnSpeed;
    @Override
    public void robotInit() {
        SmartDashboard.putNumber("kp: ", 0.1);
        SmartDashboard.putNumber("ki: ", 0.1);
        Strongback.configure()
                .recordDataToFile("/home/lvuser/")
                .recordEventsToFile("/home/lvuser/", 2097152);

        boolean invert = SmartDashboard.getBoolean("Invert Drive", false);

        Motor leftDrive = Hardware.Motors.talon(1);
        Motor rightDrive = Hardware.Motors.talon(0);

        myGyro = new ADXRS450_Gyro(SPI.Port.kOnboardCS0);
        //deciding which one of the two wheels will be inverted
        if (invert)
            rightDrive = rightDrive.invert();
        else
            leftDrive = leftDrive.invert();

        allDrive = new TankDrive(leftDrive, rightDrive);

        joysticky = Hardware.HumanInterfaceDevices.logitechAttack3D(0);

        Strongback.switchReactor().onTriggered(joysticky.getTrigger(), () -> {
            myGyro.reset();
            cumulativeError = 0;
        });
        SmartDashboard.putNumber("Multiplier: ", kp);

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

        //normal driving code(if the joystick ISN'T triggered)
        if (!joysticky.getTrigger().isTriggered()) {
            pitch = joysticky.getPitch().read();
            turnSpeed = joysticky.getRoll().read();
            allDrive.arcade(pitch, turnSpeed * 0.9);
        }
        //gyro code that makes sure the robot drives perfectly straight(if the joystick IS triggered)
        else {
            //gyroscope code that ensures that the robot is going straight(PI controller)
            double angle = myGyro.getAngle();
            cumulativeError +=  angle * 0.05;
            allDrive.arcade(joysticky.getPitch().read()*0.8, -cumulativeError*ki - angle*kp);
            //SmartDasboard variables
            kp = SmartDashboard.getNumber("kp: ", 0.1);
            ki = SmartDashboard.getNumber("ki: ", 0.1);
            SmartDashboard.putNumber("Angle: ", angle);
            SmartDashboard.putNumber("Turning: ", -angle*kp);
            SmartDashboard.putNumber("Cumulative Errkp = SmartDashboard.getNumber(\"kp: \", 0.1);\n" +
                    "            ki = SmartDashboard.getNumber(\"ki: \", 0.1);or: ", cumulativeError);
        }

    }

    @Override
    public void autonomousPeriodic() {
        //gyroscope code the ensures that the robot is going straight(PI controller)
        double angle = myGyro.getAngle();
        cumulativeError +=  angle * 0.05;
        allDrive.arcade(0.65352, cumulativeError*ki + angle*kp);
        //SmartDashboard variables
        kp = SmartDashboard.getNumber("kp: ", 0.1);
        ki = SmartDashboard.getNumber("ki: ", 0.1);
        SmartDashboard.putNumber("Angle: ", angle);
        SmartDashboard.putNumber("Turning: ", -angle*kp);
        SmartDashboard.putNumber("Cumulative Error: ", cumulativeError);
    }

    @Override
    public void disabledInit() {
        Strongback.disable();
    }
}