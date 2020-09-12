package bgu.spl.net.api;

import bgu.spl.net.srv.Connections;

import java.io.Serializable;

public interface MessagingProtocol<T> {

    /**
     * process the given message
     *
     * @param msg the received message
     * @return the response to send or null if no response is expected by the client
     */
    Serializable process(T msg);

    /**
     * start the MessagingProtocol
     *
     * @param connections connections initialize
     */
    void start(int id, Connections<T> connections);

    /**
     * @return true if the connection should be terminated
     */
    boolean shouldTerminate();

}