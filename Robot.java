/* Created Mon Nov 07 20:00:44 EST 2016 */
package com.myteam.robot;

import org.strongback.Strongback;
import org.strongback.components.ui.ContinuousRange;
import org.strongback.components.TalonSRX;
import org.strongback.components.ui.FlightStick;
import org.strongback.hardware.Hardware;

import edu.wpi.first.wpilibj.IterativeRobot;

public class Robot extends IterativeRobot {

	private static final int JOYSTICK_PORT = 0,
			MOTOR_PORT = 9,
			ENCODER_PPR = -7;
	private ContinuousRange motorSpeed;
	private TalonSRX movingMotor;
    @Override
    public void robotInit() {
    	FlightStick joystick = Hardware.HumanInterfaceDevices.logitechAttack3D(JOYSTICK_PORT);
    	//movingMotor = Hardware.Motors.talonSRX(MOTOR_PORT);
    	movingMotor = Hardware.Motors.talonSRX(MOTOR_PORT, ENCODER_PPR);
    	motorSpeed = joystick.getPitch();
    }

    @Override
    public void teleopInit() {
        // Start Strongback functions ...
        //Strongback.start();
    }

    @Override
    public void teleopPeriodic() {
    	movingMotor.setSpeed(motorSpeed.read());
    	System.out.println("Encoder Value: "+movingMotor.getEncoderInput().getRate()+"\nInput: " + motorSpeed.read());
    }

    @Override
    public void disabledInit() {
        // Tell Strongback that the robot is disabled so it can flush and kill commands.
        Strongback.disable();
    }

}
