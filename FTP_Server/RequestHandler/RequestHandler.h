#pragma once

#include <string>
#include <exception>
#include <vector>

#include "ClientState.h"

class Command {
public:
    virtual struct Response handleCommand() = 0;
    virtual bool isCorrect() = 0;
    virtual struct Response handleFaultyCommand() = 0;
};

class RequestHandler: public ClientState {

protected:
    const std::string root_path = "~/Student/semestr_6/TIN/Projekt/Program/TIN_FTP";

private:
    bool exit = false;
    
    // bool logged = false;
    // std::string username;
    // std::string curr_dir;
    int err = 0;

public:
    void Run();
    virtual Command * nextCommand() = 0;
    virtual void returnResponse(Response resp) = 0;
    
    virtual std::string dataTransmission() = 0;
    
protected:
    virtual void handleNoCommandFault() = 0;

private:
    //  int DoWork(std::string &resp_str);



    friend class ExitCommand;
};

struct Response{
    int err_code;       // 0 if correct; error code otherwise
    int operation;              //
    std::string msg_response;   // response to send to client
};

class ExitCommand : public Command {

private:
    RequestHandler * rh;

protected:
    void stopCommandHandler(){
        rh->exit = true;
    }

public:

    ExitCommand(RequestHandler * request_handler) : rh(request_handler){}

    bool isCorrect(){
        return true;
    }

    Response handleFaultyCommand(){
        Response response;

        return response;
    }

    Response handleCommand(){
        Response response;
        stopCommandHandler();
        return response;
    }
};
