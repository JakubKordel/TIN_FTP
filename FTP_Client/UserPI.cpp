#include "../NetFunctions/NetFunctions.h"

#include "UserPI.h"

  UserPI::UserPI(){
    open = false;

  }


  // UserPI::UserPI(UserPI upi);

  void UserPI::createSocket(){
    sock = socket( AF_INET, SOCK_STREAM, 0);
    if (sock == -1){
        perror("opening stream socket");
        exit(1);
        //instead of exit throw some exception
    }
  }

  int UserPI::connectToServer(std::string serverName, int serverPort){
    createSocket();
    servName = serverName;

    server.sin_family = AF_INET;
    hp = gethostbyname(serverName.c_str());
    if(hp == (struct hostent *) 0) {
        return -1;
    }
    memcpy((char *) &server.sin_addr, (char *) hp->h_addr, hp->h_length);
    server.sin_port = htons( serverPort );

    if(connect(sock, (struct sockaddr *) &server, sizeof server ) == -1 ){
        return -2;
    }

    open = true;
    return 0;
  }

  void UserPI::closeConnection(){
      close(sock);
      open = false;
  }


  int UserPI::sendMsgToServer(std::string msg){
    if (open){
      return SendMsg(sock, msg);
    } else {
      return -1;
    }
  }

  std::string UserPI::waitForServerResponse(){
    std::string response;
    ReceiveMsg(sock, response);
    if(response.empty()){
      std::cout << "Lost ftp server connection\n";
    }
    return response;
  }

  bool UserPI::isOpen(){
    return open;
  }

  UserPI::~UserPI(){
    /*if (isOpen()){
      closeConnection();
    }*/
  }

  std::string UserPI::getServerName(){
    return servName;
  }
