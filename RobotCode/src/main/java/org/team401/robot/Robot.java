package org.team401.robot;

import edu.wpi.first.wpilibj.IterativeRobot;
import org.strongback.Strongback;
import org.strongback.components.Motor;
import org.strongback.components.Solenoid;
import org.strongback.components.Switch;
import org.strongback.components.ui.FlightStick;
import org.strongback.drive.TankDrive;
import org.strongback.hardware.Hardware;

/**
 * creates working robot code with working shooter and drive
 *
 * @author Leah
 * @version 12/21/2016
 */
public class Robot extends IterativeRobot {

    private Motor leftGearbox, rightGearbox;
    private FlightStick leftJoystick, rightJoystick, armJoystick;
    private TankDrive drive;
    private Arm arm;
    private Shooter cannon;

    /**
     * sets up robot hardware
     */
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

        armJoystick = Hardware.HumanInterfaceDevices.logitechAttack3D(2);
        leftJoystick = Hardware.HumanInterfaceDevices.logitechAttack3D(0);
        rightJoystick = Hardware.HumanInterfaceDevices.logitechAttack3D(1);

        Solenoid sole = Hardware.Solenoids.doubleSolenoid(5, 6, Solenoid.Direction.RETRACTING);
        Switch switchTop = Hardware.Switches.normallyClosed(0);
        Switch switchBottom = Hardware.Switches.normallyClosed(1);
        Motor motorA = Hardware.Motors.talonSRX(4);
        Motor leftMotor = Hardware.Motors.talonSRX(8).invert();
        Motor rightMotor = Hardware.Motors.talonSRX(3);
        arm = new Arm(motorA, switchTop, switchBottom, leftMotor, rightMotor, sole);
        cannon = arm.getShooter();
    }

    /**
     * restarts strongback when entering teleop
     */
    @Override
    public void teleopInit() {
        Strongback.restart();
    }

    /**
     * starts strongback when entering teleop
     */
    @Override
    public void autonomousInit() {
        Strongback.start();
    }

    /**
     * runs robot code in 20 ms
     */
    @Override
    public void teleopPeriodic() {
        double throttle = (armJoystick.getThrottle().read()* -1 + 1) / 2;
        drive.tank(leftJoystick.getPitch().read(), rightJoystick.getPitch().read());

        if (armJoystick.getButton(1).isTriggered())
            cannon.extend();
        else cannon.retract();
        arm.drive(armJoystick.getPitch().read());
        if (armJoystick.getButton(5).isTriggered())cannon.spinOut(throttle);
        else if (armJoystick.getButton(3).isTriggered())cannon.spinIn(.5);
        else cannon.stop();
    }

    /**
     *nothing currently cuz i'm lazy
     */
    @Override
    public void autonomousPeriodic() {

    }

    /**
     * disables strongback when robot is disabled
     */
    @Override
    public void disabledInit() {
        Strongback.disable();
    }
}
