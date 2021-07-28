#include <stdio.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <memory.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/tcp.h>
#include <thread>
#include <string>
#include <future>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <sys/types.h>
#define PORT 80
#define MYIP "192.168.35.149"

class Sock
{
protected:
    sockaddr_in thisSocketAdress;
    unsigned int adressLen = sizeof(thisSocketAdress);

public:
    int thisSocket;
    void SockAdressClear();
    void SocketDefine();
};

class ClientSock : public Sock
{
public:
    int AcceptConnection(int serverSocket);
    sockaddr *ReturnSockAdressP();
    void AcceptSocket(int serverSocket);
    int SendFile(const char *fileName);
};

class ServerSock : public Sock
{
private:
public:
    int BindAndListenSocketInPort(unsigned int portNum);
};
