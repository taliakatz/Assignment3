package bgu.spl.net.impl.Frames;

import bgu.spl.net.impl.User;
import bgu.spl.net.impl.stomp.ConnectionsImpl;
import bgu.spl.net.impl.stomp.StompMessagingProtocolImpl;
import bgu.spl.net.srv.Connections;

public class CONNECT extends Frame {
    private double accept_version;
    private String host;
    private String login;
    private String passcode;


    public String getLogin() {
        return login;
    }

    public String getPasscode() {
        return passcode;
    }

    public double getAccept_version() {
        return accept_version;
    }

    public String getBodyFrame() {
        return "";
    }

    @Override
    public String toString() {
        return "CONNECT" + "\n" + "accept-version:" + accept_version + "\n" + "host:" + host + "\n" + "login:" + login + "\n" + "passcode:" + passcode + "\n" + "\n" + '\0';
    }

    @Override
    public String getName() {
        return "CONNECT";
    }

    @Override
    public void execute(StompMessagingProtocolImpl protocol) {

        ConnectionsImpl<Frame> connections = protocol.getConnections();
        int id = protocol.getId();

        connections.addUserIfAbsent(this.getLogin(), this.getPasscode(), id);

        User user = connections.getUsers().get(this.getLogin());

        Frame result;
        if (user.isConnected()) {
            result = new ERROR("User already logged in", this.getBodyFrame());
            connections.send(id, result);
            protocol.terminate = true;
            //connections.disconnect(id);
        } else if (!this.getPasscode().equals(user.getPasscode())) {
            result = new ERROR("Wrong password", this.getBodyFrame());
            connections.send(id, result);
            protocol.terminate = true;
            //connections.disconnect(id);
        } else {
            result=new CONNECTED(this.getAccept_version());
            user.setConnected(true);
            user.setIdConnectionHandler(id);
        }
        connections.send(id, result);
        String print = result.toString();

    }
}
