//
// Created by taliakat@wincs.cs.bgu.ac.il on 07/01/2020.
//

#ifndef ASS3_KEYBOARDTASK_H
#define ASS3_KEYBOARDTASK_H

#include "ConnectionHandler.h"
#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include "ClientDetails.h"
#include "Tools.h"

using namespace std;

class KeyBoardTask{
private:
    ConnectionHandler* connectionHandler;
    bool loggedIn;

public:

    KeyBoardTask(ConnectionHandler *connectionHandler);
    KeyBoardTask(const KeyBoardTask& other);
    virtual ~KeyBoardTask();
    KeyBoardTask& operator=(const KeyBoardTask& other);

    void operator()();
};

#endif //ASS3_KEYBOARDTASK_H
