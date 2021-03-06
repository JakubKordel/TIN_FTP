#pragma once

#include <string>
#include <exception>
#include <vector>
#include <iostream>

#include "ClientState.h"

class Command {
public:
    virtual ~Command() = default;
    virtual void handleCommand() = 0;
    virtual bool isCorrect() = 0;
    virtual void handleFaultyCommand() = 0;
};

class RequestHandler: public ClientState {

protected:
    bool exitHandler = false;


    int err = 0;

public:
    void Run();
    virtual Command * nextCommand() = 0;

protected:
    virtual void handleNoCommandFault() = 0;

private:
    //  int DoWork(std::string &resp_str);



    friend class ExitCommand;
};

struct Response{
    std::string status_code;       // 3 digits
    std::string msg_response;   // response to send to client
};

class ExitCommand : public Command {

private:
    RequestHandler * rh;

protected:
    void stopCommandHandler(){
        rh->exitHandler = true;
    }

public:

    ExitCommand(RequestHandler * request_handler) : rh(request_handler){}

    bool isCorrect(){
        return true;
    }

    void handleFaultyCommand(){

    }

    void handleCommand(){
        stopCommandHandler();
    }
};
