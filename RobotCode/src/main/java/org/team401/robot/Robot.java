package org.team401.robot;

import edu.wpi.first.wpilibj.IterativeRobot;

import org.strongback.Strongback;
import org.strongback.components.Motor;
import org.strongback.components.Solenoid;
import org.strongback.components.ui.FlightStick;
import org.strongback.drive.TankDrive;
import org.strongback.hardware.Hardware;

public class Robot extends IterativeRobot {
    private Motor leftGearbox, rightGearbox;
    private Solenoid solenoid;
    private FlightStick leftJoystick, rightJoystick;
    private TankDrive drive;

    @Override
    public void robotInit() {

        Strongback.configure()
                .recordDataToFile("/home/lvuser/")
                .recordEventsToFile("/home/lvuser/", 2097152);
        leftGearbox = Motor.compose(
                Hardware.Motors.talonSRX(0),
                Hardware.Motors.talonSRX(1).invert(),
                Hardware.Motors.talonSRX(2).invert());

        rightGearbox = Motor.compose(
                Hardware.Motors.talonSRX(5),
                Hardware.Motors.talonSRX(6),
                Hardware.Motors.talonSRX(7).invert());
        drive = new TankDrive(leftGearbox, rightGearbox);

        leftJoystick = Hardware.HumanInterfaceDevices.logitechAttack3D(0);
        rightJoystick = Hardware.HumanInterfaceDevices.logitechAttack3D(1);

        solenoid = Hardware.Solenoids.doubleSolenoid(4, 6, Solenoid.Direction.RETRACTING);

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
        drive.tank(leftJoystick.getPitch().read(), rightJoystick.getPitch().read());

        if (leftJoystick.getButton(2).isTriggered()){
            solenoid.extend();
        }else if(leftJoystick.getButton(3).isTriggered()){
            solenoid.retract();
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
