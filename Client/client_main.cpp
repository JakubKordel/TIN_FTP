#define THREADS_FREE

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>


#include "../NetFunctions/NetFunctions.h"


#define DATA "Half a league, half a league . . . "

int main(int argc, char *argv[])
{
    int sock;
    struct sockaddr_in server;
    struct hostent *hp;
    // const char *message = "Poczatek wiadomosci, Hello world , Hey Hi Hello "
        // "To juz druga linia tej wiadomosci. Ciekawe jaki przekaz bedzie tej informacji "
        // "Zdaje sie, ze ostatnio za malo czytasz, bo brakuje ci slow do wyslania w dziwnej "
        // "testowej wiadomosci. Nie poddawaj sie tylko probuj nowa tresc wiadomosci, co by sie nic nie "
        // "powtorzylo. Na razie calkiem niezle ci idzie. Do dziala. Dalej, dalej. Dobrze jest miec natchnienie "
        // "To nie jest wcale takie proste\0";
    const char *message = "get file.txt\0";
       

    /* Create socket */
    sock = socket( AF_INET, SOCK_STREAM, 0);
    if (sock == -1){
        perror("opening stream socket");
        exit(1);
    }

    /* uzyskajmy adres IP z nazwy */
    server.sin_family = AF_INET;
    hp = gethostbyname(argv[1]);
    // inet_pton(AF_INET, argv[1], &server.sin_addr);
    /* hostbyname zwraca strukture zawierajaca adres danego hosta */
    if(hp == (struct hostent *) 0) {
        fprintf(stderr, "%s: unknow host\n", argv[1]);
        exit(2);
    }
    memcpy((char *) &server.sin_addr, (char *) hp->h_addr, hp->h_length);
    server.sin_port = htons(atoi( argv[2] ));

    std::cout << "Cos\n";

    if(connect(sock, (struct sockaddr *) &server, sizeof server ) == -1 ){
        perror("connecting stream socket");
        exit(1);
    }
    int a = 1;
    // while(a!=0){

        int nread = 1;
        std::string rcvmsg;
        
        // std::cout << message << std::endl;
        
        
        char buff[10];

        std::cout << "Czytanie danych\n";
        ReceiveMsg(sock, rcvmsg, 20);
        // std::cin >> a;
        SendMsg(sock, std::string(message));
        // do{
        //     nread = read(sock, buff, sizeof(buff));
        //     if(nread>0){
        //         std::cout << "Petla\n";
        //         rcvmsg.append(buff);
        //     }else if(nread == 0){
        //         std::cout << "End\n";
        //         //end
        //     }else{
        //         std::cout << "Error reading\n";
        //     }
        // }while(buff[nread-1] != '\0');
        std::cout << rcvmsg <<"\n";

        std::cin>>a;
        // if( write(sock, message, strlen(message)+1) == -1 )
        //     perror("writing on stream socket");
        
        std::string msgtosend(message);
        // SendMsg(sock, msgtosend);

    // }
    close(sock);
    exit(0);

    return 0;
}