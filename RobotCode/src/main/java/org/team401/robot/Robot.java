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
import org.usfirst.frc.team3539.robot.MotionProfileExample;

public class Robot extends IterativeRobot {

    /**
     * The Talon we want to motion profile.
     */
    CANTalon talon = new CANTalon(9);

    /**
     * some example logic on how one can manage an MP
     */
    MotionProfileExample example = new MotionProfileExample(talon);

    public Robot() { // could also use RobotInit()
        talon.setFeedbackDevice(CANTalon.FeedbackDevice.QuadEncoder);
        talon.reverseSensor(false); /* keep sensor and motor in phase */
    }

    public void teleopInit() {
        example.startMotionProfile();
    }

    /**
     * function is called periodically during operator control
     */
    public void teleopPeriodic() {
        /* Button5 is held down so switch to motion profile control mode => This is done in MotionProfileControl.
		 * When we transition from no-press to press,
		 * pass a "true" once to MotionProfileControl.
	     */
        example.control();

        talon.changeControlMode(CANTalon.TalonControlMode.MotionProfile);

        CANTalon.SetValueMotionProfile setOutput = example.getSetValue();

        talon.set(setOutput.value);

    }

    /**
     * function is called periodically during disable
     */
    public void disabledPeriodic() {
		/* it's generally a good idea to put motor controllers back
		 * into a known state when robot is disabled.  That way when you
		 * enable the robot doesn't just continue doing what it was doing before.
		 * BUT if that's what the application/testing requires than modify this accordingly */
        talon.changeControlMode(CANTalon.TalonControlMode.PercentVbus);
        talon.set(0);
		/* clear our buffer and put everything into a known state */
        example.reset();
    }
}
