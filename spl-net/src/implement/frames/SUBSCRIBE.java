package bgu.spl.net.impl.Frames;

import bgu.spl.net.impl.User;
import bgu.spl.net.impl.stomp.ConnectionsImpl;
import bgu.spl.net.impl.stomp.StompMessagingProtocolImpl;

import java.util.LinkedList;

public class SUBSCRIBE extends Frame {
    private String destination;
    private int id;
    private int receipt;

    public int getId() {
        return id;
    }

    public int getReceipt() {
        return receipt;
    }

    public String getDestination() {
        return destination;
    }

    @Override
    public String toString (){
        return "SUBSCRIBE"+"\n"+"destination:"+destination+"\n"+"id:"+id+"\n"+"\n"+'\0';
    }
    @Override
    public String getName(){
        return "SUBSCRIBE";
    }

    @Override
    public void execute(StompMessagingProtocolImpl protocol) {

        ConnectionsImpl<Frame> connections=protocol.getConnections();
        int id=protocol.getId();
        User user = protocol.getUserById(new LinkedList<>( connections.getUsers().values()));
        user.getSubscriptions().put(this.getDestination(), this.getId());
        RECEIPT msgToSend = new RECEIPT(this.getReceipt());
        connections.send(id, msgToSend);
    }

}
