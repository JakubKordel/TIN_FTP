#ifndef _COMMANDS_H
#define _COMMANDS_H

#include <string>
#include <iostream>
#include <fstream>
#include "CommandHandler.h"
#include "helpStringsOperations.h"
#include <arpa/inet.h>
#include "../UserPI.h"
#include "../UserDTP.h"
#include "../Filesystem/FileSystem.h"

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

  StringShapeCommand(std::string str){
    command = str;
    splitArguments();
  }

  void printHelp(){
    std::cout << "Command: " << argsNames[0] << std::endl;
    std::vector<std::string>::iterator it = argsNames.begin();
    std::cout << "Usage: " << *it;
    ++it;
    for ( ; it != argsNames.end(); ++it)
        std::cout << " [ " << *it << " ] ";
    std::cout << std::endl << commandDescription << std::endl;
  }

	bool isCorrect(){
		return (args.size() >= 2 && args[1] == "--help") || (args.size() >= argumentsMinimum && args.size() <= argumentsMaximum);
	}

	void handleFaultyCommand(){
		std::cout << std::endl << "ERROR: Bad arguments" << std::endl;
		printHelp();
	}

  void handleCommand(){
      if (args.size() >= 2 && args[1] == "--help")
      printHelp();
        else
      handle();
  }

  virtual void handle() = 0;
};

class ConnectCommand : public StringShapeCommand {
  UserPI & upi;
public:
	ConnectCommand(std::string string, UserPI & userPI) : StringShapeCommand(string), upi(userPI) {
			argumentsMinimum = 3;
			argumentsMaximum = 3;
			commandDescription = "Connects user to the server";
      argsNames.push_back("connect");
			argsNames.push_back("server address");
      argsNames.push_back("port");
	}

	void handle(){
		//std::cout << std::endl << "I AM HANDLING CONNECT COMMAND" << std::endl;
    if(upi.connectToServer(args[1], atoi(args[2].c_str())) != 0) {std::cout << "Connection error - server not found or doesnt accept your connection"; }
    std::string welcome_msg = upi.waitForServerResponse();
    std::cout << welcome_msg << "\n";
  }

  void handleFaultyCommand(){
		std::cout << std::endl << "ERROR: you have to close current connection" << std::endl;
		printHelp();
	}
  
  bool isCorrect(){
		return !upi.isOpen() && ((args.size() >= 2 && args[1] == "--help") || (args.size() >= argumentsMinimum && args.size() <= argumentsMaximum));
	}

};

class DisconnectCommand : public StringShapeCommand {
  UserPI & upi;
public:
  DisconnectCommand(std::string string, UserPI & userPI) : StringShapeCommand(string), upi(userPI) {
			argumentsMinimum = 1;
			argumentsMaximum = 1;
			commandDescription = "Close connection with server";
      argsNames.push_back("close");
	}

  void handle(){
    std::string cmd = "exit";
    upi.sendMsgToServer(cmd);
    upi.closeConnection();
  }

  void handleFaultyCommand(){
    if(!upi.isOpen()){
      std::cout << "ERROR: you have to be connected to close connection";
    }else{
      std::cout << "ERROR: Bad arguments";
      printHelp();
    }
  }

