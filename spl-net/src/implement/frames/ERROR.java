package bgu.spl.net.impl.Frames;

import bgu.spl.net.impl.stomp.StompMessagingProtocolImpl;

public class ERROR extends Frame {
    private String message;
    private String bodyFrame;

    public ERROR( String message, String bodyFrame){
        super();
        this.message = message;
        this.bodyFrame = bodyFrame;
    }
    @Override
    public String toString (){
        return "ERROR"+"\n"+"message:"+message+"\n"+"\n"+bodyFrame+"\n"+'\0';
    }
    @Override
    public String getName(){
        return "ERROR";
    }

    @Override
    public void execute(StompMessagingProtocolImpl protocol) {

    }
}
