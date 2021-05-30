#include "ServerPI.h"
#include "../RequestHandler/helpStringsOperations.h"
#include "../RequestHandler/Commands.h"

ServerPI::ServerPI(int msgsock, int cliport, std::string cliaddr){
    msgsocket = msgsock;
    client_port = cliport;
    client_addr = cliaddr;
}

int ServerPI::Start(){
    // 
    // char buffer[200];
    Greeting(); // welcome the client

    std::cout << "Serving client " << client_addr << ":" << client_port << std::endl;
    
    
    while(1){
        // we serve client until he send end of connection
        // check client command
        Run();

    }

    // 

// obsluz 
    // wyslij odpowiedz
    // 


    Close(msgsocket);
    return 0;
}

std::string ServerPI::WaitForRequest(){
    std::string request;
    ReceiveMsg(msgsocket, request);
    return request;
}

void ServerPI::Greeting(){
    std::cout << "Greeting start\n";
    SendMsg(msgsocket, welcome_msg);
    std::cout << "Greeting end\n";
}

void ServerPI::handleNoCommandFault() {
    std::cout << "Handle no command fault\n";
}

Command* ServerPI::nextCommand() {
    std::string req = WaitForRequest();
    std::string comm_name = getFirstWord(req);

    Command *command = nullptr;

    if (comm_name == "exit") command = new ExitCommand(this) ; else
    if (comm_name == "help") command = new HelpCommand(this) ; else
    if (comm_name == "login") command = new LoginCommand(req) ; else
    if (comm_name == "logout") command = new LogoutCommand(req) ; else
    if (comm_name == "upload") command = new UploadCommand(req) ; else
    if (comm_name == "download") command = new DownloadCommand(req) ; else
    if (comm_name == "mkdir") command = new MkdirCommand(req) ; else
    if (comm_name == "cd") command = new CdCommand(req); else
    if (comm_name == "ls") command = new ListCommand(req);
    return command;
}


void ServerPI::PrintHelp(){
    std::cout << "List of available commands: " << std::endl;

    std::cout << "login \t\t\t logout \t\t upload \ndownload \t\t mkdir \t\t\t cd \nls \t\t\t help \t\t\t exit";

    std::cout << "\n\nType"<< std::endl << "[Command Name] --help " << std::endl << "for more information about command";
}



HelpCommand::HelpCommand(ServerPI * server_pi) : spi(server_pi){}

bool HelpCommand::isCorrect(){
    return true;
}

void HelpCommand::handleFaultyCommand(){}

void HelpCommand::handleCommand(){
    spi ->PrintHelp();
}
