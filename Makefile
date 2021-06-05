CFLAGS=-Wall -pedantic -std=c++17 -g
DB_PATH=FTP_Server/Database
FSYSTEM_PATH=FTP_Server/Filesystem


	

FTP_Server: Server

# jesli <filesystem> obslugiwany
#Server: obj DB ReqHandler ServerPI ServerDTP FTPServer main Filesystem
#	g++ obj/FTPServer.o obj/main.o obj/ServerPI.o obj/ServerDTP.o obj/RequestHandler.o obj/FileSystem.o  obj/AuthenticationDB.o obj/readCsv.o obj/Database.o obj/passwordHashing.o obj/sha1.o -o Server -lpthread

# it needs dirs for object files and static library files
obj:
	mkdir obj

# jesli <filesystem> nieobslugiwany
Server: obj DB ReqHandler ServerPI ServerDTP FTPServer main Filesystem
	g++ obj/FTPServer.o obj/main.o obj/ServerPI.o obj/ServerDTP.o obj/RequestHandler.o obj/FileSystem.o  obj/AuthenticationDB.o obj/readCsv.o obj/Database.o obj/passwordHashing.o obj/sha1.o obj/ChecksumDB.o -o Server -lpthread -lstdc++fs


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



DB: Auth ReadCsv Database PassHashing sha1 Checksum
	

Auth:
	g++ -c $(CFLAGS) $(DB_PATH)/AuthenticationDB.cpp -o obj/AuthenticationDB.o


Checksum:
	g++ -c $(CFLAGS) $(DB_PATH)/ChecksumDB.cpp -o obj/ChecksumDB.o

ReadCsv:
	g++ -c $(CFLAGS) $(DB_PATH)/readCsv.cpp -o obj/readCsv.o

Database:
	g++ -c $(CFLAGS) $(DB_PATH)/Database.cpp -o obj/Database.o

PassHashing:
	g++ -c $(CFLAGS) $(DB_PATH)/HashFunctions/passwordHashing.cpp -o obj/passwordHashing.o

sha1:
	g++ -c $(CFLAGS) $(DB_PATH)/HashFunctions/sha1.cpp -o obj/sha1.o


Filesystem: 
	g++ -c $(CFLAGS) $(FSYSTEM_PATH)/FileSystem.cpp -o obj/FileSystem.o
	

# jesli <filesystem> nieobslugiwany
mainUI:
	g++ FTP_Client/FTP_User_Interface/mainUI.cpp FTP_Client/FTP_User_Interface/CommandHandler.h FTP_Client/FTP_User_Interface/UserInterface.h FTP_Client/FTP_User_Interface/UserInterface.cpp FTP_Client/FTP_User_Interface/helpStringsOperations.cpp FTP_Client/FTP_User_Interface/helpStringsOperations.h FTP_Client/FTP_User_Interface/Commands.h NetFunctions/NetFunctions.h FTP_Client/UserDTP.h FTP_Client/UserDTP.cpp FTP_Client/UserPI.h FTP_Client/UserPI.cpp FTP_Client/Filesystem/FileSystem.h FTP_Client/Filesystem/FileSystem.cpp -lpthread -o ftp_ui -lstdc++fs


# jesli <filesystem> obslugiwany
#mainUI:
#	g++ FTP_Client/FTP_User_Interface/mainUI.cpp FTP_Client/FTP_User_Interface/CommandHandler.h FTP_Client/FTP_User_Interface/UserInterface.h FTP_Client/FTP_User_Interface/UserInterface.cpp FTP_Client/FTP_User_Interface/helpStringsOperations.cpp FTP_Client/FTP_User_Interface/helpStringsOperations.h FTP_Client/FTP_User_Interface/Commands.h NetFunctions/NetFunctions.h FTP_Client/UserDTP.h FTP_Client/UserDTP.cpp FTP_Client/UserPI.h FTP_Client/UserPI.cpp FTP_Client/Filesystem/FileSystem.h FTP_Client/Filesystem/FileSystem.cpp -lpthread -o ftp_ui


clean:
	rm -r obj
