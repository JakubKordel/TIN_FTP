#include "RequestHandler.h"


void RequestHandler::Run(){
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