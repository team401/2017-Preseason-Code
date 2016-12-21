package org.team401vision.configeditor.config;

/**
 * Created by cameronearle on 12/11/16.
 */
public class ConfigBean {
    private boolean autoExposure;
    private boolean autoWB;
    private boolean autoGain;
    private int exposure;
    private int saturation;
    private int contrast;
    private int gain;
    private int lowerBoundH;
    private int lowerBoundS;
    private int lowerBoundV;
    private int upperBoundH;
    private int upperBoundS;
    private int upperBoundV;
    private int cannyLowerBound;
    private int cannyUpperBound;

    public ConfigBean(){}

    public ConfigBean(boolean autoExposure, boolean autoWB, boolean autoGain, int exposure, int saturation, int contrast, int gain, int lowerBoundH, int lowerBoundS, int lowerBoundV, int upperBoundH, int upperBoundS, int upperBoundV, int cannyLowerBound, int cannyUpperBound) {
        this.autoExposure = autoExposure;
        this.autoWB = autoWB;
        this.autoGain = autoGain;
        this.exposure = exposure;
        this.saturation = saturation;
        this.contrast = contrast;
        this.gain = gain;
        this.lowerBoundH = lowerBoundH;
        this.lowerBoundS = lowerBoundS;
        this.lowerBoundV = lowerBoundV;
        this.upperBoundH = upperBoundH;
        this.upperBoundS = upperBoundS;
        this.upperBoundV = upperBoundV;
        this.cannyLowerBound = cannyLowerBound;
        this.cannyUpperBound = cannyUpperBound;
    }

    public boolean isAutoExposure() {
        return autoExposure;
    }

    public void setAutoExposure(boolean autoExposure) {
        this.autoExposure = autoExposure;
    }

    public boolean isAutoWB() {
        return autoWB;
    }

    public void setAutoWB(boolean autoWB) {
        this.autoWB = autoWB;
    }

    public boolean isAutoGain() {
        return autoGain;
    }

    public void setAutoGain(boolean autoGain) {
        this.autoGain = autoGain;
    }

    public int getExposure() {
        return exposure;
    }

    public void setExposure(int exposure) {
        this.exposure = exposure;
    }

    public int getSaturation() {
        return saturation;
    }

    public void setSaturation(int saturation) {
        this.saturation = saturation;
    }

    public int getContrast() {
        return contrast;
    }

    public void setContrast(int contrast) {
        this.contrast = contrast;
    }

    public int getGain() {
        return gain;
    }

    public void setGain(int gain) {
        this.gain = gain;
    }

    public int getLowerBoundH() {
        return lowerBoundH;
    }

    public void setLowerBoundH(int lowerBoundH) {
        this.lowerBoundH = lowerBoundH;
    }

    public int getLowerBoundS() {
        return lowerBoundS;
    }

    public void setLowerBoundS(int lowerBoundS) {
        this.lowerBoundS = lowerBoundS;
    }

    public int getLowerBoundV() {
        return lowerBoundV;
    }

    public void setLowerBoundV(int lowerBoundV) {
        this.lowerBoundV = lowerBoundV;
    }

    public int getUpperBoundH() {
        return upperBoundH;
    }

    public void setUpperBoundH(int upperBoundH) {
        this.upperBoundH = upperBoundH;
    }

    public int getUpperBoundS() {
        return upperBoundS;
    }

    public void setUpperBoundS(int upperBoundS) {
        this.upperBoundS = upperBoundS;
    }

    public int getUpperBoundV() {
        return upperBoundV;
    }

    public void setUpperBoundV(int upperBoundV) {
        this.upperBoundV = upperBoundV;
    }

    public int getCannyLowerBound() {
        return cannyLowerBound;
    }

    public void setCannyLowerBound(int cannyLowerBound) {
        this.cannyLowerBound = cannyLowerBound;
    }

    public int getCannyUpperBound() {
        return cannyUpperBound;
    }

    public void setCannyUpperBound(int cannyUpperBound) {
        this.cannyUpperBound = cannyUpperBound;
    }
}
