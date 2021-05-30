#pragma once

#include "../NetFunctions/unp.h"
#include "ServiceProvider.h"

#include <string>
#include <iostream>



class ServerPI{
private:
    int msgsocket;
    int client_port;
    std::string client_addr;


public:
    ServerPI(int msgsock, int cliport, std::string cliaddr);
    

    int Run();

private:
    void *ServeClient(void* arg);
    void Greeting();
    std::string WaitForRequest();

    const std::string welcome_msg = "Welcome to FTP Server 1.0\nSend \"help\" to get information how to use server";

};