package org.team401.robot;

import org.strongback.components.Motor;
import org.strongback.components.Solenoid;

/**
 * Created by Neema on 12/21/16.
 */


public class Shooty {

    public static final double INTAKE_SPEED = 0.5;
    public Motor leftShootSnoot, rightShootSnoot;
    public Solenoid realGood;

    public Shooty(Motor leftShootSnoot, Motor rightShootSnoot, Solenoid realGood) {
        this.leftShootSnoot = leftShootSnoot;
        this.rightShootSnoot = rightShootSnoot;
        this.realGood = realGood;
    }

    public void intake(){
        leftShootSnoot.setSpeed(INTAKE_SPEED);
        rightShootSnoot.setSpeed(-INTAKE_SPEED);
    }

    public void shoot(double throble){
        throble = (((throble * -1) + 1) / 2);
        leftShootSnoot.setSpeed(-throble);
        rightShootSnoot.setSpeed(throble);
    }
    public void sssStop(){
        rightShootSnoot.stop();
        leftShootSnoot.stop();
    }

    public void pppPushIt(){
        realGood.extend();
    }

    public void rrrRetractic(){
        realGood.retract();
    }

}
