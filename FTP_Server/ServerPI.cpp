#include "ServerPI.h"

// #include "../NetFunctions/NetFunctions.h"

ServerPI::ServerPI(int msgsock, int cliport, std::string cliaddr){
    msgsocket = msgsock;
    client_port = cliport;
    client_addr = cliaddr;
}

int ServerPI::Run(){
    char buffer[200];
    // 
    std::cout << "Waiting for data from " << client_addr << ":" << client_port << std::endl;
    int datalength = Recv(msgsocket, buffer, sizeof(buffer), 0);

    std::cout << buffer <<std::endl;


    Close(msgsocket);
    return 0;
}


// void ServeClient(void *arg);