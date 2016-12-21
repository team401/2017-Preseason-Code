package org.team401vision.configeditor.config;

import java.io.FileWriter;
import java.util.HashMap;
import java.util.Map;

/**
 * Created by cameronearle on 12/11/16.
 */
public class ConfigWriter {
    public static void write(ConfigBean configBean, String filePath) {
        try {
            FileWriter fileWriter = new FileWriter(filePath);

            if (configBean.isAutoExposure()) {
                fileWriter.write("autoExposure=1\n");
            } else {
                fileWriter.write("autoExposure=0\n");
            }
            if (configBean.isAutoWB()) {
                fileWriter.write("autoWB=1\n");
            } else {
                fileWriter.write("autoWB=0\n");
            }
            if (configBean.isAutoGain()) {
                fileWriter.write("autoGain=1\n");
            } else {
                fileWriter.write("autoGain=0\n");
            }
            fileWriter.write("exposure=" + Integer.toString(configBean.getExposure()) + "\n");
            fileWriter.write("saturation=" + Integer.toString(configBean.getSaturation()) + "\n");
            fileWriter.write("contrast=" + Integer.toString(configBean.getContrast()) + "\n");
            fileWriter.write("gain=" + Integer.toString(configBean.getGain()) + "\n");
            fileWriter.write("lowerBoundH=" + Integer.toString(configBean.getLowerBoundH()) + "\n");
            fileWriter.write("lowerBoundS=" + Integer.toString(configBean.getLowerBoundS()) + "\n");
            fileWriter.write("lowerBoundV=" + Integer.toString(configBean.getLowerBoundV()) + "\n");
            fileWriter.write("upperBoundH=" + Integer.toString(configBean.getUpperBoundH()) + "\n");
            fileWriter.write("upperBoundS=" + Integer.toString(configBean.getUpperBoundS()) + "\n");
            fileWriter.write("upperBoundV=" + Integer.toString(configBean.getUpperBoundV()) + "\n");
            fileWriter.write("cannyLowerBound=" + Integer.toString(configBean.getCannyLowerBound()) + "\n");
            fileWriter.write("cannyUpperBound=" + Integer.toString(configBean.getCannyUpperBound()) + "\n");

            fileWriter.close();

        } catch (Exception ignored) {
            System.exit(1);
        }

    }
}
