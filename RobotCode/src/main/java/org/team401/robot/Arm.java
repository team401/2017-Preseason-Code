package org.team401.robot;

import org.strongback.components.Motor;
import org.strongback.components.Solenoid;
import org.strongback.components.Switch;

/**
 * creates robot arm with two wheel shooter and linear actuator to elevate it
 *
 * @author Leah
 * @version 12/21/2016
 */
public class Arm {

    private Shooter shooter;
    private LinearActuator dart;

    /**
     * constructor to create arm :)
     * @param motor this is the motor for the linear actuator
     * @param topLimitSwitch this is the switch on the top of the linear actuator
     * @param bottomLimitSwitch switch on the BOTTOM of the LINEAR ACTUATOR
     * @param leftMotor motor on left shooter wheel
     * @param rightMotor motor on right shooter wheel
     * @param sole solenoid to hit ball
     */


    public Arm(Motor motor, Switch topLimitSwitch, Switch bottomLimitSwitch, Motor leftMotor, Motor rightMotor, Solenoid sole) {

        dart = new Dart(motor, topLimitSwitch, bottomLimitSwitch);
        shooter = new Shooter(leftMotor, rightMotor, sole);

    }

    /**
     * uses limit switches to prevent over travel and moves dart
     * @param speed the speed to move LA up and down
     */
    public void drive(double speed) {

        if (dart.isTopLimitSwitchTriggered()){
            if (speed > 0) dart.stop();
            if (speed <= 0) dart.drive(speed);
        }
       else if (dart.isBottomLimitSwitchTriggered()){
            if (speed < 0) dart.stop();
            if (speed >= 0) dart.drive(speed);
        }
        else dart.drive(speed);
    }

    /**
     * @return allows access to shooter system
     */
    public Shooter getShooter(){
        return shooter;
    }

}
