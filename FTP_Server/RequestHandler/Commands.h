#ifndef _COMMANDS_H
#define _COMMANDS_H

#include <string>
#include <iostream>
#include <fstream>
#include "RequestHandler.h"
#include "helpStringsOperations.h"
#include "../Filesystem/FileSystem.h"
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

    void handleFaultyCommand(){
        Response response;
        response.err_code = 1;
        response.msg_response = "Too many / less arguments\n"
                                "See help for more information";
        std::cout << std::endl << "ERROR: Bad argumets" << std::endl;
        printHelp();
    }

    void handleCommand(){
        if (args[1] == "--help")
            printHelp();
        else
            return handle();
    }


    virtual void handle() = 0;
};

// command: login [username] [password]
class LoginCommand : public StringShapeCommand {
private:
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

    void handle(){
        Response response;
        std::cout << std::endl << "I AM HANDLING LOGIN COMMAND" << std::endl;

        Authentication auth;
        bool issuccess = auth.login(args.at(1), args.at(2));
        if( issuccess ){
            response.err_code = 230;    // success - logged 
            response.msg_response = "OK, you have been logged in";
        }else{
            response.err_code = 530;    // wrong login or password
            response.msg_response = "Login error, wrong username or password";
        }

        // send response to client 
        ((ServerPI*)rq)->SendResponse(response);

    }
};

// command: logout
class LogoutCommand : public StringShapeCommand {
private:
    RequestHandler *rq;
public:
    LogoutCommand(RequestHandler *request_handler, std::string string) : rq(request_handler), StringShapeCommand(string) {
        argumentsMinimum = 1;
        argumentsMaximum = 1;
        commandDescription = "Logouts and disconnects user from server";
        argsNames.push_back("logout");
    }

    void handle(){
        Response response;
        
        if(!rq->IsLogged()){
            // user is not logged in generate error
            response.err_code = 531;
            response.msg_response = "Logout error, you are not logged";
        }else{
            rq->ResetLogged();
            rq->SetUsername("");
            response.err_code = 231;
            response.msg_response = "OK, you have been logged out";
        }

        ((ServerPI *)rq)->SendResponse(response);
        std::cout << std::endl << "I AM HANDLING LOGOUT COMMAND" << std::endl;
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

    void handle(){
        Response response;
        std::cout << std::endl << "I AM UPLOADING FILE TO THE SERVER" << std::endl;
        
        if( rq->IsLogged() ){
            response.err_code = 531; //u are LOGGED_OUT
            response.msg_response = "Error uploading, you have to be logged in to upload files";
        }else{
            std::string data = rq->getData();
            // ServerPI got from the ServerDTP data to save on disc
            std::string full_path = rq->GetCurrPath();
            full_path.append(args.at(1));// concat current path and the filename
            FileSystem::SaveFile(full_path, data);
            // send response

        }
        
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

    void handle(){
        Response response;
        std::cout << std::endl << "I AM DOWNLOADING FILE FROM THE SERVER" << std::endl;
        
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

    void handle(){
        Response response;
        std::cout << std::endl << "I AM CREATING NEW DIRECTORY ON THE SERVER" << std::endl;
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

    void handle(){
        Response response;
        std::cout << std::endl << "I AM CHANGING CURRENT DIRECTORY ON THE SERVER" << std::endl;
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

    void handle(){
        Response response;
        std::cout << std::endl << "I AM LISTING FILES IN CURRENT DIRECTORY" << std::endl;
    }
};


#endif
