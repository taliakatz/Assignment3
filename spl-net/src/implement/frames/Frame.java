package bgu.spl.net.impl.Frames;

import bgu.spl.net.impl.stomp.StompMessagingProtocolImpl;

public abstract class Frame {

    public abstract  String  toString ();

    public abstract String getName();

    public abstract void execute(StompMessagingProtocolImpl protocol);
}
