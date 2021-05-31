CFLAGS=-Wall -pedantic -std=c++11 -g
AUTH_PATH=FTP_Server/Authentication/

FTP_Server: Server

Server: Auth_st_lib ReqHandler ServerPI ServerDTP FTPServer main
	g++ obj/FTPServer.o obj/main.o obj/ServerPI.o obj/ServerDTP.o obj/RequestHandler.o libs/Auth.a -o Server -lpthread

main:
	g++ -c main.cpp -o obj/main.o

FTPServer:
	g++ -c FTP_Server/FTPServer.cpp -o obj/FTPServer.o

ServerPI:
	g++ -c FTP_Server/ServerPI.cpp -o obj/ServerPI.o
	
ServerDTP:
	g++ -c FTP_Server/ServerDTP.cpp -o obj/ServerDTP.o

ReqHandler:
	g++ -c FTP_Server/RequestHandler/RequestHandler.cpp -o obj/RequestHandler.o



Auth_st_lib: Auth ReadCsv Userbase PassHashing sha1
	ar rvs libs/Auth.a obj/Authentication.o obj/readCsv.o obj/Userbase.o 

Auth:
	g++ -c $(AUTH_PATH)/Authentication.cpp -o obj/Authentication.o

ReadCsv:
	g++ -c $(AUTH_PATH)/readCsv.cpp -o obj/readCsv.o

Userbase:
	g++ -c $(AUTH_PATH)/Userbase.cpp -o obj/Userbase.o

PassHashing:
	g++ -c $(AUTH_PATH)/HashFunctions/passwordHashing.cpp -o obj/passwordHashing.o

sha1:
	g++ -c $(AUTH_PATH)/HashFunctions/sha1.cpp -o obj/sha1.o

clean:
	rm -f obj/*.o
