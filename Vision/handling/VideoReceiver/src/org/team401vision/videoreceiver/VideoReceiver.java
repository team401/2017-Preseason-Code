package org.team401vision.videoreceiver;

import boofcv.gui.image.ImagePanel;
import boofcv.gui.image.ShowImages;
import org.zeromq.ZMQ;

import javax.imageio.ImageIO;
import java.io.ByteArrayInputStream;

/**
 * Created by cameronearle on 12/4/16.
 */
public class VideoReceiver {

    static ZMQ.Context context = ZMQ.context(1);
    static ZMQ.Socket socket;
    public static void main(String[] args) {
        AddressSelector addressSelector = new AddressSelector();
        addressSelector.pack();
        addressSelector.setVisible(true);
        String address = addressSelector.getAddress();
        socket = context.socket(ZMQ.SUB);
        socket.connect("tcp://" + address);
        socket.subscribe("".getBytes());
        ImagePanel panel = new ImagePanel(640,480);
        ShowImages.showWindow(panel, "Robot Camera Feed", true);
        while (true) {
            try {
                panel.setBufferedImage(ImageIO.read(new ByteArrayInputStream(socket.recv())));
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}
