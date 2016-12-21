package org.team401.robot;

import org.strongback.components.Stoppable;

public interface LinearActuator extends Stoppable {

    boolean isTopLimitSwitchTriggered();

    boolean isBottomLimitSwitchTriggered();

    void driveOut(double speed);

    void driveIn(double speed);
}
