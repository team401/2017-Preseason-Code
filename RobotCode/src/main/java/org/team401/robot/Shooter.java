package org.team401.robot;

import org.strongback.components.Motor;
import org.strongback.components.Solenoid;

/**
 * two wheel shooter system with pnewmatic kick out
 *
 * @author Leah
 * @version 12/21/16
 */
public class Shooter {
    private Motor leftMotor, rightMotor;
    private Solenoid solenoid;

    /**
     * constructor for shooter system
     *
     * @param left motor for left wheel
     * @param right motor for right wheel
     * @param sole solenoid to push ball
     */
    public Shooter(Motor left, Motor right, Solenoid sole){
        leftMotor = left;
        rightMotor = right;
        solenoid = sole;
    }

    /**
     * sets intake speed
     *
     * @param speed motor speed
     */
    public void spinIn(double speed){
        leftMotor.setSpeed(speed);
        rightMotor.setSpeed(speed);
    }

    /**
     * sets outtake speed
     *
     * @param speed motor speed
     */
    public void spinOut(double speed){
        leftMotor.invert().setSpeed(speed);
        rightMotor.invert().setSpeed(speed);
    }

    /**
     * pushes ball into the shooter
     */
    public void extend(){
        solenoid.extend();
    }

    /**
     * stop pushing ball
     */
    public void retract(){
        solenoid.retract();
    }

    /**
     *stops shooter motors
     */
    public void stop(){
        leftMotor.setSpeed(0);
        rightMotor.setSpeed(0);
    }

}
