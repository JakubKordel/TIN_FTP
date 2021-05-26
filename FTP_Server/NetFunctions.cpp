#include "unp.h"

int Socket(int family, int type, int protocol){
    int sockfd = socket(family, type, protocol);
    if( sockfd == -1 ){
        perror("opening stream socket");
        exit(1);
    }
    return sockfd;
}

int Bind(int sock, struct sockaddr * saddr, socklen_t addrlen){
    if( bind(sock, (struct sockaddr*)saddr, addrlen)) == -1){
        perror("binding stream socket");
        exit(1);
    }
    return 0;
}

int Listen(int sockfd, int backlog){
    if( listen(sockfd, backlog) == -1 ){
        perror("listen function");
        exit(1);
    }
    return 0;
}

int Accept(int sockfd, struct *cliaddr, socklen_t *addrlen){
    int result = accept(sockfd, (struct sockaddr *)cliaddr, (unsigned int *)addrlen);
    if( result == -1 ){
        perror("accept");
        exit(1);
    }
    return result;
}

int Inet_pton(int family, const char *strptr, void *addrptr){
    int res = inet_pton(family, strptr, addrptr);
    if( res == -1 ){
        perror("inet_pton error");
        exit(1);
    }else if ( res == 0 ){
        perror("incorect presentation format");
        exit(1);
    }
    return res;
}

const char *Inet_ntop(int family, const void *addrptr, char *strptr, size_t len){
    const char *result = inet_ntop(family, addrptr, strptr, len);
    if( inet_ntop == NULL ){
        perror("inet_ntop function");
        exit(1);
    }
    return result;
}