  bool isCorrect(){
    return upi.isOpen() && ((args.size() >= 2 && args[1] == "--help") || (args.size() >= argumentsMinimum && args.size() <= argumentsMaximum));
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

  bool isCorrect(){
    return ((args.size() >= 2 && args[1] == "--help") || (args.size() >= argumentsMinimum && args.size() <= argumentsMaximum)) && upi.isOpen();
  }

  void handleFaultyCommand(){
    if (!((args.size() >= 2 && args[1] == "--help") || (args.size() >= argumentsMinimum && args.size() <= argumentsMaximum))){
      std::cout << std::endl << "ERROR: Bad arguments" << std::endl;
      printHelp();
    }
    else if (!upi.isOpen()){
      std::cout << std::endl << "ERROR: You have to connect to server first" << std::endl;
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

  bool isCorrect(){
    return ((args.size() >= 2 && args[1] == "--help") || (args.size() >= argumentsMinimum && args.size() <= argumentsMaximum)) && upi.isOpen();
  }

  void handleFaultyCommand(){
    if (!((args.size() >= 2 && args[1] == "--help") || (args.size() >= argumentsMinimum && args.size() <= argumentsMaximum))){
      std::cout << std::endl << "ERROR: Bad arguments" << std::endl;
      printHelp();
    }
    else if (!upi.isOpen()){
      std::cout << std::endl << "ERROR: You have to connect to server first" << std::endl;
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
  			argsNames.push_back("put");
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
          if (response[1] == '5' && response[2] == '0' ) {
            UserDTP userDTP;
            std::string file;
            FileSystem::GetFile(file, args[1]);
            int serverPort = std::stoi(response.substr(4));
            userDTP.connectToServerDTPPort(upi.getServerName(), serverPort);
            // userDTP.run(UserDTP:: ,file);
            userDTP.sendData(file);
            userDTP.closeConnection();
          }
          else {
            getline(std::cin, msg) ;
            upi.sendMsgToServer(msg);
          }
        } else if (response[0] == '4'){
            commandHandlingFinished = true;
        } else if (response[0] == '5'){
            commandHandlingFinished = true;
        }
      }
  	}

    bool isCorrect(){
      return ((args.size() >= 2 && args[1] == "--help") || (args.size() >= argumentsMinimum && args.size() <= argumentsMaximum)) && upi.isOpen();
    }

    void handleFaultyCommand(){
      if (!((args.size() >= 2 && args[1] == "--help") || (args.size() >= argumentsMinimum && args.size() <= argumentsMaximum))){
        std::cout << std::endl << "ERROR: Bad arguments" << std::endl;
        printHelp();
      }
      else if (!upi.isOpen()){
        std::cout << std::endl << "ERROR: You have to connect to server first" << std::endl;
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
        argsNames.push_back("get");
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
          if (response[1] == '5' && response[2] == '1' ) {
            UserDTP userDTP;
            uint16_t serverPort = static_cast<uint16_t>(std::stoi(response.substr(4)));
            std::cout << serverPort << "\n";
            int resConn = userDTP.connectToServerDTPPort(upi.getServerName(), serverPort);
            std::cout << resConn << "\n";
            std::string file = userDTP.getData();
            int saveRes = FileSystem::SaveFile(args.at(1), file);
            if( saveRes != 0) std::cout << "Saving error\n";
            userDTP.closeConnection();
          }
          else {
            getline(std::cin, msg) ;
            upi.sendMsgToServer(msg);
          }
        } else if (response[0] == '4'){
            commandHandlingFinished = true;
        } else if (response[0] == '5'){
            commandHandlingFinished = true;
        }
      }
    }

    bool isCorrect(){
      return ((args.size() >= 2 && args[1] == "--help") || (args.size() >= argumentsMinimum && args.size() <= argumentsMaximum)) && upi.isOpen();
    }

    void handleFaultyCommand(){
      if (!((args.size() >= 2 && args[1] == "--help") || (args.size() >= argumentsMinimum && args.size() <= argumentsMaximum))){
        std::cout << std::endl << "ERROR: Bad arguments" << std::endl;
        printHelp();
      }
      else if (!upi.isOpen()){
        std::cout << std::endl << "ERROR: You have to connect to server first" << std::endl;
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
        argsNames.push_back("mkd");
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

    bool isCorrect(){
      return ((args.size() >= 2 && args[1] == "--help") || (args.size() >= argumentsMinimum && args.size() <= argumentsMaximum)) && upi.isOpen();
    }

    void handleFaultyCommand(){
      if (!((args.size() >= 2 && args[1] == "--help") || (args.size() >= argumentsMinimum && args.size() <= argumentsMaximum))){
        std::cout << std::endl << "ERROR: Bad arguments" << std::endl;
        printHelp();
      }
      else if (!upi.isOpen()){
        std::cout << std::endl << "ERROR: You have to connect to server first" << std::endl;
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
          getline(std::cin, msg) ;
          upi.sendMsgToServer(msg);
        } else if (response[0] == '4'){
            commandHandlingFinished = true;
        } else if (response[0] == '5'){
            commandHandlingFinished = true;
        }
      }
    }

    bool isCorrect(){
      return ((args.size() >= 2 && args[1] == "--help") || (args.size() >= argumentsMinimum && args.size() <= argumentsMaximum)) && upi.isOpen();
    }

    void handleFaultyCommand(){
      if (!((args.size() >= 2 && args[1] == "--help") || (args.size() >= argumentsMinimum && args.size() <= argumentsMaximum))){
        std::cout << std::endl << "ERROR: Bad arguments" << std::endl;
        printHelp();
      }
      else if (!upi.isOpen()){
        std::cout << std::endl << "ERROR: You have to connect to server first" << std::endl;
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
          getline(std::cin, msg) ;
          upi.sendMsgToServer(msg);
        } else if (response[0] == '4'){
            commandHandlingFinished = true;
        } else if (response[0] == '5'){
            commandHandlingFinished = true;
        }
      }
    }

    bool isCorrect(){
      return ((args.size() >= 2 && args[1] == "--help") || (args.size() >= argumentsMinimum && args.size() <= argumentsMaximum)) && upi.isOpen();
    }

    void handleFaultyCommand(){
      if (!((args.size() >= 2 && args[1] == "--help") || (args.size() >= argumentsMinimum && args.size() <= argumentsMaximum))){
        std::cout << std::endl << "ERROR: Bad arguments" << std::endl;
        printHelp();
      }
      else if (!upi.isOpen()){
        std::cout << std::endl << "ERROR: You have to connect to server first" << std::endl;
      }
    }
  };




#endif
