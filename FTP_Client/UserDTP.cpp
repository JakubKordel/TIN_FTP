#include "../NetFunctions/unp.h"

#include "UserDTP.h"

  UserDTP::UserDTP(){
    open = false;
    sockaddr_in my_addr;
    my_addr.sin_addr.s_addr = INADDR_ANY;
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(0);
    sock = socket( AF_INET, SOCK_STREAM, 0);
    if (sock == -1){
        perror("opening stream socket");
        exit(1);
        //instead of exit throw some exception
    }
    Bind(sock, (sockaddr *)&my_addr, sizeof my_addr);
  }

  int UserDTP::connectToServerDTPPort(std::string serverName, uint16_t serverPort){
    server.sin_family = AF_INET;
    hp = gethostbyname(serverName.c_str());
    if(hp == (struct hostent *) 0) {
        return -1;
    }
    memcpy((char *) &server.sin_addr, (char *) hp->h_addr, hp->h_length);
    server.sin_port = htons( serverPort );

    sleep(1);// wait in case server start listening after our connection try
    if(connect(sock, (struct sockaddr *) &server, sizeof server ) == -1 ){
        return -2;
    }
    open = true;
    return 0;
  }

  std::string UserDTP::run(int op, std::string data){
      std::string result;
      if (isOpen()){
        if(operation != DWNLOAD && operation != UPLOAD) {result = "Bad operation"; return result; }

        if(operation == DWNLOAD){// we have to recieve data from server
            ReceiveMsg(sock, result, PREFERRED_BUF_SIZE);
        }else{ //we have to send data to server
          SendMsg(sock, data);
          result = "0";
        }
      } else {

      }

      return result;
  }

  void UserDTP::closeConnection(){
      close(sock);
      open = false;
  }

  bool UserDTP::isOpen(){
    return open;
  }

  UserDTP::~UserDTP(){
    if (isOpen()){
      closeConnection();
    }
  }
