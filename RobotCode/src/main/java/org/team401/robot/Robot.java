/* Created Sat Dec 17 19:36:59 EST 2016 */
package org.team401.robot;

import edu.wpi.first.wpilibj.IterativeRobot;

import org.strongback.Strongback;
import org.strongback.components.Motor;
import org.strongback.components.ui.FlightStick;
import org.strongback.drive.TankDrive;
import org.strongback.hardware.Hardware;


public class Robot extends IterativeRobot {
    private Motor leftGearbox, rightGearbox;
    private FlightStick leftJoystick, rightJoystick;
    private TankDrive drive;

    @Override
    public void robotInit() {
        Strongback.configure()
                .recordDataToFile("/home/lvuser/")
                .recordEventsToFile("/home/lvuser/", 2097152);
    	/*leftGearbox=Motor.compose(
    			Hardware.Motors.talonSRX(0).invert(),
    			Hardware.Motors.talonSRX(1).invert(),
    			Hardware.Motors.talonSRX(2));
    	rightGearbox=Motor.compose(
    			Hardware.Motors.talonSRX(3),
    			Hardware.Motors.talonSRX(4),
    			Hardware.Motors.talonSRX(5).invert());
    	*/
        leftGearbox=Hardware.Motors.talon(0);
        rightGearbox=Hardware.Motors.talon(1);
        drive = new TankDrive(leftGearbox, rightGearbox);

        leftJoystick = Hardware.HumanInterfaceDevices.logitechAttack3D(0);
        rightJoystick = Hardware.HumanInterfaceDevices.logitechAttack3D(1);


    }

    @Override
    public void teleopInit() {
        // Start Strongback functions ...
        Strongback.restart();

    }

    @Override
    public void teleopPeriodic() {

        drive.tank(leftJoystick.getPitch().read(),rightJoystick.getPitch().read());
    }

    @Override
    public void disabledInit() {
        // Tell Strongback that the robot is disabled so it can flush and kill commands.
        Strongback.disable();
    }

}

