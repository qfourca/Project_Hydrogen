#include "DataClass.h"
#include "Defines.h"
#include <algorithm>
#include <arpa/inet.h>
#include <fcntl.h>
#include <future>
#include <iostream>
#include <memory.h>
#include <mutex>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <string>
#include <sys/sendfile.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <thread>
#include <unistd.h>
#define PORT 80
#define MYIP "192.168.35.149"

class Sock
{
protected:
    Sock();
    sockaddr_in thisSocketAdress;
    unsigned int adressLen = sizeof(thisSocketAdress);

public:
    int thisSocket; //소켓 디스크럽터
};

class ClientSock : public Sock
{
private:
    int whereIsSlash();
    int skipSpace(char *string, int startPoint);
    int skipSpace(int startPoint);
    int returnFileName(char *fileName);
    char *searchString(const char *string);

public:
    static int folderSize;
    bool keep_conection;
    //char recivedData[BUFSIZ]; //임시로 데이터를 저장할 곳
    Data recivedData;

    ClientSock();

    int AcceptConnection(int serverSocket); //서버연결
    sockaddr *ReturnSockAdressP();
    void AcceptSocket(int serverSocket); //소켓 연결
    int SendFile(const char *fileName);  //파일전송
    int SendData(const char *);
    int Interpreter();
};

class ServerSock : public Sock
{
private:
public:
    ServerSock();
};
