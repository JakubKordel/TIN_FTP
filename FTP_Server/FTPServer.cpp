#include "FTPServer.h"
#include "ServerPI.h"

#include "../NetFunctions/NetFunctions.h" // wrapped network function (definisions)


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

    struct sockaddr_in client;
    int msgsock;
    unsigned int cliaddrlen = sizeof(client);

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    BindSock(listenfd);
    Listen(listenfd, 5);

    // display ip address and port
    WriteOut();

    
    while(1){
        std::cout << "Listening ... \n";
        msgsock = Accept(listenfd, (struct sockaddr*) &client, &cliaddrlen);
        std::cout << "Client accepted\n";
        PassClientToServe(msgsock, client);

    }
    Close(listenfd);

    return 0;
}

void FTPServer::WriteOut(){
    // std::cout << "ip port" << ip_addr << std::endl;
    // std::cout << "port: " << port << std::endl;
    std::cout << "ip port\n" << ip_addr << " " << port << "\n";
}

int FTPServer::BindSock(int sock){
    struct sockaddr_in server;
    char *saddr = &ip_addr[0];

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
    SaveServAddress(server, sock);

    return 0;
}

void FTPServer::SaveServAddress(struct sockaddr_in &server, int sock){
    char servipstr[INET_ADDRSTRLEN];
    unsigned int length = sizeof(server);
    Getsockname( sock, (struct sockaddr *) &server, &length );
    Inet_ntop(AF_INET, &server.sin_addr, servipstr, sizeof(servipstr));
    ip_addr = std::string(servipstr);
    port = std::to_string(ntohs(server.sin_port));
}

void FTPServer::PassClientToServe(int msgsock, struct sockaddr_in &cliaddr){
    ServerPIArgs *args = new ServerPIArgs;
    // ServerPIArgs args;
    pthread_t tid;
    char cliaddrstr[INET_ADDRSTRLEN];
    Inet_ntop(AF_INET, &cliaddr.sin_addr, cliaddrstr, sizeof (cliaddr));

    // prepare arguments for ServerPI
    args->msgsock = msgsock;
    args->cliaddr = std::string(cliaddrstr);
    args->cliport = cliaddr.sin_port;

    int res = CreateThread(&tid, NULL, CreateServerPI, (void *)args);
    
    if(res>0) {
        std::cout << "Create thread error";
        // 
    }

    // Pthread_create(NULL, NULL, CreateServerPI, (void *)&args);
    // Pthread_join(tid, NULL);
}

void *CreateServerPI(void *arg){
// this function could be inside FTPServer class, but then FTPServer would be static 
    Pthread_detach(pthread_self()); // detach from the main thread

    ServerPIArgs *serv_args = static_cast<ServerPIArgs*> (arg);

    ServerPI server_PI = ServerPI(serv_args->msgsock, serv_args->cliport, serv_args->cliaddr);
    delete serv_args; // free unneeded memory
    server_PI.Start();

    return NULL;
}

int CreateThread(pthread_t *tid, pthread_attr_t *attr, void *(*func)(void *), void *arg){
    int res = pthread_create(tid, attr, func, (void *)arg);
 
    if(res>0){
        errno = res;
        perror("creating thread");
        exit(1); 
    }
    return res;
}