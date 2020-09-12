//
// Created by taliakat@wincs.cs.bgu.ac.il on 09/01/2020.
//

#include "../include/ReadFromSocketTask.h"
#include <boost/asio/ip/tcp.hpp>
//#include <KeyBoardTask.h>

ReadFromSocketTask::ReadFromSocketTask(ConnectionHandler *connectionHandler) : connectionHandler(connectionHandler),
                                                                               loggedIn(true) {}

void ReadFromSocketTask::operator()() {
    while (loggedIn) {
        string str;
        connectionHandler->getLine(str);

        connectionHandler->getMutexSplitVector().lock();
        vector<string> words = Tools::split(str, '\n');
        connectionHandler->getMutexSplitVector().unlock();
        Tools::printMessage(words);
        if (words[0] == "RECEIPT") {
            connectionHandler->getMutexSplitVector().lock();
            vector<string> receiptVector = Tools::split(words[1], ':');
            connectionHandler->getMutexSplitVector().unlock();
            string msg = connectionHandler->getClientDetails().getReceiptMsg().find(stoi(receiptVector[1]))->second;
            if (msg != "close the socket") {
                cout << connectionHandler->getClientDetails().getReceiptMsg().find(stoi(receiptVector[1]))->second
                     << std::endl;
            } else {
                loggedIn = false;
                connectionHandler->close();
            }
        } else if (words[0] == "CONNECTED") {
            cout << "Login Successful" << endl;
        } else if (words[0] == "MESSAGE") {
            connectionHandler->getMutexSplitVector().lock();
            vector<string> bodyMessage = Tools::split(words[5], ' ');
            connectionHandler->getMutexSplitVector().unlock();

            connectionHandler->getMutexFixSplitedVector().lock();
            bodyMessage = Tools::fixSplitedVector(bodyMessage);
            connectionHandler->getMutexFixSplitedVector().unlock();

            connectionHandler->getMutexSplitVector().lock();
            vector<string> destination = Tools::split(words[3], ':');
            connectionHandler->getMutexSplitVector().unlock();

            connectionHandler->getMutexSplitVector().lock();
            vector<string> subId = Tools::split(words[1], ':');
            connectionHandler->getMutexSplitVector().unlock();


            bool flag = true;
            for (size_t i = 0; (i < bodyMessage.size()) & flag; i++) {
                if (bodyMessage[i] == "borrow") {
                    string book = bodyMessage[bodyMessage.size() - 1];
                    int ans = connectionHandler->getClientDetails().findBookIndex(book);
                    if (ans != -1 && bodyMessage[0] != connectionHandler->getClientDetails().getName()) {
                        string str = "SEND\ndestination:" + destination[1] + "\n\n" +
                                     connectionHandler->getClientDetails().getName() + " has " +
                                     bodyMessage[bodyMessage.size() - 1] + "\n";
                        connectionHandler->sendLine(str);
                        flag = false;
                    }
                }
            }
            if (flag) {
                unordered_map<std::string, int> subs = connectionHandler->getClientDetails().getSubscriptions();
                auto subscriptionNum = subs.find(destination[1]);
                if (subscriptionNum != subs.end()) {
                    int value = subscriptionNum->second;
                    bool ans = value == stoi(subId[1]);

                    if (bodyMessage.size() == 3 && bodyMessage[1] == "has" && ans &&
                        bodyMessage[0] != connectionHandler->getClientDetails().getName()) {
                        int bookInWishList = connectionHandler->getClientDetails().findBookInWishList(bodyMessage[2]);
                        if (bookInWishList != -1) {
                            connectionHandler->getClientDetails().getMutexBorrowedFrom().lock();
                            connectionHandler->getClientDetails().getBorrowedFrom().insert(
                                    {bodyMessage[2], bodyMessage[0]});
                            connectionHandler->getClientDetails().getMutexBorrowedFrom().unlock();
                            connectionHandler->getClientDetails().getMutexWishList().lock();
                            connectionHandler->getClientDetails().getWishList().erase(
                                    connectionHandler->getClientDetails().getWishList().begin() + bookInWishList);
                            connectionHandler->getClientDetails().getMutexWishList().unlock();
                            connectionHandler->getClientDetails().getMutexInventory().lock();
                            connectionHandler->getClientDetails().getInventory().push_back(bodyMessage[2]);
                            connectionHandler->getClientDetails().getMutexInventory().unlock();
                            string str = "SEND\ndestination:" + destination[1] + "\n\n" + "Taking " +
                                         bodyMessage[bodyMessage.size() - 1] + " from " + bodyMessage[0] + "\n";
                            connectionHandler->sendLine(str);
                        }

                    } else if (bodyMessage[0] == "Taking" &&
                               bodyMessage[bodyMessage.size() - 1] == connectionHandler->getClientDetails().getName()) {
                        string book = bodyMessage[1];
                        string returnBook = connectionHandler->getClientDetails().deleteBook(book);

                    } else if (bodyMessage[0] == "Returning" &&
                               bodyMessage[bodyMessage.size() - 1] == connectionHandler->getClientDetails().getName()) {
                        connectionHandler->getClientDetails().getInventory().push_back(bodyMessage[1]);
                    } else if (bodyMessage.size() > 1 && bodyMessage[1] == "status") {
                        string inventory = connectionHandler->getClientDetails().printInventory();
                        string str = "SEND\ndestination:" + destination[1] + "\n\n" +
                                     connectionHandler->getClientDetails().getName() + ":" + inventory + "\n";
                        connectionHandler->sendLine(str);
                    }

                }
            }
        } else if (words[0] == "ERROR") {
            loggedIn = false;
            cout << "An error occurred. Please enter BYE:" << endl;
            connectionHandler->close();

        }
    }
}

ReadFromSocketTask::ReadFromSocketTask(
        const ReadFromSocketTask &other) : connectionHandler(other.connectionHandler),
                                           loggedIn(other.loggedIn) {}

ReadFromSocketTask::~ReadFromSocketTask() {}

ReadFromSocketTask &ReadFromSocketTask::operator=(const ReadFromSocketTask &other) = default;



