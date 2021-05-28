#pragma once

#include "../NetFunctions/unp.h"
#include <string>
#include <iostream>


const std::string welcome_msg = "Welcome to FTP Server 1.0\nSend \"help\" to get information how to use server";

class ServerPI{
private:
    int msgsocket;
    int client_port;
    std::string client_addr;
    
    bool logged = false;
    std::string username;
    std::string curr_dir;

public:
    ServerPI(int msgsock, int cliport, std::string cliaddr);
    

    int Run();

private:
    void *ServeClient(void* arg);
    void Greeting();

};