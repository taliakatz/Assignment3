package bgu.spl.net.impl.Frames;

import bgu.spl.net.impl.Pair;
import bgu.spl.net.impl.User;
import bgu.spl.net.impl.stomp.ConnectionsImpl;
import bgu.spl.net.impl.stomp.StompMessagingProtocolImpl;

import java.util.LinkedList;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;

public class UNSUBSCRIBE extends Frame {

    private int id;
    private int receipt;

    public int getId() {
        return id;
    }

    public int getReceipt() {
        return receipt;
    }

    @Override
    public String toString (){
        String st = "UNSUBSCRIBE"+"\n"+"id:"+id+"\n"+"\n"+'\0';
        return st;
    }
    @Override
    public String getName(){
        return "UNSUBSCRIBE";
    }

    @Override
    public void execute(StompMessagingProtocolImpl protocol) {
        ConnectionsImpl<Frame> connections=protocol.getConnections();
        int id=protocol.getId();

        User user = protocol.getUserById(new LinkedList<>(connections.getUsers().values()));
        ConcurrentHashMap<String,Integer> mapSub = user.getSubscriptions();
        Set<Map.Entry<String, Integer>> set = mapSub.entrySet();
        for(Map.Entry<String,Integer> entry: set){
            if(entry.getValue() == id){
                mapSub.remove(entry.getKey(), entry.getValue());
            }
        }
        RECEIPT msgToSend = new RECEIPT(this.getReceipt());
        connections.send(id, msgToSend);
    }
}
