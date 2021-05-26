#pragma once

#include <string>
#include <iostream>
#include "unp.h"


static const int MAX_CLIENTS = 6;

class FTPServer{

    std::string ip_addr;
    std::string port;

    int listenfd;
    socklen_t servaddr, cliaddr;

public:
    FTPServer();
    FTPServer(char *nport);
    FTPServer(char *nip_addr, char *nport);

    int Start();

    void WriteOut();
private:

    int BindSock(int sock);


};