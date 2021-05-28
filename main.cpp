#include <iostream>


#include "FTP_Server/FTPServer.h"

using namespace std;

int main(int argc, char **argv){

    FTPServer server;// = FTPServer();


    if( argc == 1 ){
        // run -> any address, any port
        server = FTPServer();
    }else if( argc == 2 ){
        // run -> any ip adress, port=argv[1]
        server = FTPServer(argv[1]);
    }else if( argc == 3 ){
        // run -> ip=argv[1] port=argv[2]
        server = FTPServer(argv[1], argv[2]);
    }

    server.Start();
    server.WriteOut();

    return 0;
}