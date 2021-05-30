#ifndef _COMMANDS_H
#define _COMMANDS_H

#include <string>
#include <iostream>
#include <fstream>
#include "RequestHandler.h"
#include "helpStringsOperations.h"

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
      if (args[1] == "--help")
      printHelp();
        else
      handle();
  }

  virtual void handle() = 0;
};

class LoginCommand : public StringShapeCommand {
public:
	LoginCommand(std::string string) : StringShapeCommand(string) {
			argumentsMinimum = 4;
			argumentsMaximum = 4;
			commandDescription = "Connects and logins user to the server";
			argsNames.push_back("login");
      argsNames.push_back("username");
			argsNames.push_back("password");
			argsNames.push_back("serveradress");
	}

	void handle(){
		std::cout << std::endl << "I AM HANDLING LOGIN COMMAND" << std::endl;
	}
};

class LogoutCommand : public StringShapeCommand {
public:
	LogoutCommand(std::string string) : StringShapeCommand(string) {
			argumentsMinimum = 1;
			argumentsMaximum = 1;
			commandDescription = "Logouts and disconnects user from server";
			argsNames.push_back("logout");
	}

	void handle(){
		std::cout << std::endl << "I AM HANDLING LOGOUT COMMAND" << std::endl;
	}
};

  class UploadCommand : public StringShapeCommand {
  public:
  	UploadCommand(std::string string) : StringShapeCommand(string) {
  			argumentsMinimum = 2;
  			argumentsMaximum = 2;
  			commandDescription = "Uploads file to the server";
  			argsNames.push_back("upload");
        argsNames.push_back("file");
  	}

  	void handle(){
  		std::cout << std::endl << "I AM UPLOADING FILE TO THE SERVER" << std::endl;
  	}
  };

  class DownloadCommand : public StringShapeCommand {
  public:
    DownloadCommand(std::string string) : StringShapeCommand(string) {
        argumentsMinimum = 2;
        argumentsMaximum = 2;
        commandDescription = "Downloads file from the server";
        argsNames.push_back("download");
        argsNames.push_back("file");
    }

    void handle(){
      std::cout << std::endl << "I AM DOWNLOADING FILE FROM THE SERVER" << std::endl;
    }
  };

  class MkdirCommand : public StringShapeCommand {
  public:
    MkdirCommand(std::string string) : StringShapeCommand(string) {
        argumentsMinimum = 2;
        argumentsMaximum = 2;
        commandDescription = "Creates new directory in current directory";
        argsNames.push_back("mkdir");
        argsNames.push_back("directoryname");
    }

    void handle(){
      std::cout << std::endl << "I AM CREATING NEW DIRECTORY ON THE SERVER" << std::endl;
    }
  };

  class CdCommand : public StringShapeCommand {
  public:
    CdCommand(std::string string) : StringShapeCommand(string) {
        argumentsMinimum = 2;
        argumentsMaximum = 2;
        commandDescription = "Changes directory";
        argsNames.push_back("cd");
        argsNames.push_back("directoryname or ..");
    }

    void handle(){
      std::cout << std::endl << "I AM CHANGING CURRENT DIRECTORY ON THE SERVER" << std::endl;
    }
  };

  class ListCommand : public StringShapeCommand {
  public:
    ListCommand(std::string string) : StringShapeCommand(string) {
        argumentsMinimum = 1;
        argumentsMaximum = 1;
        commandDescription = "Lists files and directories in current directory";
        argsNames.push_back("ls");
    }

    void handle(){
      std::cout << std::endl << "I AM LISTING FILES IN CURRENT DIRECTORY" << std::endl;
    }
  };




#endif
