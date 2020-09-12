package bgu.spl.net.impl.Frames;

import bgu.spl.net.impl.stomp.StompMessagingProtocolImpl;

import java.util.concurrent.atomic.AtomicInteger;

public class MESSAGE extends Frame {
    private static AtomicInteger runner = new AtomicInteger(20);
    private int subscription;
    private int message_id;
    private String destination;
    private String bodyFrame;

    public MESSAGE(int subscription, String destination, String bodyFrame) {
        super();
        this.subscription = subscription;
        this.message_id = runner.incrementAndGet();
        this.destination = destination;
        this.bodyFrame = bodyFrame;
    }

    @Override
    public String toString() {
        return "MESSAGE" + "\n" + "subscription:" + subscription + "\n" + "message-id:" + message_id + "\n" + "destination:" + destination + "\n" + "\n" + bodyFrame + "\n" + '\0';
    }

    @Override
    public String getName() {
        return "MESSAGE";
    }

    @Override
    public void execute(StompMessagingProtocolImpl protocol) {

    }
}
