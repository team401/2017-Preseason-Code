package org.team401vision.configeditor.config;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Stream;

/**
 * Created by cameronearle on 12/11/16.
 */
public class ConfigParser {
    public static ConfigBean parse(String filePath) {
        Map settingsMap = new HashMap();
        List<String> fileLines = new ArrayList<>();
        try (Stream<String> stream = Files.lines(Paths.get(filePath))) {
            stream.forEach(fileLines::add);
        } catch (IOException ignored) {}

        for (String s : fileLines) {
            if (s.contains("=")) {
                String[] data = s.split("=");
                settingsMap.put(data[0], data[1]);
            }
        }

        ConfigBean configBean = new ConfigBean();
        try {
            configBean.setAutoExposure(Integer.parseInt((String) settingsMap.getOrDefault("autoExposure", "0")) != 0);
        } catch (Exception ignored) {
            configBean.setAutoExposure(false);
        }
        try {
            configBean.setAutoWB(Integer.parseInt((String) settingsMap.getOrDefault("autoWB", "0")) != 0);
        } catch (Exception ignored) {
            configBean.setAutoWB(false);
        }
        try {
            configBean.setAutoGain(Integer.parseInt((String) settingsMap.getOrDefault("autoGain", "0")) != 0);
        } catch (Exception ignored) {
            configBean.setAutoGain(false);
        }
        try {
            configBean.setExposure(Integer.parseInt((String) settingsMap.getOrDefault("exposure", "20")));
        } catch (Exception ignored) {
            configBean.setExposure(20);
        }
        try {
            configBean.setSaturation(Integer.parseInt((String) settingsMap.getOrDefault("saturation", "255")));
        } catch (Exception ignored) {
            configBean.setSaturation(255);
        }
        try {
            configBean.setContrast(Integer.parseInt((String) settingsMap.getOrDefault("contrast", "0")));
        } catch (Exception ignored) {
            configBean.setContrast(0);
        }
        try {
            configBean.setGain(Integer.parseInt((String) settingsMap.getOrDefault("gain", "20")));
        } catch (Exception ignored) {
            configBean.setGain(20);
        }
        try {
            configBean.setLowerBoundH(Integer.parseInt((String) settingsMap.getOrDefault("lowerBoundH", "50")));
        } catch (Exception ignored) {
            configBean.setLowerBoundH(50);
        }
        try {
            configBean.setLowerBoundS(Integer.parseInt((String) settingsMap.getOrDefault("lowerBoundS", "250")));
        } catch (Exception ignored) {
            configBean.setLowerBoundS(250);
        }
        try {
            configBean.setLowerBoundV(Integer.parseInt((String) settingsMap.getOrDefault("lowerBoundV", "40")));
        } catch (Exception ignored) {
            configBean.setLowerBoundV(40);
        }
        try {
            configBean.setUpperBoundH(Integer.parseInt((String) settingsMap.getOrDefault("upperBoundH", "70")));
        } catch (Exception ignored) {
            configBean.setUpperBoundH(70);
        }
        try {
            configBean.setUpperBoundS(Integer.parseInt((String) settingsMap.getOrDefault("upperBoundS", "255")));
        } catch (Exception ignored) {
            configBean.setUpperBoundS(255);
        }
        try {
            configBean.setUpperBoundV(Integer.parseInt((String) settingsMap.getOrDefault("upperBoundV", "160")));
        } catch (Exception ignored) {
            configBean.setUpperBoundV(160);
        }
        try {
            configBean.setCannyLowerBound(Integer.parseInt((String) settingsMap.getOrDefault("cannyLowerBound", "30")));
        } catch (Exception ignored) {
            configBean.setCannyLowerBound(30);
        }
        try {
            configBean.setCannyUpperBound(Integer.parseInt((String) settingsMap.getOrDefault("cannyUpperBound", "60")));
        } catch (Exception ignored) {
            configBean.setCannyUpperBound(60);
        }

        return configBean;
    }
}
