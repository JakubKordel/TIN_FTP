#ifndef _COMMANDHANDLER_H
#define _COMMANDHANDLER_H

#include <string>
#include <iostream>
#include <fstream>

class Command {
public:
  virtual void handleCommand() = 0;
  virtual bool isCorrect() = 0;
  virtual void handleFaultyCommand() = 0;
};

class CommandHandler{
protected:
  virtual void handleNoCommandFault() = 0;
private:
  bool exit = false;
public:
  void run(){
      while (!exit) {
          Command * command = nextCommand();
          if (command == nullptr){
            handleNoCommandFault();
          } else {
            if (command ->isCorrect()){
              command ->handleCommand();
            } else {
              command ->handleFaultyCommand();
            }
            delete(command);
          }
      }
  }

  virtual Command * nextCommand() = 0;

  friend class ExitCommand;

};

class ExitCommand : public Command {

private:
CommandHandler * ch;

protected:
  void stopCommandHandler(){
      ch->exit = true;
  }

public:

  ExitCommand(CommandHandler * commandHandler) : ch(commandHandler){}

  bool isCorrect(){
    return true;
  }

  void handleFaultyCommand(){}

  void handleCommand(){
    stopCommandHandler();
  }
};

#endif
