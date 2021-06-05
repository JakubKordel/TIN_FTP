#ifndef _USERPI_H
#define _USERPI_H

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

class UserPI {
  int sock;
  struct sockaddr_in server;
  struct hostent *hp;
  std::string servName;

  bool open;

  public:

  UserPI();
  // UserPI(UserPI upi);

  ~UserPI();

  int connectToServer(std::string serverName, int serverPort);

  void closeConnection();

  int sendMsgToServer(std::string msg);

  std::string waitForServerResponse();

  bool isOpen();

  std::string getServerName();

};

#endif
