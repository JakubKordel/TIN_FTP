#include "ServerPI.h"
#include "RequestHandler/helpStringsOperations.h"
#include "RequestHandler/Commands.h"
#include "ServerDTP.h"


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

    Run();

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

int ServerPI::SendResponse(Response resp){
    std::string msg;
    msg.append(resp.status_code);
    msg.append(resp.msg_response);
    SendMsg(msgsocket, msg);

    return 0;
}

Command* ServerPI::nextCommand() {
    std::string req = WaitForRequest();
    std::string comm_name = getFirstWord(req);

    Command *command = nullptr;

    if (comm_name == "help") {command = new HelpCommand(this) ; curr_operation = 1;} else // pomyslec, czy potrzebny
    if (comm_name == "put") {command = new UploadCommand(this, req) ; curr_operation = 2;} else
    if (comm_name == "get") {command = new DownloadCommand(this, req) ; curr_operation = 3;} else
    if (comm_name == "ls") {command = new ListCommand(this, req); curr_operation = 4;} else
    if (comm_name == "login") {command = new LoginCommand(this, req) ; curr_operation = 5; } else
    if (comm_name == "logout") {command = new LogoutCommand(this, req) ; curr_operation = 6;} else
    if (comm_name == "exit") {command = new ExitCommand(this) ; curr_operation = 7; } else
    if (comm_name == "mkd") {command = new MkdirCommand(this, req) ; curr_operation = 8;} else
    if (comm_name == "cd") {command = new CdCommand(this, req); curr_operation = 9;}
    return command;
}

void ServerPI::handleNoCommandFault() {
    // unknown command - send error to client
    std::cout << "Handle no command fault\n";
    std::string msg = "Unknown command";


}

std::string ServerPI::getData(){
    int datasock = 0;
    int port;
    std::string data;

    datasock = Socket(AF_INET, SOCK_STREAM, 0);
    port = bindServerDTP(datasock);

    if(port>0){
        SendDTPPort(port);
        ServerDTP dtp = ServerDTP(datasock, curr_operation, client_addr);
        data = dtp.Run();
    }else{
        // error
    }

    return data;
}

int ServerPI::SendDTPPort(int port){
    Response resp;
    resp.status_code = "xxx";
    resp.msg_response = " DTP_port 22 \nPlease connect to DTP_port";

    SendResponse(resp);
    return 0;
}

int ServerPI::bindServerDTP(int sock){
    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(0);

    Bind(sock, (struct sockaddr *) &server, sizeof(server) );

    return DTP_PORT;
}

void ServerPI::returnResponse(Response resp){
    SendResponse(resp);
}

void ServerPI::PrintHelp(){
    std::cout << "List of available commands: " << std::endl;

    std::cout << "help \t\t\t put \t\t get \nls \t\t login \t\t\t logout \ncd \t\t\t mkd \t\t\t exit";

    std::cout << "\n\nType"<< std::endl << "[Command Name] --help " << std::endl << "for more information about command";
}

HelpCommand::HelpCommand(ServerPI * server_pi) : spi(server_pi){}

bool HelpCommand::isCorrect(){
    return true;
}

void HelpCommand::handleFaultyCommand(){
    // std::string err_msg =

}

void HelpCommand::handleCommand(){
    spi->PrintHelp();
}
