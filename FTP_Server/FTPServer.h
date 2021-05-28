#pragma once

#include <string>
#include <iostream>
#include "../NetFunctions/unp.h"


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
    void SaveServAddress(struct sockaddr_in &server, int sock);
    void PassClientToServe(int msgsock, struct sockaddr_in & cliaddr);

};

void *CreateServerPI(void *arg);


int CreateServerPIThread(pthread_t *tid, pthread_attr_t *attr, void *(*func)(void *), void *arg);

struct ServerPIArgs{
    int msgsock;
    int cliport;
    std::string cliaddr;
};