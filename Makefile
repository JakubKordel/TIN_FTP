CFLAGS=-Wall -pedantic -std=c++11 -g

FTP_Server: Server

Server: ServiceProvider ServerPI FTPServer main
	g++ obj/FTPServer.o obj/main.o obj/ServerPI.o obj/ServiceProvider.o -o Server -lpthread

main:
	g++ -c main.cpp -o obj/main.o

FTPServer:
	g++ -c FTP_Server/FTPServer.cpp -o obj/FTPServer.o

ServerPI:
	g++ -c FTP_Server/ServerPI.cpp -o obj/ServerPI.o
	
ServiceProvider:
	g++ -c FTP_Server/ServiceProvider.cpp -o obj/ServiceProvider.o

clean:
	rm -f obj/*.o
