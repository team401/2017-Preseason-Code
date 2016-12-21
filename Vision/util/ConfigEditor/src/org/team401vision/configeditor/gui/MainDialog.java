package org.team401vision.configeditor.gui;

import org.team401vision.configeditor.config.ConfigBean;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.text.DefaultFormatter;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.util.List;

public class MainDialog extends JDialog {
    private JPanel contentPane;
    private JButton buttonOK;
    private JButton buttonCancel;
    private JCheckBox autoExposureCheckbox;
    private JCheckBox autoWBCheckbox;
    private JCheckBox autoGainCheckbox;
    private JSpinner exposureSpinner;
    private JSpinner saturationSpinner;
    private JSpinner contrastSpinner;
    private JSpinner lowerBoundHSpinner;
    private JSpinner lowerBoundSSpinner;
    private JSpinner lowerBoundVSpinner;
    private JLabel lowerBoundColorPreviewLabel;
    private JLabel upperBoundColorPreviewLabel;
    private JSpinner cannyLowerBoundSpinner;
    private JSpinner cannyUpperBoundSpinner;
    private JSpinner upperBoundHSpinner;
    private JSpinner upperBoundSSpinner;
    private JSpinner upperBoundVSpinner;
    private JCheckBox lowerBoundStandardCheckbox;
    private JCheckBox upperBoundStandardCheckbox;
    private JSpinner gainSpinner;

