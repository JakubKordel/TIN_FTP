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





ssize_t Recv(int sockfd, void *buff, size_t nbytes, int flags){
    int result = recv(sockfd, buff, nbytes, flags);
    if(result<0){
        // reading error
        perror("receiving data");
    }
    return result;
}

ssize_t Read(int sockfd, void *buff, size_t nbytes){
    int result = read(sockfd, buff, nbytes);
    if(result<0){
        // reading error
        perror("reading data");
    }
    return result;
}

ssize_t Send(int sockfd, const void *buff, size_t nbytes, int flags){
    int result = send(sockfd, buff,  nbytes, flags);
    if( result < 0 ){
        perror("sending data");
        // exit(1);
    }
    return result;
}

int SendMsg(int msgsocket, std::string msg){

    char *message;
    msg.push_back('\0'); // adding character which means end of msg
    message = &msg[0];
    int msglength = msg.length()+1; // send byte 0 - end of message
    int curr_pos = 0, to_send = msglength;
    while(curr_pos<msglength){
        int nsent = Send(msgsocket, message+curr_pos, to_send, 0);
        if( nsent>0 ){
            curr_pos += nsent;
            to_send -= nsent;
        }else if( nsent == 0 ){
            // entire message has been sent
            // curr_pos = msg.length() + 1;
            
        }else{
            // error
            return -1;
        }

    }
    return 0;
}

/* read() and recv() works a bit different!:
 * read() passes as result msg[] and put after last byte character '\0'
 * meanwhile recv() dont do this
*/
int ReceiveMsg(int msgsocket, std::string &msg, int rcvbuf_size, int flags ){

    char msg_buf[rcvbuf_size+1]; // last byte for '\0'
    // msg_buf[rcvbuf_size-1] = 
    msg.clear();
    int ndata;
    do{
        ndata = Recv(msgsocket, msg_buf, rcvbuf_size, flags);
        msg_buf[ndata] = '\0';
        if(ndata>0){
            msg.append(msg_buf);
        }
    }while(msg_buf[ndata-1] != '\0');// we read entire message (until get char which means that msg ends)

    return 0;
}


int ReadMsg(int msgsocket, std::string &msg, int rcvbuf_size){
    char msg_buf[rcvbuf_size];
    // msg_buf[rcvbuf_size-1] = 
    msg.clear();
    int ndata;
    do{
        ndata = Read(msgsocket, msg_buf, sizeof(msg_buf));
        std::cout << msg_buf <<std::endl;
        if(ndata>0){
            msg.append(msg_buf);
        }
    }while(msg_buf[ndata-1] != '\0');// we read entire message (until get char which means that msg ends)

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

#endif
