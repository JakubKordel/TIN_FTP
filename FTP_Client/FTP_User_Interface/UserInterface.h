#ifndef _USERINTERFACE_H
#define _USERINTERFACE_H

#include "CommandHandler.h"
#include "../UserPI.h"

class UserInterface : public CommandHandler {
protected:
  UserPI userPI;

  void handleNoCommandFault();

public:

  void printHelp();

  Command * getCommand(std::string str);

  Command * nextCommand();

};

class HelpCommand : public Command {

private:
UserInterface * ui;

public:

  HelpCommand(UserInterface * userInterface);

  bool isCorrect();

  void handleFaultyCommand();

  void handleCommand();
};

#endif
