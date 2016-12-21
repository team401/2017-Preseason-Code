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

/**
 * Two wheel shooter system with pneumatic kick out
 *
 * @author Neema
 * @version 12/21/16.
 */

package org.team401.robot;

import edu.wpi.first.wpilibj.IterativeRobot;
import org.strongback.components.Solenoid;
import org.strongback.Strongback;
import org.strongback.components.Motor;
import org.strongback.components.Switch;
import org.strongback.components.ui.FlightStick;
import org.strongback.drive.TankDrive;
import org.strongback.hardware.Hardware;

public class Robot extends IterativeRobot {

    private FlightStick leftJoysticky, rightJoysticky;
    private TankDrive allDrive;
    private Arm captArmy;

    /**
     * Initializes the motors and defines later used variables
     */
    @Override
    public void robotInit() {
        Strongback.configure()
                .recordDataToFile("/home/lvuser/")
                .recordEventsToFile("/home/lvuser/", 2097152);
        Solenoid moreUselessThanCameron = Hardware.Solenoids.doubleSolenoid(5, 1, Solenoid.Direction.RETRACTING);
        Switch topLimity = Hardware.Switches.normallyClosed(0);
        Switch bottomLimity = Hardware.Switches.normallyClosed(1);

        //initializing the motors
        Motor leftShooter = Hardware.Motors.talonSRX(3);
        Motor rightShooter = Hardware.Motors.talonSRX(8);
        Motor dodoMoto = Hardware.Motors.talonSRX(4);
        Motor leftFront = Hardware.Motors.talonSRX(2).invert();
        Motor leftMiddle = Hardware.Motors.talonSRX(0);
        Motor leftRear = Hardware.Motors.talonSRX(1).invert();
        Motor rightFront = Hardware.Motors.talonSRX(6);
        Motor rightMiddle = Hardware.Motors.talonSRX(7).invert();
        Motor rightRear = Hardware.Motors.talonSRX(5);
        LinearActuator dart = new Darty(dodoMoto, topLimity, bottomLimity);
        Shooty cannon = new Shooty(leftShooter, rightShooter, moreUselessThanCameron);
        captArmy = new Arm(dart, cannon);

        Motor leftDrive = Motor.compose(leftFront, leftMiddle, leftRear);
        Motor rightDrive = Motor.compose(rightFront, rightMiddle, rightRear);

        allDrive = new TankDrive(leftDrive, rightDrive);



        leftJoysticky = Hardware.HumanInterfaceDevices.logitechAttack3D(1);
        rightJoysticky = Hardware.HumanInterfaceDevices.logitechAttack3D(2);
    }

    /**
     * Restarts strongback
     */
    @Override
    public void teleopInit() {
        Strongback.restart();
    }

    /**
     *Starts strongback
     */
    @Override
    public void autonomousInit() {
        Strongback.start();
    }

    /**
     *Runs the robot code every 20 ms.
     */
    @Override
    public void teleopPeriodic() {
        if (!rightJoysticky.getButton(2).isTriggered()) {
            allDrive.tank(leftJoysticky.getPitch().read(), rightJoysticky.getPitch().read());
        }

        if (rightJoysticky.getButton(2).isTriggered()){
        captArmy.drive((rightJoysticky.getPitch().read())*0.5);
        }
        else {
            captArmy.drive(0);
        }

        if (rightJoysticky.getButton(1).isTriggered()){
            captArmy.getPropulzion().pppPushIt();
        }
        else{
            captArmy.getPropulzion().rrrRetractic();
        }

        if (rightJoysticky.getButton(4).isTriggered()){
            captArmy.getPropulzion().shoot(rightJoysticky.getThrottle().read());
        }
        else if (rightJoysticky.getButton(3).isTriggered()){
            captArmy.getPropulzion().intake();
        }
        else {
            captArmy.getPropulzion().sssStop();
        }

        //cameronEarle.isTriggered = true
    }

    @Override
    public void autonomousPeriodic() {

    }

    /**
     *Disables strongback
     */
    @Override
    public void disabledInit() {
        Strongback.disable();
    }
}
