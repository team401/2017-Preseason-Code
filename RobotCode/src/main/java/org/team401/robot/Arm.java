package org.team401.robot;

import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;
import org.strongback.components.Motor;
import org.strongback.components.Switch;
import org.strongback.hardware.Hardware;

public class Arm {

    private LinearActuator dart;

    public Arm(Motor motor, Switch topLimitSwitch, Switch bottomLimitSwitch) {
        // take in a motor and two switches

        // you need to create your own implementation of LinearActuator and then initialize the one here

        dart = new Darty(motor, topLimitSwitch, bottomLimitSwitch);
    }

    public void drive(double pitch) {
        // drive the dart here, you will need to use the limit switch methods of the LinearActuator interface to tell
        // if it has been driven too far
        if (dart.isTopLimitSwitchTriggered() && pitch > 0){
            dart.stop();
        }
        else if (dart.isBottomLimitSwitchTriggered() && pitch < 0){
            dart.stop();
        }
        else {
            dart.driveOut(pitch);
        }
    }

}
