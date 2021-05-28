#ifndef _NETFUNCTIONS_H
#define _NETFUNCTIONS_H

#include "unp.h"
#include <iostream>

// wrapped network functions 


int Socket(int family, int type, int protocol){
    int sockfd = socket(family, type, protocol);
    if( sockfd == -1 ){
        perror("opening stream socket");
        exit(1);
    }
    return sockfd;
}

int Bind(int sock, struct sockaddr * saddr, socklen_t addrlen){
    if( bind(sock, (struct sockaddr*)saddr, addrlen) == -1){
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

int Accept(int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen){
    int result = accept(sockfd, (struct sockaddr *)cliaddr, (socklen_t *)addrlen);
    if( result == -1 ){
        perror("accept");
        exit(1);
    }
    return result;
}

int Close(int fd){
    int result = close(fd);
    if(result<0){
        perror("close");
        exit(1);
    }
    return 0;
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

int Getsockname(int sock, struct sockaddr *addr, socklen_t *length){
    if( getsockname(sock, (struct sockaddr *) addr, length) == -1 ){
        perror("getting socket name");
        exit(1);
    }
    return 0;
}

// Pthread_create() have to know function which is passed to it as argument 

int Pthread_detach(pthread_t tid){
    int res = pthread_detach(tid);
    if(res>0){
        errno = res;
        perror("creating thread");
        exit(1); 
    }
    return res;
}

int Pthread_join(pthread_t tid, void **status){
    int res = pthread_join(tid, status);
    if(res>0){
        errno = res;
        perror("creating thread");
        exit(1); 
    }
    return res;
}


ssize_t Recv(int sockfd, void *buff, size_t nbytes, int flags){
    int result = recv(sockfd, buff, nbytes, flags);
    if(result<0){
        // blad czytania
    }
    return result;
}

#endif
