#include "ServerDTP.h"

#include <iostream>

std::string ServerDTP::Run(){
    std::string result;
    if(operation != DWNLOAD && operation != UPLOAD) {result = "Bad operation"; return result; }

    struct sockaddr_in client;
    int datasock;
    unsigned int cliaddrlen = sizeof(client);

    Listen(listensock, 1);
    // it could be implemented better with timing
    std::cout << "ServerDTP\t Listening ... \n";
    datasock = Accept(listensock, (struct sockaddr*) &client, &cliaddrlen);

    if(operation == DWNLOAD){// we have to send data to client
        SendMsg(datasock, data);
        result = "0";
    }else{// uploading file - we have to read data from client
        ReceiveMsg(datasock, result, PREFERRED_BUF_SIZE);
    }

    return result;
}

bool ServerDTP::VerifyClient(sockaddr_in client){
    char client_s[INET_ADDRSTRLEN];
    Inet_ntop(AF_INET, &client.sin_addr, client_s, sizeof(client));
    return client_addr.compare(client_s);
}
