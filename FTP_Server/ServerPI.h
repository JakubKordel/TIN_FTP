#pragma once

#include "../NetFunctions/unp.h"
#include "../RequestHandler/RequestHandler.h"

#include <string>
#include <iostream>



class ServerPI: public RequestHandler{
private:
    int msgsocket;
    int client_port;
    std::string client_addr;


public:
    ServerPI(int msgsock, int cliport, std::string cliaddr);
    
    
    int Start();
    void PrintHelp();
    int SendResponse(Response resp);

private:
    void *ServeClient(void* arg);
    void Greeting();
    std::string WaitForRequest();

    void handleNoCommandFault() override;
    Command *nextCommand() override;
    void returnResponse(Response resp) override;

    const std::string welcome_msg = "Welcome to FTP Server 1.0\nSend \"help\" to get information how to use server";

};


class HelpCommand : public Command {

private:
    ServerPI * spi;

public:

    HelpCommand(ServerPI * server_pi);

    bool isCorrect();

    Response handleFaultyCommand();

    Response handleCommand();
};