package bgu.spl.net.srv;

import bgu.spl.net.impl.stomp.ConnectionsImpl;

public interface Connections<T> {

    boolean send(int connectionId, T msg);

    public static <T> Connections<T> getInstance(){
        return new ConnectionsImpl<>();
    };

    void send(String channel, T msg);

    void disconnect(int connectionId);

    public int add(ConnectionHandler<T> connectionHandler);
}
