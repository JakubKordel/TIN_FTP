#pragma once

#include "../NetFunctions/unp.h"
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

};