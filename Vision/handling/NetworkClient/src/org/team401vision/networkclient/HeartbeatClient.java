package org.team401vision.networkclient;

import org.zeromq.ZMQ;

import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicReference;

/**
 * Created by cameronearle on 12/17/16.
 */

@Deprecated
public class HeartbeatClient extends Thread {
    private ZMQ.Context context;
    private ZMQ.Socket socket;
    private AtomicBoolean connected = new AtomicBoolean(false);
    public HeartbeatClient(String address, int port) {
        context = ZMQ.context(1);
        socket = context.socket(ZMQ.SUB);
        socket.setReceiveTimeOut(10000);
        socket.subscribe("".getBytes());
        socket.connect("tcp://" + address + ":" + port);
    }

    public boolean isConnected() {
        return connected.get();
    }

    public Thread getThread() {
        return currentThread();
    }

    @Override
    public void run() {
        while (!currentThread().isInterrupted()) {
            connected.set(socket.recvStr() != null);
        }
    }
}
