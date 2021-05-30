#ifndef _UNP_H
#define _UNP_H

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>


#include <string>

const int RECV_BUF_SIZE = 200;

int Socket(int family, int type, int protocol);
int Bind(int sock, struct sockaddr * saddr, socklen_t addrlen);
int Listen(int sockfd, int backlog);
int Accept(int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen);
int Close(int fd);
int Inet_pton(int family, const char *strptr, void *addrptr);
const char *Inet_ntop(int family, const void *addrptr, char *strptr, size_t len);
int Getsockname(int sock, struct sockaddr *addr, socklen_t *length);
ssize_t Recv(int sockfd, void *buff, size_t nbytes, int flags);
ssize_t Read( int sockfd, void *buff, size_t nbytes);
ssize_t Send(int sockfd, const void *buf, size_t nbytes, int flags);
int SendMsg(int msgsocket, std::string msg);
int ReceiveMsg(int msgsocket, std::string &msg, int rcvbuf_size = RECV_BUF_SIZE, int flags = 0);
int ReadMsg(int msgsocket, std::string &msg, int rcvbuf_size = RECV_BUF_SIZE);


int Pthread_detach(pthread_t tid);
int Pthread_join(pthread_t tid, void **status);



#endif
