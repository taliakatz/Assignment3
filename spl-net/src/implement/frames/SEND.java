package bgu.spl.net.impl.Frames;

import bgu.spl.net.impl.User;
import bgu.spl.net.impl.stomp.ConnectionsImpl;
import bgu.spl.net.impl.stomp.StompMessagingProtocolImpl;

import java.util.LinkedList;

public class SEND extends Frame {
    private String destination;
    private String bodyFrame;

    public String getDestination() {
        return destination;
    }

    public String getBodyFrame() {
        return bodyFrame;
    }

    @Override
    public String toString (){
        return "SEND"+"\n"+"destination:"+destination+"\n"+"\n"+bodyFrame+"\n"+'\0';
    }

    @Override
    public String getName(){
        return "SEND";
    }

    @Override
    public void execute(StompMessagingProtocolImpl protocol) {

        ConnectionsImpl<Frame> connections=protocol.getConnections();

        LinkedList<User> users = connections.getUsersByTopic(this.getDestination());

        User user = protocol.getUserById(users);
        if (user != null) {
            Integer subId = user.getSubscriptions().get(this.getDestination());
            MESSAGE msgToSend = new MESSAGE(subId, this.getDestination(), this.getBodyFrame());
            connections.send(this.getDestination(), msgToSend);
        }
    }
}
