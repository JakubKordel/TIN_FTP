#ifndef _COMMANDS_H
#define _COMMANDS_H

#include <string>
#include <iostream>
#include <fstream>
#include "RequestHandler.h"
#include "helpStringsOperations.h"

#include "../Authentication/Authentication.h"

class StringShapeCommand : public Command {
private:

    void splitArguments(){
        splitToWords(command, args);
    }

protected:

    std::string command;
    std::vector<std::string> args;

    int argumentsMinimum;
    int argumentsMaximum;
    std::string commandDescription;
    std::vector<std::string> argsNames;

public:

    StringShapeCommand(std::string str){
        command = str;
        splitArguments();
    }  

    void printHelp(){
        std::cout << "Command: " << argsNames[0] << std::endl;
        std::vector<std::string>::iterator it = argsNames.begin();
        std::cout << "Usage: " << *it;
        ++it;
    for (it ; it != argsNames.end(); ++it)
        std::cout << " [ " << *it << " ] ";
        std::cout << std::endl << commandDescription << std::endl;
    }

    bool isCorrect(){
        return (args.size() >= 2 && args[1] == "--help") || (args.size() >= argumentsMinimum && args.size() <= argumentsMaximum);
    }

    Response handleFaultyCommand(){
        Response response;
        response.err_code = 1;
        response.msg_response = "Too many / less arguments\n"
                                "See help for more information";
        std::cout << std::endl << "ERROR: Bad argumets" << std::endl;
        printHelp();
        return response;
    }

    Response handleCommand(){
        Response response;
        if (args[1] == "--help")
            printHelp();
        else
            return handle();
        return response;
    }


    virtual Response handle() = 0;
};

class LoginCommand : public StringShapeCommand {
private:
    std::string root_path;
    RequestHandler *rq;
public:
    LoginCommand(RequestHandler *request_handler, std::string string) : rq(request_handler), StringShapeCommand(string) {
        argumentsMinimum = 3;
        argumentsMaximum = 3;
        commandDescription = "Connects and logins user to the server";
        argsNames.push_back("login");
        argsNames.push_back("username");
        argsNames.push_back("password");
        argsNames.push_back("serveradress");
    }

    Response handle(){
        Response response;
        std::cout << std::endl << "I AM HANDLING LOGIN COMMAND" << std::endl;

        Authentication auth;
        bool issuccess = auth.login(args.at(1), args.at(2));
        if( issuccess ){
            response.err_code = 0;
            response.msg_response = "OK, you have been logged in";
        }else{
            response.err_code = 1;
            response.msg_response = "Login error, wrong username or password";
        }

        return response;
    }
};

class LogoutCommand : public StringShapeCommand {
private:
    bool logged;
    RequestHandler *rq;
public:
    LogoutCommand(RequestHandler *request_handler, std::string string) : rq(request_handler), StringShapeCommand(string) {
        argumentsMinimum = 1;
        argumentsMaximum = 1;
        commandDescription = "Logouts and disconnects user from server";
        argsNames.push_back("logout");
    }

    Response handle(){
        Response response;
        
        if(rq->logged == false){
            // user is not logged in generate error
            response.err_code = 1;
            response.msg_response = "Logout error, you are not logged";
        }else{
            rq->logged = false;
            rq->username = "";
            response.err_code = 0;
            response.msg_response = "OK, you have been logged out";
        }

        std::cout << std::endl << "I AM HANDLING LOGOUT COMMAND" << std::endl;
        return response;
    }
};

class UploadCommand : public StringShapeCommand {
private:
    RequestHandler *rq;
public:
    UploadCommand(RequestHandler *request_handler, std::string string) : rq(request_handler), StringShapeCommand(string) {
        argumentsMinimum = 2;
        argumentsMaximum = 2;
        commandDescription = "Uploads file to the server";
        argsNames.push_back("upload");
        argsNames.push_back("file");
    }

    Response handle(){
        Response response;
        std::cout << std::endl << "I AM UPLOADING FILE TO THE SERVER" << std::endl;
        
        if( rq->logged == false ){
            response.err_code = 2; //LOGGED_OUT
            response.msg_response = "Error uploading, you have to be logged in to upload files";
        }else{
            // ((ServerPI*)rq)->initServerDTP();
            std::string data = rq->dataTransmission();
            // ServerPI create new listen socket for transmission data
            // ServerPI sends to client new port for data connection
            // then 
        }

        return response;
    }
};

class DownloadCommand : public StringShapeCommand {
    RequestHandler *rq;
public:
    DownloadCommand(RequestHandler *request_handler, std::string string) : rq(request_handler),  StringShapeCommand(string) {
        argumentsMinimum = 2;
        argumentsMaximum = 2;
        commandDescription = "Downloads file from the server";
        argsNames.push_back("download");
        argsNames.push_back("file");
    }

    Response handle(){
        Response response;
        std::cout << std::endl << "I AM DOWNLOADING FILE FROM THE SERVER" << std::endl;
        
        return response;
    }
};

class MkdirCommand : public StringShapeCommand {
private:
    RequestHandler *rq;

public:
    MkdirCommand(RequestHandler *request_handler, std::string string) : rq(request_handler), StringShapeCommand(string) {
        argumentsMinimum = 2;
        argumentsMaximum = 2;
        commandDescription = "Creates new directory in current directory";
        argsNames.push_back("mkdir");
        argsNames.push_back("directoryname");
    }

    Response handle(){
        Response response;
        std::cout << std::endl << "I AM CREATING NEW DIRECTORY ON THE SERVER" << std::endl;
        return response;
    }
};

class CdCommand : public StringShapeCommand {
private:
    RequestHandler *rq;
public:
    CdCommand(RequestHandler *request_handler, std::string string) : rq(request_handler), StringShapeCommand(string) {
        argumentsMinimum = 2;
        argumentsMaximum = 2;
        commandDescription = "Changes directory";
        argsNames.push_back("cd");
        argsNames.push_back("directoryname or ..");
    }

    Response handle(){
        Response response;
        std::cout << std::endl << "I AM CHANGING CURRENT DIRECTORY ON THE SERVER" << std::endl;
        return response;
    }
};

class ListCommand : public StringShapeCommand {
private:
    RequestHandler *rq;
public:
    ListCommand(RequestHandler *request_handler, std::string string) : rq(request_handler), StringShapeCommand(string) {
        argumentsMinimum = 1;
        argumentsMaximum = 1;
        commandDescription = "Lists files and directories in current directory";
        argsNames.push_back("ls");
    }

    Response handle(){
        Response response;
        std::cout << std::endl << "I AM LISTING FILES IN CURRENT DIRECTORY" << std::endl;
        return response;
    }
};


#endif
