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

public class Robot extends IterativeRobot {

    /*
        For this assignment, you need to get the 2016 robot completely driving in
        Java, and be able to switch between low and high gear. You should create
        a new branch off of this one in GitKraken, name it "yourname-drive" without
        quotes, and push it to GitHub for Liam and I to review by this Saturday, 12/10.
            - Zach
     */

    @Override
    public void robotInit() {
        Strongback.configure()
                .recordDataToFile("/home/lvuser/")
                .recordEventsToFile("/home/lvuser/", 2097152);

        /*
            Initialize your motors here. The gearboxes on the 2016 bot each have 3 motors.
            The front and rear motors spin one direction while the middle will spin in the opposite.
            You need to either log into the robot via 10.40.1.2 when your at the shop or
            look at the motors on the robot to get their CAN IDs. We use TalonSRX.

         */
        private Motor leftDrive;
        private Motor rightDrive;

        // solenoid initialization

        /*
            Initialize the solenoid here. You only need one solenoid as it controls
            the piston in both gearboxes.
         */

        // solenoid initialization

        // joysticks, LogitechAttack3D

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
        // here is where you should read joystick inputs and set motor speeds
    }

    @Override
    public void autonomousPeriodic() {

    }

    @Override
    public void disabledInit() {
        Strongback.disable();
    }
}
