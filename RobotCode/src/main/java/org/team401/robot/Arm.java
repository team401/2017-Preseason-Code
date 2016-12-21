package org.team401.robot;

public class Arm {

    private LinearActuator dart;
    private Shooty propulzion;

    public Arm(LinearActuator dardo, Shooty propulzion) {

        dart = dardo;
        this.propulzion = propulzion;

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

    public Shooty getPropulzion(){
        return propulzion;
    }

}
