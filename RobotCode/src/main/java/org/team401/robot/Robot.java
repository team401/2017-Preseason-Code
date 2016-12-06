/*
    Quetzalcoatl - Copperhead Robotics 2016 Robot code for FIRST Stronghold
    Copyright (C) 2016 FRC Team 401

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/
package org.team401.robot;

import edu.wpi.first.wpilibj.IterativeRobot;

import org.strongback.Strongback;
import org.strongback.components.Motor;
import org.strongback.components.Relay;
import org.strongback.components.Solenoid;
import org.strongback.components.ui.FlightStick;
import org.strongback.drive.TankDrive;
import org.strongback.hardware.Hardware;

public class Robot extends IterativeRobot {

    private TankDrive chassis;

    private FlightStick leftDriveController, rightDriveController, armController;

    private Motor dart, cannon;

    private Solenoid s;


    @Override
    public void robotInit() {
        // merging motors into one motor (gearbox)
        Motor leftGearbox = Motor.compose(
                Hardware.Motors.talonSRX(1).invert(),
                Hardware.Motors.talonSRX(2).invert(),
                Hardware.Motors.talonSRX(0));
        Motor rightGearbox = Motor.compose(
                Hardware.Motors.talonSRX(5),
                Hardware.Motors.talonSRX(6),
                Hardware.Motors.talonSRX(7).invert());

        dart = Hardware.Motors.talonSRX(4);
        cannon = Motor.compose(
                Hardware.Motors.talonSRX(8).invert(),
                Hardware.Motors.talonSRX(3));
        // a simple solenoid
        s = Hardware.Solenoids.doubleSolenoid(4, 3, Solenoid.Direction.RETRACTING);
        chassis = new TankDrive(leftGearbox, rightGearbox);

        leftDriveController = Hardware.HumanInterfaceDevices.logitechAttack3D(0);
        rightDriveController = Hardware.HumanInterfaceDevices.logitechAttack3D(1);
        armController = Hardware.HumanInterfaceDevices.logitechAttack3D(2);

        Strongback.configure()
                .recordDataToFile("/home/lvuser/")
                .recordEventsToFile("/home/lvuser/", 2097152);
        Strongback.switchReactor().onTriggered(leftDriveController.getButton(3), () -> s.extend());
        Strongback.switchReactor().onTriggered(leftDriveController.getButton(4), () -> s.retract());
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
        // read values from joystick and drive (maybe)
        chassis.tank(leftDriveController.getPitch().read(), rightDriveController.getPitch().read());

        cannon.setSpeed(armController.getPitch().read());
    }

    @Override
    public void autonomousPeriodic() {

    }

    @Override
    public void disabledInit() {
        Strongback.disable();
    }
}
