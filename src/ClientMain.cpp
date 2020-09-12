//
// Created by taliakat@wincs.cs.bgu.ac.il on 08/01/2020.
//

#include "../include/ClientMain.h"
#include "../include/ConnectionHandler.h"
#include "../include/KeyBoardTask.h"
#include "../include/boost/accumulators/numeric/functional/vector.hpp"
#include "../include/ReadFromSocketTask.h"
#include <iostream>

using namespace std;
using boost::asio::ip::tcp;

ConnectionHandler *connectionHandler;

ClientMain::ClientMain() : clientDetails() {}

int main(int argc, char *argv[]) {
    bool isLoggedIn(false);
    while (!isLoggedIn) {
        short bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        std::vector<std::string> words = Tools::split(line, ' ');
        if (words[0] == "login") {
            isLoggedIn = true;
            std::vector<std::string> hostPort = Tools::split(words[1], ':');
            connectionHandler = new ConnectionHandler(hostPort[0], std::stoi(hostPort[1]));
            connectionHandler->getClientDetails().setName(words[2]);
            connectionHandler->getClientDetails().setPasscode(words[3]);
            bool isConnected = connectionHandler->connect();
            string str = "CONNECT\naccept-version:1.2\nhost:"+hostPort[0] + "\nlogin:"+words[2] +"\npasscode:"+words[3]+ "\n\n";
            connectionHandler->sendLine(str);
            KeyBoardTask keyBoardTask(connectionHandler);
            ReadFromSocketTask readFromSocketTask(connectionHandler);
            if (isConnected) {
                thread thread1(keyBoardTask);
                thread thread2(readFromSocketTask);
                thread1.join();
                thread2.join();
            }
            else {
                cout << "Could not connect to server" << endl;
            }
        }
        //isLoggedIn=false;
    }
    delete connectionHandler;
}