package org.team401.robot;

import org.strongback.components.Motor;
import org.strongback.components.Switch;
import org.strongback.hardware.Hardware;

/**
 * Created by Neema on 12/21/16.
 */
public class Darty implements LinearActuator{

    private Motor mopedMoto;
    private Switch topSvitcy, bottomSvitcy;



    public Darty(Motor mangoMoto, Switch topSwitcy, Switch bottomSwitcy){
        mopedMoto = mangoMoto;
        topSvitcy = topSwitcy;
        bottomSvitcy = bottomSwitcy;
    }

    @Override
    public boolean isTopLimitSwitchTriggered() {
        return topSvitcy.isTriggered();

    }

    @Override
    public boolean isBottomLimitSwitchTriggered() {
        return bottomSvitcy.isTriggered();
    }

    @Override
    public void driveOut(double speed) {
        mopedMoto.setSpeed(speed);
    }

    @Override
    public void driveIn(double speed) {
        mopedMoto.setSpeed(-speed);
    }

    @Override
    public void stop() {
        mopedMoto.stop();
    }
}