    public MainDialog(ConfigBean configBean) {
        setContentPane(contentPane);
        setModal(true);
        getRootPane().setDefaultButton(buttonOK);

        buttonOK.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                onOK();
            }
        });

        buttonCancel.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                onCancel();
            }
        });

        // call onCancel() when cross is clicked
        setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
        addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent e) {
                onCancel();
            }
        });

        // call onCancel() on ESCAPE
        contentPane.registerKeyboardAction(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                onCancel();
            }
        }, KeyStroke.getKeyStroke(KeyEvent.VK_ESCAPE, 0), JComponent.WHEN_ANCESTOR_OF_FOCUSED_COMPONENT);

        List<JComponent> componentList = new ArrayList<>();
        componentList.add(lowerBoundHSpinner.getEditor());
        componentList.add(lowerBoundSSpinner.getEditor());
        componentList.add(lowerBoundVSpinner.getEditor());
        componentList.add(upperBoundHSpinner.getEditor());
        componentList.add(upperBoundSSpinner.getEditor());
        componentList.add(upperBoundVSpinner.getEditor());
        for (JComponent comp : componentList) {
            JFormattedTextField field = (JFormattedTextField) comp.getComponent(0);
            DefaultFormatter formatter = (DefaultFormatter) field.getFormatter();
            formatter.setCommitsOnValidEdit(true);
        }

        lowerBoundHSpinner.addChangeListener((ChangeEvent e) -> updatePreviewColor(0,0)); //There Zach, I used a Lambda.
        lowerBoundSSpinner.addChangeListener((ChangeEvent e) -> updatePreviewColor(0,0)); //Hey, that was pretty neat, maybe I'll use 6 more
        lowerBoundVSpinner.addChangeListener((ChangeEvent e) -> updatePreviewColor(0,0));
        upperBoundHSpinner.addChangeListener((ChangeEvent e) -> updatePreviewColor(1,0));
        upperBoundSSpinner.addChangeListener((ChangeEvent e) -> updatePreviewColor(1,0));
        upperBoundVSpinner.addChangeListener((ChangeEvent e) -> updatePreviewColor(1,0));
        lowerBoundStandardCheckbox.addItemListener((ItemEvent e) -> updatePreviewColor(0,1));
        upperBoundStandardCheckbox.addItemListener((ItemEvent e) -> updatePreviewColor(1,1));


        autoExposureCheckbox.setSelected(configBean.isAutoExposure());
        autoWBCheckbox.setSelected(configBean.isAutoWB());
        autoGainCheckbox.setSelected(configBean.isAutoGain());
        exposureSpinner.setValue(configBean.getExposure());
        saturationSpinner.setValue(configBean.getSaturation());
        contrastSpinner.setValue(configBean.getContrast());
        gainSpinner.setValue(configBean.getGain());
        lowerBoundHSpinner.setValue(configBean.getLowerBoundH());
        lowerBoundSSpinner.setValue(configBean.getLowerBoundS());
        lowerBoundVSpinner.setValue(configBean.getLowerBoundV());
        upperBoundHSpinner.setValue(configBean.getUpperBoundH());
        upperBoundSSpinner.setValue(configBean.getUpperBoundS());
        upperBoundVSpinner.setValue(configBean.getUpperBoundV());
        cannyLowerBoundSpinner.setValue(configBean.getCannyLowerBound());
        cannyUpperBoundSpinner.setValue(configBean.getCannyUpperBound());

    }

    private void onOK() {
        // add your code here
        dispose();
    }

    private void onCancel() {
        // add your code here if necessary
        dispose();
        System.exit(0);
    }

    public ConfigBean getConfigBean() {
        ConfigBean configBean = new ConfigBean();
        configBean.setAutoExposure(autoExposureCheckbox.isSelected());
        configBean.setAutoWB(autoWBCheckbox.isSelected());
        configBean.setAutoGain(autoGainCheckbox.isSelected());
        configBean.setExposure((int) exposureSpinner.getValue());
        configBean.setSaturation((int) saturationSpinner.getValue());
        configBean.setContrast((int) contrastSpinner.getValue());
        configBean.setGain((int) gainSpinner.getValue());
        if (lowerBoundStandardCheckbox.isSelected()) {
            int origS = (int) lowerBoundSSpinner.getValue();
            int origV = (int) lowerBoundVSpinner.getValue();
            int h = (int) lowerBoundHSpinner.getValue() / 2;
            float s = ((float) origS / 100f) * 255;
            float v = ((float) origV / 100f) * 255;
            configBean.setLowerBoundH(h);
            configBean.setLowerBoundS((int) s);
            configBean.setLowerBoundV((int) v);
        } else {
            configBean.setLowerBoundH((int) lowerBoundHSpinner.getValue());
            configBean.setLowerBoundS((int) lowerBoundSSpinner.getValue());
            configBean.setLowerBoundV((int) lowerBoundVSpinner.getValue());
        }
        if (upperBoundStandardCheckbox.isSelected()) {
            int origS = (int) upperBoundSSpinner.getValue();
            int origV = (int) upperBoundVSpinner.getValue();
            int h = (int) upperBoundHSpinner.getValue() / 2;
            float s = ((float) origS / 100f) * 255;
            float v = ((float) origV / 100f) * 255;
            configBean.setUpperBoundH(h);
            configBean.setUpperBoundS((int) s);
            configBean.setUpperBoundV((int) v);
        } else {
            configBean.setUpperBoundH((int) upperBoundHSpinner.getValue());
            configBean.setUpperBoundS((int) upperBoundSSpinner.getValue());
            configBean.setUpperBoundV((int) upperBoundVSpinner.getValue());
        }
        configBean.setCannyLowerBound((int) cannyLowerBoundSpinner.getValue());
        configBean.setCannyUpperBound((int) cannyUpperBoundSpinner.getValue());

        return configBean;
    }

    private void updatePreviewColor(int which, int who) {
        if (which == 0) {
            if (lowerBoundStandardCheckbox.isSelected()) {
                int origH = (int) lowerBoundHSpinner.getValue();
                int origS = (int) lowerBoundSSpinner.getValue();
                int origV = (int) lowerBoundVSpinner.getValue();
                float h = (float) origH / 360f; //Java wants a weird hue input, this is the conversion
                float s = (float) origS / 100f;
                float v = (float) origV / 100f;
                lowerBoundColorPreviewLabel.setBackground(Color.getHSBColor(h, s, v));
            } else { //Well now we have to do stupid math.
                int origH = (int) lowerBoundHSpinner.getValue();
                int origS = (int) lowerBoundSSpinner.getValue(); //Ok so I figured out the stupid math I have to do
                int origV = (int) lowerBoundVSpinner.getValue(); //And it is very stupid, I can assure you that
                float h = ((float) origH*2) / 360f; //Because stupid OpenCV uses a stupid half cylinder
                float s = (float) origS / 255f; //Because stupid OpenCV uses some weird (stupid) 255 system for S&V
                float v = (float) origV / 255f; //Because stupid OpenCV is still stupid
                lowerBoundColorPreviewLabel.setBackground(Color.getHSBColor(h, s, v));
            }
        } else {
            if (upperBoundStandardCheckbox.isSelected()) {
                int origH = (int) upperBoundHSpinner.getValue();
                int origS = (int) upperBoundSSpinner.getValue();
                int origV = (int) upperBoundVSpinner.getValue();
                float h = (float) origH / 360f;
                float s = (float) origS / 100f;
                float v = (float) origV / 100f;
                upperBoundColorPreviewLabel.setBackground(Color.getHSBColor(h, s, v));
            } else {
                int origH = (int) upperBoundHSpinner.getValue();
                int origS = (int) upperBoundSSpinner.getValue();
                int origV = (int) upperBoundVSpinner.getValue();
                float h = ((float) origH*2) / 360f;
                float s = (float) origS / 255f;
                float v = (float) origV / 255f;
                upperBoundColorPreviewLabel.setBackground(Color.getHSBColor(h, s, v));
            }
        }
    }

}
