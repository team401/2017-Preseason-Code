package org.team401.robot;

import org.strongback.components.Motor;
import org.strongback.components.Switch;

/**
 * two sensor linear actuator to not over drive
 *
 * @author Leah
 * @version 12/21/16.
 */
public class Dart implements LinearActuator {

    private LinearActuator dart;
    private Switch switchTop, switchBottom;
    private Motor motorA;

    /**
     * constructor for dart
     *
     * @param motor for linear actuator
     * @param topLimitSwitch hall effect for top
     * @param bottomLimitSwitch hall effect for bottom
     */
    public Dart(Motor motor, Switch topLimitSwitch, Switch bottomLimitSwitch) {
        motorA = motor;
        switchTop = topLimitSwitch;
        switchBottom = bottomLimitSwitch;
    }

    /**
     *
     * @return true if dart all the way extended
     */
    @Override
    public boolean isTopLimitSwitchTriggered() {
        return switchTop.isTriggered();

    }

    /**
     *
     * @return true if dart is fully retracted
     */
    @Override
    public boolean isBottomLimitSwitchTriggered() {
        return switchBottom.isTriggered();

    }

    /**
     *
     * @param speed motor speed
     */
    @Override
    public void drive(double speed) {
        motorA.setSpeed(speed);

    }

    /**
     * prevents dart from moving
     */
    @Override
    public void stop() {
        motorA.setSpeed(0);
    }
}
