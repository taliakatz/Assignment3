package bgu.spl.net.impl.Frames;


import bgu.spl.net.impl.stomp.StompMessagingProtocolImpl;

public class CONNECTED extends Frame {
    private double version;

    public CONNECTED(double version){
        super();
        this.version=version;

    }

    public double getVersion() {
        return version;
    }

    public String getBodyFrame (){
        return "";
    }

    public String toString (){
        return "CONNECTED\nversion:"+version+"\n\n\0";
    }
    public String getName(){
        return "CONNECTED";
    }

    public void execute(StompMessagingProtocolImpl protocol) {

    }
}
