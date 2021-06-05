#ifndef _COMMANDS_H
#define _COMMANDS_H

#include <string>
#include <iostream>
#include <fstream>
#include "CommandHandler.h"
#include "helpStringsOperations.h"
#include "../UserPI.h"

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
		std::cout << std::endl << "ERROR: Bad argumets" << std::endl;
		printHelp();
	}

  void handleCommand(){
      if ( args.size() >= 2 && args[1] == "--help")
      printHelp();
        else
      handle();
  }

  virtual void handle() = 0;
};

class ConnectCommand : public StringShapeCommand {
  UserPI upi;
public:
	ConnectCommand(std::string string, UserPI & userPI) : StringShapeCommand(string), upi(userPI) {
			argumentsMinimum = 3;
			argumentsMaximum = 3;
			commandDescription = "Connects user to the server";
      argsNames.push_back("connect");
			argsNames.push_back("server adress");
      argsNames.push_back("port");
	}

	void handle(){
		//std::cout << std::endl << "I AM HANDLING CONNECT COMMAND" << std::endl;

    upi.connectToServer(args[1], atoi(args[2].c_str()));
	}
};

class LoginCommand : public StringShapeCommand {
  UserPI &upi;
public:
	LoginCommand(std::string string, UserPI &userPI) : StringShapeCommand(string), upi(userPI){
      // upi = userPI;
			argumentsMinimum = 1;
			argumentsMaximum = 3;
			commandDescription = "Logins user to the server";
			argsNames.push_back("login");
      argsNames.push_back("username");
			argsNames.push_back("password");

	}

	void handle(){

    std::cout << "Login handle\n";
    std::string response;
    std::string msg;
    bool commandHandlingFinished = false;
    upi.sendMsgToServer(command);
    while (!commandHandlingFinished){
      response = upi.waitForServerResponse();
      std::cout << response << std::endl;
      if (response[0] == '1'){

      } else if (response[0] == '2') {
        commandHandlingFinished = true;
      } else if (response[0] == '3'){
        getline(std::cin, msg);
        upi.sendMsgToServer(msg);
      } else if (response[0] == '4'){
          commandHandlingFinished = true;
      } else if (response[0] == '5'){
          commandHandlingFinished = true;
      }
    }

	}
};

class LogoutCommand : public StringShapeCommand {
  UserPI upi;
public:
	LogoutCommand(std::string string, UserPI & userPI) : StringShapeCommand(string), upi(userPI) {
			argumentsMinimum = 1;
			argumentsMaximum = 1;
			commandDescription = "Logouts user from server";
			argsNames.push_back("logout");
	}

