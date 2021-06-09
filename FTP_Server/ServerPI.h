#pragma once

#include "../NetFunctions/unp.h"
#include "RequestHandler/RequestHandler.h"

#include <string>
#include <iostream>
#include <unistd.h>



class ServerPI: public RequestHandler{
private:
    int msgsocket;
    int client_port;
    std::string client_addr;
    // std::string serv_addr; it could be useful during creating DTP connection


public:
    ServerPI(int msgsock, int cliport, std::string cliaddr);


    int Start();
    void PrintHelp();
    int SendResponse(Response resp);
    std::string WaitForRequest();

    void sendData(const std::string& data);
    std::string getData();

private:
    int SendDTPPort(int port);
    void *ServeClient(void* arg);
    void Greeting();
    short bindServerDTP(int sock);

    void handleNoCommandFault() override;
    Command *nextCommand() override;

    const std::string welcome_msg = "Welcome to FTP Server 1.0\nSend \"help\" to get information how to use server";
    // const int DTP_PORT = 22;
    const int UPLOAD_OP = 2;
    const int DOWNLOAD_OP = 3;
    
};


class HelpCommand : public Command {

private:
    ServerPI * spi;

public:

    HelpCommand(ServerPI * server_pi);

    bool isCorrect();

    void handleFaultyCommand();

    void handleCommand();
};
