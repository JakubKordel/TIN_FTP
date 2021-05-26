CFLAGS=-Wall -pedantic -std=c++11 -g

FTP_Server: Server

Server: FTPServer main
	g++ obj/FTPServer.o obj/main.o -o Server

main:
	g++ -c main.cpp -o obj/main.o

FTPServer:
	g++ -c FTP_Server/FTPServer.cpp -o obj/FTPServer.o

clean:
	rm -f obj/*.o