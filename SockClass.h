#include "InterpreterDefine.h"
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
#include <algorithm>
#include <mutex>
#define PORT 80
#define MYIP "192.168.35.149"

class Sock
{
protected:
    Sock();
    sockaddr_in thisSocketAdress;
    unsigned int adressLen = sizeof(thisSocketAdress);

public:
    int thisSocket; //소켓 번호
};

class ClientSock : public Sock
{
private:
    int whereIsSlash();

public:
    char recivedData[BUFSIZ]; //임시로 데이터를 저장할 곳

    ClientSock();

    int AcceptConnection(int serverSocket); //서버연결
    sockaddr *ReturnSockAdressP();
    void AcceptSocket(int serverSocket);     //소켓 연결
    int SendFile(const char *fileName);      //파일전송
    int PutInRecivedData(const char *input); //파일 입력
    int Interpreter();
};

class ServerSock : public Sock
{

private:
public:
    ServerSock();
};
