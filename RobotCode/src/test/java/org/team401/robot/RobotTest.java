package org.team401.robot;

import org.junit.Test;
import org.strongback.mock.Mock;
import org.strongback.mock.MockMotor;

import static org.junit.Assert.*;

public class RobotTest {

    @Test
    public void testDart() {
        LinearActuator dart = new Darty(Mock.runningTalonSRX(0), Mock.notTriggeredSwitch(), Mock.notTriggeredSwitch());
        assertEquals(dart.isBottomLimitSwitchTriggered(), false);
        assertEquals(dart.isTopLimitSwitchTriggered(), false);
        dart.
    }
}