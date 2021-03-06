#include <string>
#include <iostream>
#include <fstream>
#include "helpStringsOperations.h"
#include "UserInterface.h"
#include "Commands.h"


void UserInterface::handleNoCommandFault(){
  std::cout << std::endl <<"ERROR: There is no such a command" << std::endl;
  printHelp();
}

Command * UserInterface::getCommand(std::string str){


  std::string commandName = getFirstWord(str);
  std::cout << str << "\n";
  Command * command = nullptr;

  if (commandName == "exit") command = new ExitCommand(this) ; else
  if (commandName == "help") command = new HelpCommand(this) ; else
  if (commandName == "connect") command = new ConnectCommand(str, userPI) ; else
  if (commandName == "login") command = new LoginCommand(str, userPI) ; else
  if (commandName == "logout") command = new LogoutCommand(str, userPI) ; else
  if (commandName == "put") command = new UploadCommand(str, userPI) ; else
  if (commandName == "get") command = new DownloadCommand(str, userPI) ; else
  if (commandName == "mkd") command = new MkdirCommand(str, userPI) ; else
  if (commandName == "cd") command = new CdCommand(str, userPI); else
  if (commandName == "ls") command = new ListCommand(str, userPI); else
  if (commandName == "close" ) command = new DisconnectCommand(str, userPI);
  return command;
}



void UserInterface::printHelp(){
  std::cout << "List of available commands: " << std::endl;

  std::cout << "connect, login, logout, put, get, mkd, cd, ls, help, exit, close";

  std::cout << "\n\nType"<< std::endl << "[Command Name] --help " << std::endl << "for more information about command";
}

Command * UserInterface::nextCommand(){
  std::string str;
  std::cout << std::endl << "$: ";
  getline(std::cin, str) ;
  Command * command = getCommand(str);
  return command;
}



HelpCommand::HelpCommand(UserInterface * userInterface) : ui(userInterface){}

bool HelpCommand::isCorrect(){
  return true;
}

void HelpCommand::handleFaultyCommand(){}

void HelpCommand::handleCommand(){
  ui ->printHelp();
}
