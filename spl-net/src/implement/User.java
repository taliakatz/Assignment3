package bgu.spl.net.impl;

import java.util.concurrent.ConcurrentHashMap;


public class User {
    private String name;
    private String passcode;
    private int idConnectionHandler;
    ConcurrentHashMap<String,Integer> subscriptions;
    private boolean connected;
  //  private List<Integer> subscriptionId;

    public User(String name, String passcode, int idConnectionHandler, boolean connected){
        this.name = name;
        this.passcode = passcode;
        this.idConnectionHandler = idConnectionHandler;
        this.connected = connected;
        this.subscriptions=new ConcurrentHashMap<>();
    }
    public String getName() {
        return name;
    }

    public ConcurrentHashMap<String,Integer> getSubscriptions() {
        return subscriptions;
    }

    public void addSubscription(String topic,int id){
        subscriptions.put(topic,id);
    }

    public int getIdConnectionHandler() {
        return idConnectionHandler;
    }

    public String getPasscode() {
        return passcode;
    }

    public void setIdConnectionHandler(int idConnectionHandler) {
        this.idConnectionHandler = idConnectionHandler;
    }

    public boolean isConnected (){
        return connected;
    }

    public void setConnected(boolean flag){
        connected=flag;
    }

    public int connectionID() {
        return idConnectionHandler;
    }
}
