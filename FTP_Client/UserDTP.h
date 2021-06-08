#ifndef _USERDTP_H
#define _USERDTP_H

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

class UserDTP{
  
  int sock;
  struct sockaddr_in server;
  struct hostent *hp;

  bool open;

  public:

  UserDTP();

  ~UserDTP();

  int connectToServerDTPPort(std::string serverName, uint16_t serverPort);

  void closeConnection();

  // std::string run(int operation, std::string data);

  void sendData(std::string data);
  
  std::string getData();

  bool isOpen();

  static const int DWNLOAD = 3;
  static const int UPLOAD = 2;

  const int PREFERRED_BUF_SIZE = 400;

};

#endif
