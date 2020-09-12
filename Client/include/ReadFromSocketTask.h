//
// Created by taliakat@wincs.cs.bgu.ac.il on 09/01/2020.
//

#ifndef ASS3_READFROMSOCKETTASK_H
#define ASS3_READFROMSOCKETTASK_H

#include "ConnectionHandler.h"
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "ClientDetails.h"
#include "Tools.h"

using namespace std;

class ReadFromSocketTask {

private:
    ConnectionHandler* connectionHandler;
    bool loggedIn;

public:

    ReadFromSocketTask(ConnectionHandler *connectionHandler);
    ReadFromSocketTask(const ReadFromSocketTask& other);
    virtual ~ReadFromSocketTask();
    ReadFromSocketTask& operator=(const ReadFromSocketTask& other);
    void operator()();

};
#endif //ASS3_READFROMSOCKETTASK_H
