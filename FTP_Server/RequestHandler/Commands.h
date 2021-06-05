#ifndef _COMMANDS_H
#define _COMMANDS_H

#include <string>
#include <iostream>
#include <fstream>
#include "RequestHandler.h"
#include "helpStringsOperations.h"
#include "../Filesystem/FileSystem.h"
#include "../Database/AuthenticationDB.h"



class StringShapeCommand : public Command {
private:

    void splitArguments(){
        splitToWords(command, args);
    }

protected:

    std::string command;
    std::vector<std::string> args;

    unsigned int argumentsMinimum;
    unsigned int argumentsMaximum;
    std::string commandDescription;
    std::vector<std::string> argsNames;

public:

    // ~StringShapeCommand(){}
    StringShapeCommand(std::string str){
        command = str;
        splitArguments();
    }

    void printHelp(){
    //     std::cout << "Command: " << argsNames[0] << std::endl;
    //     std::vector<std::string>::iterator it = argsNames.begin();
    //     std::cout << "Usage: " << *it;
    //     ++it;
    // for (it ; it != argsNames.end(); ++it)
    //     std::cout << " [ " << *it << " ] ";
    //     std::cout << std::endl << commandDescription << std::endl;
    }

    bool isCorrect(){
        return (args.size() >= 2 && args[1] == "--help") || (args.size() >= argumentsMinimum && args.size() <= argumentsMaximum);
    }

    void handleFaultyCommand(){
        Response response;
        response.status_code = "xxx";
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
    LoginCommand(RequestHandler *request_handler, std::string string) : StringShapeCommand(string) {
        rq = request_handler;
        argumentsMinimum = 1;

        argumentsMaximum = 3;
        commandDescription = "Connects and logins user to the server";
        argsNames.push_back("login");
        argsNames.push_back("username");
        argsNames.push_back("password");
    }

    void handle(){
        Response response;
        std::string login;
        std::string password;

        if (args.size() == 1) {
          response.status_code = "3xx";
          response.msg_response = " Put your login: ";
          ((ServerPI*)rq)->SendResponse(response);
          login = ((ServerPI*)rq)->WaitForRequest();
          response.status_code = "3xx";
          response.msg_response = " Put your password: ";
          ((ServerPI*)rq)->SendResponse(response);
          password = ((ServerPI*)rq)->WaitForRequest();
        }
        else if (args.size() == 2) {
          response.status_code = "3xx";
          response.msg_response = " Put your password: ";
          ((ServerPI*)rq)->SendResponse(response);
          login = args[1];
          password = ((ServerPI*)rq)->WaitForRequest();
        }

        else if (args.size() == 3) {
          login = args[1];
          password = args[2];
        }

        AuthenticationDB auth;
        bool issuccess = auth.login(login, password);
        if( issuccess ){
            response.status_code = "2xx";
            response.msg_response = " OK, you have been logged in";
        }else{
            response.status_code = "2xx";
            response.msg_response = " Login error, wrong username or password";
        }

        // send response to client
        ((ServerPI*)rq)->SendResponse(response);
        std::cout << std::endl << "I HANDLED LOGIN COMMAND" << std::endl;
    }
};

// command: logout
class LogoutCommand : public StringShapeCommand {
private:
    RequestHandler *rq;
public:
    LogoutCommand(RequestHandler *request_handler, std::string string) : StringShapeCommand(string) {
        rq = request_handler;
        argumentsMinimum = 1;
        argumentsMaximum = 1;
        commandDescription = "Logouts and disconnects user from server";
        argsNames.push_back("logout");
    }

    void handle(){
        Response response;
        
        if(!rq->IsLogged()){
            // user is not logged in generate error
            response.status_code = "531";
            response.msg_response = "Logout error, you are not logged";
        }else{
            rq->ResetLogged();
            rq->SetUsername("");
            response.status_code = "231";
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
    UploadCommand(RequestHandler *request_handler, std::string string) : StringShapeCommand(string) {
        rq = request_handler;
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
            response.status_code = "531"; //u are LOGGED_OUT
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
    DownloadCommand(RequestHandler *request_handler, std::string string) : StringShapeCommand(string) {
        rq = request_handler;
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
    MkdirCommand(RequestHandler *request_handler, std::string string) : StringShapeCommand(string) {
        rq = request_handler;
        argumentsMinimum = 2;
        argumentsMaximum = 2;
        commandDescription = "Creates new directory in current directory";
        argsNames.push_back("mkdir");
        argsNames.push_back("directoryname");
    }

    void handle() {
        Response response;
        if (rq->IsLogged()) {
            response.status_code = "200"; // u are LOGGED_OUT
            response.msg_response = "Error creating directory, you have to be logged in to create directories";
        } else {
            int result = FileSystem::MakeDir(rq->GetCurrPath(), args.at(1));
            switch (result) {
                case 0:
                    response.status_code = "0";
                    response.msg_response = "OK, directory created successfully";
                    break;
                case 1:
                    response.status_code = "5";
                    response.msg_response = "Error creating directory, directory already exists";
                    break;
                case 2:
                    response.status_code = "6";
                    response.msg_response = "Error creating directory";
                    break;
            }
        }
        ((ServerPI *)rq)->SendResponse(response);
    }
};

class CdCommand : public StringShapeCommand {
private:
    RequestHandler* rq;
public:
    CdCommand(RequestHandler *request_handler, std::string string) : StringShapeCommand(string) {
        rq = request_handler;
        argumentsMinimum = 2;
        argumentsMaximum = 2;
        commandDescription = "Changes directory";
        argsNames.push_back("cd");
        argsNames.push_back("directoryname or ..");
    }

    void handle() {
        Response response;
        if (rq->IsLogged()) {
            response.status_code = "4"; // u are LOGGED_OUT
            response.msg_response = "Error creating directory, you have to be logged in to create directories";
        }
        else {
            std::string result = "";
            int code = FileSystem::ChangeDirectory(result, rq->GetRootPath(), rq->GetCurrPath(), args.at(1));
            switch (code) {
            case 0:
                rq->SetCurrPath(result);
                response.status_code = "0";
                response.msg_response = "OK, directory changed successfully";
                break;
            case -1:
                response.status_code = "7";
                response.msg_response = "Error changing directory, tried changing directory to above root";
                break;
            case -2:
                response.status_code = "8";
                response.msg_response = "Error changing directory, directory not found";
                break;
            }
        }
        ((ServerPI*)rq)->SendResponse(response);
        std::cout << std::endl << "I AM CHANGING CURRENT DIRECTORY ON THE SERVER" << std::endl;
    }
};

class ListCommand : public StringShapeCommand {
private:
    RequestHandler *rq;
public:
    ListCommand(RequestHandler *request_handler, std::string string) : StringShapeCommand(string) {
        rq = request_handler;
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
