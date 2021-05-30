#include "ServerPI.h"


ServerPI::ServerPI(int msgsock, int cliport, std::string cliaddr){
    msgsocket = msgsock;
    client_port = cliport;
    client_addr = cliaddr;
}

int ServerPI::Run(){
    // 
    // char buffer[200];
    Greeting(); // welcome the client

    std::cout << "Serving client " << client_addr << ":" << client_port << std::endl;
    
    ServiceProvider serv_provider = ServiceProvider();

    while(1){
        // we serve client until he send end of connection
        std::string request = WaitForRequest();
        // check client command
        serv_provider.ProvideService(request);
        std::cout << request << std::endl;

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