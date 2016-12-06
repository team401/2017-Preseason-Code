
package org.team401.robot;

import edu.wpi.first.wpilibj.IterativeRobot;


import org.strongback.Strongback;
import org.strongback.components.Solenoid;
import org.strongback.components.ui.FlightStick;
import org.strongback.hardware.Hardware;

public class Robot extends IterativeRobot {

    private Solenoid solenoidPnewmatics;
    private FlightStick joystick;


    @Override
    public void robotInit() {
        solenoidPnewmatics = Hardware.Solenoids.doubleSolenoid(0, -1, Solenoid.Direction.RETRACTING);
        joystick = Hardware.HumanInterfaceDevices.logitechAttack3D(0);
        Strongback.configure()
                    .recordDataToFile("/home/lvuser/")
                    .recordEventsToFile("/home/lvuser/", 2097152);
    }

    @Override
    public void teleopInit() {
        Strongback.restart();
    }

    @Override
    public void autonomousInit() {
        }

    @Override
    public void teleopPeriodic() {
        if (joystick.getTrigger().isTriggered()) {
            solenoidPnewmatics.extend();
        }
        else {
            solenoidPnewmatics.retract();
        }
    }

    @Override
    public void autonomousPeriodic() {

    }

    @Override
    public void disabledInit() {
        Strongback.disable();
    }
}