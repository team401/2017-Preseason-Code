/**
 * Moves the arm and keeps it from breaking itself
 *
 * @author Neema
 * @version 12/21/16.
 */

package org.team401.robot;

public class Arm {

    private LinearActuator dart;
    private Shooty propulzion;

    /**
     *
     *
     * @param dardo is the arm's postion
     * @param propulzion pushes out the ball
     */
    public Arm(LinearActuator dardo, Shooty propulzion) {

        dart = dardo;
        this.propulzion = propulzion;

    }

    /**
     * Prevents the arm from going too high or too low and damaging itself
     *
     * @param pitch is how far the joystick is pushed forwards
     */
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
            dart.drive(pitch);
        }
    }

    /**
     * @return the instance of the shooter
     */
    public Shooty getPropulzion(){
        return propulzion;
    }

}
