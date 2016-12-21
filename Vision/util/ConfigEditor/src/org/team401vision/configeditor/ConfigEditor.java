package org.team401vision.configeditor;

import org.team401vision.configeditor.config.ConfigBean;
import org.team401vision.configeditor.config.ConfigParser;
import org.team401vision.configeditor.config.ConfigWriter;
import org.team401vision.configeditor.gui.FileSelectDialog;
import org.team401vision.configeditor.gui.MainDialog;

/**
 * Created by cameronearle on 12/11/16.
 */
public class ConfigEditor {
    public static void main(String[] args) {
        FileSelectDialog fileSelectDialog = new FileSelectDialog();
        fileSelectDialog.pack();
        fileSelectDialog.setVisible(true);
        String filePath = fileSelectDialog.getFilePath();

        ConfigBean configBean = ConfigParser.parse(filePath);

        MainDialog mainDialog = new MainDialog(configBean);
        mainDialog.pack();
        mainDialog.setVisible(true);

        ConfigBean newSettings = mainDialog.getConfigBean();

        ConfigWriter.write(newSettings, filePath);
    }
}
