package org.team401.robot;

import org.strongback.components.ui.ContinuousRange;

/**
 * Created by cameronearle on 12/31/2016.
 */
public class ScaledRange {
    private ContinuousRange range;
    private double multiplier;

    public ScaledRange(ContinuousRange range, double multiplier)  {
        this.range = range;
        this.multiplier = multiplier;
    }

    public ScaledRange() {}

    public ContinuousRange getRange() {
        return range;
    }

    public void setRange(ContinuousRange range) {
        this.range = range;
    }

    public double getMultiplier() {
        return multiplier;
    }

    public void setMultiplier(double multiplier) {
        this.multiplier = multiplier;
    }

    public double readScaled() {
        return range.read() * multiplier;
    }
}
