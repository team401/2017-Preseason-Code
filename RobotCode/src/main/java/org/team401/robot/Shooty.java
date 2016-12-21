package org.team401.robot;

import org.strongback.components.Motor;
import org.strongback.components.Solenoid;

/**
 * Allows the robot to shoot out the ball
 *
 * @author Neema
 * @version 12/21/16.
 */


public class Shooty {

    public static final double INTAKE_SPEED = 0.5;
    public Motor leftShootSnoot, rightShootSnoot;
    public Solenoid realGood;

    /**
     * Constructor for the shooter system
     *
     * @param leftShootSnoot is the left shooting motor
     * @param rightShootSnoot is the right shooting motor
     * @param realGood is the solenoid that pushes the ball into the wheels to be shot
     */

    public Shooty(Motor leftShootSnoot, Motor rightShootSnoot, Solenoid realGood) {
        this.leftShootSnoot = leftShootSnoot;
        this.rightShootSnoot = rightShootSnoot;
        this.realGood = realGood;
    }

    /**
     *Spins the motors in the correct directions for proper intake of the ball
     */

    public void intake(){
        leftShootSnoot.setSpeed(INTAKE_SPEED);
        rightShootSnoot.setSpeed(-INTAKE_SPEED);
    }

    /**
     *Spins the motors in the correct directions for proper shooting of the ball
     *
     *@param throble determines how fast the motors will spin
     */
    public void shoot(double throble){
        throble = (((throble * -1) + 1) / 2);
        leftShootSnoot.setSpeed(-throble);
        rightShootSnoot.setSpeed(throble);
    }

    /**
     *Stops the motors
     */
    public void sssStop(){
        rightShootSnoot.stop();
        leftShootSnoot.stop();
    }

    /**
     *Extends the solenoid to push the ball
     */
    public void pppPushIt(){
        realGood.extend();
    }

    /**
     *Retracts the solenoid
     */
    public void rrrRetractic(){
        realGood.retract();
    }

}