	void handle(){
    std::string response;
    std::string msg;
    bool commandHandlingFinished = false;
    upi.sendMsgToServer(command);
    while (!commandHandlingFinished){
      response = upi.waitForServerResponse();
      std::cout << response << std::endl;
      if (response[0] == '1'){

      } else if (response[0] == '2') {
        commandHandlingFinished = true;
      } else if (response[0] == '3'){
        getline(std::cin, msg);
        upi.sendMsgToServer(msg);
      } else if (response[0] == '4'){
          commandHandlingFinished = true;
      } else if (response[0] == '5'){
          commandHandlingFinished = true;
      }
    }
	}
};

  class UploadCommand : public StringShapeCommand {
    UserPI upi;
  public:
  	UploadCommand(std::string string, UserPI & userPI) : StringShapeCommand(string), upi(userPI) {
  			argumentsMinimum = 2;
  			argumentsMaximum = 2;
  			commandDescription = "Uploads file to the server";
  			argsNames.push_back("upload");
        argsNames.push_back("file");
  	}

  	void handle(){
      std::string response;
      std::string msg;
      bool commandHandlingFinished = false;
      upi.sendMsgToServer(command);
      while (!commandHandlingFinished){
        response = upi.waitForServerResponse();
        std::cout << response << std::endl;
        if (response[0] == '1'){

        } else if (response[0] == '2') {
          commandHandlingFinished = true;
        } else if (response[0] == '3'){
          getline(std::cin, msg);
          upi.sendMsgToServer(msg);
        } else if (response[0] == '4'){
            commandHandlingFinished = true;
        } else if (response[0] == '5'){
            commandHandlingFinished = true;
        }
      }

  	}
  };

  class DownloadCommand : public StringShapeCommand {
    UserPI upi;
  public:
    DownloadCommand(std::string string, UserPI & userPI) : StringShapeCommand(string), upi(userPI) {
        argumentsMinimum = 2;
        argumentsMaximum = 2;
        commandDescription = "Downloads file from the server";
        argsNames.push_back("download");
        argsNames.push_back("file");
    }

    void handle(){
      std::string response;
      std::string msg;
      bool commandHandlingFinished = false;
      upi.sendMsgToServer(command);
      while (!commandHandlingFinished){
        response = upi.waitForServerResponse();
        std::cout << response << std::endl;
        if (response[0] == '1'){

        } else if (response[0] == '2') {
          commandHandlingFinished = true;
        } else if (response[0] == '3'){
          getline(std::cin, msg);
          upi.sendMsgToServer(msg);
        } else if (response[0] == '4'){
            commandHandlingFinished = true;
        } else if (response[0] == '5'){
            commandHandlingFinished = true;
        }
      }


    }
  };

  class MkdirCommand : public StringShapeCommand {
    UserPI upi;
  public:
    MkdirCommand(std::string string, UserPI & userPI) : StringShapeCommand(string), upi(userPI) {
        argumentsMinimum = 2;
        argumentsMaximum = 2;
        commandDescription = "Creates new directory in current directory";
        argsNames.push_back("mkdir");
        argsNames.push_back("directoryname");
    }

    void handle(){
      std::string response;
      std::string msg;
      bool commandHandlingFinished = false;
      upi.sendMsgToServer(command);
      while (!commandHandlingFinished){
        response = upi.waitForServerResponse();
        std::cout << response << std::endl;
        if (response[0] == '1'){

        } else if (response[0] == '2') {
          commandHandlingFinished = true;
        } else if (response[0] == '3'){
          getline(std::cin, msg);
          upi.sendMsgToServer(msg);
        } else if (response[0] == '4'){
            commandHandlingFinished = true;
        } else if (response[0] == '5'){
            commandHandlingFinished = true;
        }
      }

    }
  };

  class CdCommand : public StringShapeCommand {
    UserPI upi;
  public:
    CdCommand(std::string string, UserPI & userPI) : StringShapeCommand(string), upi(userPI) {
        argumentsMinimum = 2;
        argumentsMaximum = 2;
        commandDescription = "Changes directory";
        argsNames.push_back("cd");
        argsNames.push_back("directoryname or ..");
    }

    void handle(){
      std::string response;
      std::string msg;
      bool commandHandlingFinished = false;
      upi.sendMsgToServer(command);
      while (!commandHandlingFinished){
        response = upi.waitForServerResponse();
        std::cout << response << std::endl;
        if (response[0] == '1'){

        } else if (response[0] == '2') {
          commandHandlingFinished = true;
        } else if (response[0] == '3'){
          getline(std::cin, msg);
          upi.sendMsgToServer(msg);
        } else if (response[0] == '4'){
            commandHandlingFinished = true;
        } else if (response[0] == '5'){
            commandHandlingFinished = true;
        }
      }
    }
  };

  class ListCommand : public StringShapeCommand {
    UserPI upi;
  public:
    ListCommand(std::string string, UserPI & userPI) : StringShapeCommand(string), upi(userPI) {
        argumentsMinimum = 1;
        argumentsMaximum = 1;
        commandDescription = "Lists files and directories in current directory";
        argsNames.push_back("ls");
    }

    void handle(){
      std::string response;
      std::string msg;
      bool commandHandlingFinished = false;
      upi.sendMsgToServer(command);
      while (!commandHandlingFinished){
        response = upi.waitForServerResponse();
        std::cout << response << std::endl;
        if (response[0] == '1'){

        } else if (response[0] == '2') {
          commandHandlingFinished = true;
        } else if (response[0] == '3'){
          getline(std::cin, msg);
          upi.sendMsgToServer(msg);
        } else if (response[0] == '4'){
            commandHandlingFinished = true;
        } else if (response[0] == '5'){
            commandHandlingFinished = true;
        }
      }
    }
  };




#endif
