cc=gcc
pp=g++

main = Main

all :
	g++ -c  Sock.cpp SockClass.h
	g++ -c  Server.cpp Server.h
	g++ -c Data.cpp DataClass.h
	g++ -o  Server Main.cpp Sock.o Server.o Data.o -pthread
	rm -rf *.o
	rm -rf *.gch

clean :
	rm -rf *.o   
	rm -rf *.gch
