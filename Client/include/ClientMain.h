//
// Created by taliakat@wincs.cs.bgu.ac.il on 08/01/2020.
//

#ifndef ASS3_CLIENTMAIN_H
#define ASS3_CLIENTMAIN_H

#include <boost/asio/ip/tcp.hpp>
#include "ClientDetails.h"
#include <thread>

using namespace std;
using boost::asio::ip::tcp;
//using boost::thread;

class ClientMain {
private:
    ClientDetails clientDetails;
public:
    ClientMain();

};


#endif //ASS3_CLIENTMAIN_H
