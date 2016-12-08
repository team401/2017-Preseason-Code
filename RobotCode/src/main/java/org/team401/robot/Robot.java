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
import org.strongback.components.Solenoid;
import org.strongback.components.ui.ContinuousRange;
import org.strongback.components.ui.FlightStick;
import org.strongback.drive.TankDrive;
import org.strongback.hardware.Hardware;

public class Robot extends IterativeRobot {
//NOTE: NEED TO PROPERLY ASSIGNS JOYSTICK PORTS!!!!!
private static final int JOYSTICK_PORT_LEFT = 0;
private static final int JOYSTICK_PORT_RIGHT = 1;

private static final int MIDDLE_LEFT_MOTOR_PORT = 0;
private static final int REAR_LEFT_MOTOR_PORT = 1;
private static final int FRONT_LEFT_MOTOR_PORT = 2;
//private static final int LEFT_SHOOTER_MOTOR_PORT = 3;
//private static final int DART_PORT = 4;
private static final int REAR_RIGHT_MOTOR_PORT = 5;
private static final int FRONT_RIGHT_MOTOR_PORT = 6;
private static final int MIDDLE_RIGHT_MOTOR_PORT = 7;
//private static final int RIGHT_SHOOTER_MOTOR_PORT = 8;

private TankDrive drive;
private ContinuousRange driveSpeedRight;
private ContinuousRange driveSpeedLeft;
private Solenoid gearShift;
private FlightStick joystickLeft;
private FlightStick joystickRight;

    @Override
    public void robotInit() {
    	
    	//initiates the motors on the left and right as essentually one motor
Motor leftMotor = Motor.compose(Hardware.Motors.talonSRX(REAR_LEFT_MOTOR_PORT),
		Hardware.Motors.talonSRX(MIDDLE_LEFT_MOTOR_PORT).invert(),
		Hardware.Motors.talonSRX(FRONT_LEFT_MOTOR_PORT));
Motor rightMotor = Motor.compose(Hardware.Motors.talonSRX(REAR_RIGHT_MOTOR_PORT),
		Hardware.Motors.talonSRX(MIDDLE_RIGHT_MOTOR_PORT).invert(),
		Hardware.Motors.talonSRX(FRONT_RIGHT_MOTOR_PORT));

//initiates the two joysticks
joystickLeft = Hardware.HumanInterfaceDevices.logitechAttack3D(JOYSTICK_PORT_LEFT);
joystickRight = Hardware.HumanInterfaceDevices.logitechAttack3D(JOYSTICK_PORT_RIGHT);

//initiates the drive
drive = new TankDrive(leftMotor, rightMotor);

//assigns each joystick to power the left and right side 
driveSpeedLeft = joystickLeft.getPitch();
driveSpeedRight = joystickRight.getPitch().invert();

//initiates the gearShift solenoid
//NOTE: NEED TO DETERMIN WHICH PORTS THE SOLENOID IS AND HOW FAR IT SHOULD MOVE ETC.
gearShift = Hardware.Solenoids.doubleSolenoid(4, 1, Solenoid.Direction.RETRACTING);

//starts strongback
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
        // read values from joystick and drive (maybe)
    	//assigns the tank drive
    	drive.tank(driveSpeedLeft.read(), driveSpeedRight.read());
    	
    	//activates the solenoid if the trigger on the left joystick is triggered
    	if(joystickLeft.getTrigger().isTriggered()){
    		gearShift.extend();
    	}
    	//retracts the solenoid if the trigger on the right joystick is triggered
    	if(joystickRight.getTrigger().isTriggered()){
    		gearShift.retract();
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
