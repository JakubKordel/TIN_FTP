#include "FTPServer.h"

#include "NetFunctions.h" // wrapped network function

FTPServer::FTPServer(){
    // 
    ip_addr = "0";
    port = "0";
}

FTPServer::FTPServer(char *nport){
    // 
    std::string tport(nport);
    port = tport;
    ip_addr = "0";
}

FTPServer::FTPServer(char *nip_addr, char *nport){
    // 
    std::string tip_addr(nip_addr);
    std::string tport(nport);

    ip_addr = tip_addr;
    port = tport;
}




int FTPServer::Start(){

    struct sockaddr_in client, server;
    int msgsock;
    
    //
    socklen_t clientlen = sizeof(client);
    char buf[INET_ADDRSTRLEN];

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    BindSock(listenfd);
    Listen(listenfd, 5);

    // display ip address and port
    WriteOut();
    

    msgsock = Accept(listenfd, (struct sockaddr*) &client, &clientlen);

    Inet_ntop(AF_INET, &client.sin_addr, buf, sizeof(buf));

    std::cout << "Client ip: " << buf << std::endl;

    char msg[1024];
    read(msgsock, msg, 200);
    // std::cout << msg;

    Close(msgsock);

    Close(listenfd);

    return 0;
}

void FTPServer::WriteOut(){
    std::cout << "ip: " << ip_addr << std::endl;
    std::cout << "port: " << port << std::endl;
}

int FTPServer::BindSock(int sock){
    struct sockaddr_in server;
    char *saddr = &ip_addr[0];
    char servipstr[INET_ADDRSTRLEN];

    server.sin_family = AF_INET;
    if( ip_addr.compare("0") == 0 ){
        server.sin_addr.s_addr = INADDR_ANY;
    }
    else{
        Inet_pton(AF_INET, saddr, &server.sin_addr);
    }
    if( port.compare("0") == 0 ){
        server.sin_port = 0;
    }else{
        server.sin_port = htons(std::stoi(port));
    }

    Bind(sock, (struct sockaddr *) &server, sizeof (server));

    // assign to ip_addr and port current server's values
    unsigned int length = sizeof(server);
    Getsockname( sock, (struct sockaddr *) &server, &length );
    Inet_ntop(AF_INET, &server.sin_addr, servipstr, sizeof(servipstr));
    ip_addr = std::string(servipstr);
    port = std::to_string(ntohs(server.sin_port));

    return 0;
}