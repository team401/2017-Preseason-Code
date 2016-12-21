package org.team401.robot;

import org.strongback.components.Motor;
import org.strongback.components.Switch;

/**
 * Positions the robot arm
 *
 * @author Neema
 * @version 12/21/16.
 */
public class Darty implements LinearActuator{

    private Motor mopedMoto;
    private Switch topSvitcy, bottomSvitcy;



    public Darty(Motor mangoMoto, Switch topSwitcy, Switch bottomSwitcy){
        mopedMoto = mangoMoto;
        topSvitcy = topSwitcy;
        bottomSvitcy = bottomSwitcy;
    }

    /**
     * @return true the arm completely extended
     */
    @Override
    public boolean isTopLimitSwitchTriggered() {
        return topSvitcy.isTriggered();
    }

    /**
     *@return true if arm is completely unextended
     */
    @Override
    public boolean isBottomLimitSwitchTriggered() {
        return bottomSvitcy.isTriggered();
    }

    /**
     *Moves the the arm up at a certain speed
     *
     * @param speed is how fast the user wants the arms to move up
     */
    @Override
    public void drive(double speed) {
        mopedMoto.setSpeed(speed);
    }

    /**
     * Cuts power output the the motor moving the arm
     */
    @Override
    public void stop() {
        mopedMoto.stop();
    }
}
