#include "RequestHandler.h"

void RequestHandler::Run(){
    while (!exit) {
        std::cout << "Wait for next command from client\n";
        Command * command = nextCommand();
        if (command == nullptr){
            // unknown command
            handleNoCommandFault();// sprawdzic czy zaimplementowane
        } else {
            if (command->isCorrect()){
                // command is correct
                command->handleCommand();
            } else {
                // command is wrong - i. e too many or too less arguments 
                command->handleFaultyCommand();
            }
            delete(command);
        }
    }
}