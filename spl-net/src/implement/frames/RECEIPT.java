package bgu.spl.net.impl.Frames;

import bgu.spl.net.impl.stomp.StompMessagingProtocolImpl;

public class RECEIPT extends Frame {
    private int receipt_id;

    public RECEIPT(int receipt_id){
        super();
        this.receipt_id=receipt_id;
    }

    @Override
    public String toString (){
        return "RECEIPT"+"\n"+"receipt-id:"+receipt_id+"\n"+"\n"+'\0';
    }
    @Override
    public String getName(){
        return "RECEIPT";
    }

    @Override
    public void execute(StompMessagingProtocolImpl protocol) {

    }

}
