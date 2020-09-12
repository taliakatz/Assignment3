//
// Created by taliakat@wincs.cs.bgu.ac.il on 07/01/2020.
//
#include "../include/KeyBoardTask.h"
#include <boost/asio/ip/tcp.hpp>

using boost::asio::ip::tcp;
using namespace std;


KeyBoardTask::KeyBoardTask(ConnectionHandler *connectionHandler) : connectionHandler(connectionHandler), loggedIn(true) {}

void KeyBoardTask::operator()() {
    while (loggedIn) {
        short bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        connectionHandler->getMutexSplitVector().lock();
        std::vector<std::string> words = Tools::split(line, ' ');
        connectionHandler->getMutexSplitVector().unlock();

        string str;
        int receiptId = connectionHandler->getAndSetReceiptId();
        int subId = connectionHandler->getAndSetSubId();
        connectionHandler->getMutexFixSplitedVector().lock();
        words=Tools::fixSplitedVector(words);
        connectionHandler->getMutexFixSplitedVector().unlock();
        if(words[0] != "BYE") {
             if (words[0] == "join") {
                str = "SUBSCRIBE\ndestination:" + words[1] + "\nid:" + to_string(subId) + "\nreceipt:" + to_string(receiptId) + "\n\n";
                connectionHandler->getClientDetails().getReceiptMsg().insert({receiptId, "Joined club " + words[1]});
                connectionHandler->getClientDetails().getSubscriptions().insert({words[1], subId});

            } else if (words[0] == "exit") {
                int subId = connectionHandler->getClientDetails().getSubscriptions().find(words[1])->second;
                str = "UNSUBSCRIBE\nid:" + to_string(subId) + "\nreceipt:" + to_string(receiptId) + "\n\n";
                connectionHandler->getClientDetails().getReceiptMsg().insert({receiptId, "Exited club " + words[1]});
                connectionHandler->getClientDetails().getSubscriptions().erase(words[1]);

            } else if (words[0] == "add") {
                str = "SEND\ndestination:" + words[1] + "\n\n" + connectionHandler->getClientDetails().getName() +
                      " has added the book " + words[2] + "\n";
                connectionHandler->getClientDetails().getMutexInventory().lock();
                connectionHandler->getClientDetails().getInventory().push_back(words[2]);
                connectionHandler->getClientDetails().getMutexInventory().unlock();


             } else if (words[0] == "borrow") {
                str = "SEND\ndestination:" + words[1] + "\n\n" + connectionHandler->getClientDetails().getName() +
                      " wish to borrow " + words[2] + "\n";
                connectionHandler->getClientDetails().getMutexWishList().lock();
                connectionHandler->getClientDetails().getWishList().push_back(words[2]);
                connectionHandler->getClientDetails().getMutexWishList().unlock();

             }
            else if (words[0] == "return") {
                string lender = connectionHandler->getClientDetails().getBorrowedFrom().find(
                        words[2])->second; //i dont have anything in borrowed from
                str = "SEND\ndestination:" + words[1] + "\n\n" + "Returning " + words[2] + " to " + lender + "\n";
                connectionHandler->getClientDetails().deleteBook(words[2]);
            } else if (words[0] == "status") {
                str = "SEND\ndestination:" + words[1] + "\n\n" + "book status" + "\n";

            } else if (words[0] == "logout") {
                str = "DISCONNECT\nreceipt:" + to_string(receiptId) + "\n\n";
                connectionHandler->getClientDetails().getReceiptMsg().insert({receiptId, "close the socket"});
                loggedIn = false;
            }
            //Tools::printMessage(Tools::split(str, '\n'));
            connectionHandler->sendLine(str);
        }
        else if(words[0] == "BYE"){
            loggedIn = false;
            break;
        }
        else{
            cout<<"You are already logged in"<<endl;
        }
    }
}

KeyBoardTask::KeyBoardTask(const KeyBoardTask &other): connectionHandler(other.connectionHandler), loggedIn(other.loggedIn) {}

KeyBoardTask::~KeyBoardTask() {}

KeyBoardTask &KeyBoardTask::operator=(const KeyBoardTask &other) = default;






