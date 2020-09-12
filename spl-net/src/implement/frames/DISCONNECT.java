package bgu.spl.net.impl.Frames;

import bgu.spl.net.impl.stomp.ConnectionsImpl;
import bgu.spl.net.impl.stomp.StompMessagingProtocolImpl;

import java.util.LinkedList;

public class DISCONNECT extends Frame {
    private int receipt;

    public int getReceipt() {
        return receipt;
    }

    @Override
    public String toString (){
        return "DISCONNECT"+"\n"+"receipt:"+receipt+"\n"+"\n"+'\0';
    }
    @Override
    public String getName(){
        return "DISCONNECT";
    }

    @Override
    public void execute(StompMessagingProtocolImpl protocol) {
        ConnectionsImpl<Frame> connections=protocol.getConnections();
        int id=protocol.getId();
        RECEIPT msgToSend = new RECEIPT(this.getReceipt());
        protocol.getUserById(new LinkedList<>(connections.getUsers().values())).setConnected(false);
        connections.send(id, msgToSend);
        //connections.disconnect(id);

    }
}
