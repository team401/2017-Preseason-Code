package org.team401vision.networkclient.test;

import org.team401vision.networkclient.HeartbeatClient;
import org.team401vision.networkclient.NetworkClient;
import org.team401vision.networkclient.VisionData;

/**
 * Created by cameronearle on 12/4/16.
 */
public class MainTest {
    public static void main(String[] args) {
        HeartbeatClient heartbeatClient = new HeartbeatClient("127.0.0.1", 5800);
        NetworkClient networkClient = new NetworkClient("127.0.0.1", 5802);
        heartbeatClient.start();
        networkClient.start();


        while (true) {
            VisionData currentData = networkClient.getVisionData();
            if (heartbeatClient.isConnected()) {
                System.out.println(currentData.getYaw());
                System.out.println(currentData.getPitch());
                System.out.println(currentData.getDistance());
            }
            try {
                Thread.sleep(10);
            } catch (InterruptedException ignored) {}
        }
    }
}
