package org.team401.robot;

import edu.wpi.first.wpilibj.IterativeRobot;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

import org.strongback.Strongback;
import org.strongback.components.ui.FlightStick;
import org.strongback.control.TalonController;
import org.strongback.hardware.Hardware;

public class Robot extends IterativeRobot {
    private FlightStick joystick;
    private TalonController talonController;

    @Override
    public void robotInit() {

        Strongback.configure()
                .recordDataToFile("/home/lvuser/")
                .recordEventsToFile("/home/lvuser/", 2097152);

        talonController = Hardware.Controllers.talonController(9, 1.38, 0);
        joystick = Hardware.HumanInterfaceDevices.logitechAttack3D(0);

        talonController.setControlMode(TalonController.ControlMode.SPEED);


    }

    @Override
    public void teleopInit() {
        Strongback.restart();
    }

    @Override
    public void autonomousInit() {
        Strongback.start();
    }

    @Override
    public void teleopPeriodic() {
        talonController.withGains(SmartDashboard.getNumber("PValue"),(SmartDashboard.getNumber("IValue")),(SmartDashboard.getNumber("DValue")));
        talonController.setSpeed(joystick.getPitch().read() * 7 * 1.38);



    }

    @Override
    public void autonomousPeriodic() {

    }

    @Override
    public void disabledInit() {
        Strongback.disable();
    }
}
