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
  if (commandName == "upload") command = new UploadCommand(str, userPI) ; else
  if (commandName == "download") command = new DownloadCommand(str, userPI) ; else
  if (commandName == "mkdir") command = new MkdirCommand(str, userPI) ; else
  if (commandName == "cd") command = new CdCommand(str, userPI); else
  if (commandName == "ls") command = new ListCommand(str, userPI);
  return command;
}



void UserInterface::printHelp(){
  std::cout << "List of available commands: " << std::endl;

  std::cout << "login \t\t\t logout \t\t upload \ndownload \t\t mkdir \t\t\t cd \nls \t\t\t help \t\t\t exit";

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
