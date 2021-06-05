#pragma once

#include <string>
#include "../NetFunctions/unp.h"

class ServerDTP{

    int listensock;
    int operation;  //
    std::string client_addr;
    std::string data;

public:
    ServerDTP(int sock, int op, std::string cli_addr){
        listensock = sock;
        operation = op;
        client_addr = client_addr;
    }

    ServerDTP(int sock, int op, std::string cli_addr, std::string data_to_send): ServerDTP(sock, op, cli_addr){
        data = data_to_send;
    }

    std::string Run();

    const int DWNLOAD = 3;
    const int UPLOAD = 2;

private:
    bool VerifyClient(sockaddr_in client);

    const int PREFERRED_BUF_SIZE = 400;

};
