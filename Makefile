cc=gcc
pp=g++

main = Main

all :
	g++ -c Sock.cpp SockClass.h
	g++ -c Data.cpp DataClass.h
	g++ -o Server Main.cpp Sock.o Data.o -pthread
	rm -rf *.o
	rm -rf *.gch

clean :
	rm -rf *.o   
	rm -rf *.gch
