package bgu.spl.net.api;

import bgu.spl.net.srv.Connections;

import java.io.Serializable;

public interface StompMessagingProtocol<T>  {
	/**
	 * Used to initiate the current client protocol with it's personal connection ID and the connections implementation
	**/
    void start(int connectionId, Connections<T> connections);
    
    void process(T message);
	
	/**
     * @return true if the connection should be terminated
     */
    boolean shouldTerminate();

	/**
	 * after calling this method {@code: shouldTerminate()} should return true
	 */
    void terminate();

}
