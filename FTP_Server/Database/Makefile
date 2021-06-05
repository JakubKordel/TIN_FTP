# start:
# 	g++ main.cpp Database.cpp readCsv.cpp ChecksumDB.cpp -o checksum
# 	g++ mainA.cpp Database.cpp readCsv.cpp HashFunctions/passwordHashing.cpp HashFunctions/sha1.cpp Authentication.cpp -o auth

start: main Auth Checks DB readCsv pass sha1
	g++ obj/main.o obj/AuthenticationDB.o obj/ChecksumDB.o obj/Database.o obj/readCsv.o obj/passwordHashing.o obj/sha1.o -o auth

main:
	g++ -c mainA.cpp -o obj/main.o

# Authlib: Auth Checks DB readCsv pass sha1
# 	ar rvs obj/Auth.a obj/Authentication.o obj/ChecksumDB.o obj/readCsv.o obj/passwordHashing.o obj/sha1.o

Auth:
	g++ -c AuthenticationDB.cpp -o obj/AuthenticationDB.o

Checks:
	g++ -c ChecksumDB.cpp -o obj/ChecksumDB.o

DB:
	g++ -c Database.cpp -o obj/Database.o

readCsv:
	g++ -c readCsv.cpp -o obj/readCsv.o

pass:
	g++ -c HashFunctions/passwordHashing.cpp -o obj/passwordHashing.o

sha1:
	g++ -c HashFunctions/sha1.cpp -o obj/sha1.o