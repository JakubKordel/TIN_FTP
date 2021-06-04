CFLAGS=-Wall -pedantic -std=c++17 -g
AUTH_PATH=FTP_Server/Authentication
FSYSTEM_PATH=FTP_Server/Filesystem

FTP_Server: Server

Server: Auth_st_lib ReqHandler ServerPI ServerDTP FTPServer main Filesystem
	g++ obj/FTPServer.o obj/main.o obj/ServerPI.o obj/ServerDTP.o obj/RequestHandler.o obj/FileSystem.o libs/Auth.a -o Server -lpthread -lstdc++fs

main:
	g++ -c $(CFLAGS) -lstdc++fs main.cpp -lstdc++fs -o obj/main.o 

FTPServer:
	g++ -c $(CFLAGS) FTP_Server/FTPServer.cpp -o obj/FTPServer.o 

ServerPI:
	g++ -c $(CFLAGS) FTP_Server/ServerPI.cpp -o obj/ServerPI.o
	
ServerDTP:
	g++ -c $(CFLAGS) FTP_Server/ServerDTP.cpp -o obj/ServerDTP.o

ReqHandler:
	g++ -c $(CFLAGS) FTP_Server/RequestHandler/RequestHandler.cpp -o obj/RequestHandler.o



Auth_st_lib: Auth ReadCsv Database PassHashing sha1
	ar rvs libs/Auth.a obj/Authentication.o obj/readCsv.o obj/Database.o 

Auth:
	g++ -c $(CFLAGS) $(AUTH_PATH)/Authentication.cpp -o obj/Authentication.o

ReadCsv:
	g++ -c $(CFLAGS) $(AUTH_PATH)/readCsv.cpp -o obj/readCsv.o

Database:
	g++ -c $(CFLAGS) $(AUTH_PATH)/Database.cpp -o obj/Database.o

PassHashing:
	g++ -c $(CFLAGS) $(AUTH_PATH)/HashFunctions/passwordHashing.cpp -o obj/passwordHashing.o

sha1:
	g++ -c $(CFLAGS) $(AUTH_PATH)/HashFunctions/sha1.cpp -lstdc++fs -o obj/sha1.o

Filesystem: 
	g++ -c $(CFLAGS) $(FSYSTEM_PATH)/FileSystem.cpp -o obj/FileSystem.o

mainUI:
	g++ -lpthread FTP_Client/FTP_User_Interface/mainUI.cpp FTP_Client/FTP_User_Interface/CommandHandler.h FTP_Client/FTP_User_Interface/UserInterface.h FTP_Client/FTP_User_Interface/UserInterface.cpp FTP_Client/FTP_User_Interface/helpStringsOperations.cpp FTP_Client/FTP_User_Interface/helpStringsOperations.h FTP_Client/FTP_User_Interface/Commands.h NetFunctions/NetFunctions.h FTP_Client/UserDTP.h FTP_Client/UserPI.h FTP_Client/UserPI.cpp -o ftp_ui



clean:
	rm -f obj/*.o libs/*.a
