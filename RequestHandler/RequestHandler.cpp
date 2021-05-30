#include "RequestHandler.h"


void RequestHandler::Run(){
    Response response;
    while (!exit) {
        Command * command = nextCommand();
        if (command == nullptr){
            handleNoCommandFault();
        } else {
            if (command->isCorrect()){
                response = command->handleCommand();
            } else {
                response = command->handleFaultyCommand();
            }
            delete(command);
            // returnResponse(response);
            
            exit = 1;
        }
    }
}