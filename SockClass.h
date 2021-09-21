#include "DataClass.h"
#include "Defines/Defines.h"
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

//시간 관련 def
#define ALLOFTIME 0
#define SEC 1
#define MIN 2
#define HOUR 3
#define DAY 4

int retTime(int);
void printl(const char *);
void printl(const char *, bool);

class Sock //소켓 클래스 기본적인 소켓정보들이 들어 있다
{
protected:
    Sock();
    sockaddr_in _sock_adress;       //소켓 주소
    static unsigned int _adressLen; //주소의 길이

public:
    int _sock_descriptor; //소켓 디스크럽터
};

class ClientSock : public Sock
{
private:
    char *searchString(const char *string); //legacy

public:
    Data _data;

    ClientSock();

    int acceptConnection(int);    //서버 연결 매개변수1:서버의 소켓 반환값:0
    void acceptSocket(int);       //소켓 연결 매개변수1:서버의 소켓
    int sendFile(const char *);   //파일 전송 매개변수1:파일의 이름
                                  //         반환값:전송이 성공적으로 이루어 졌을 경우 보낸 파일의 크기(단위:byte) 실패시 -1
    int sendString(const char *); //문자열 전송 매개변수1:보낼 문자열
                                  //           반환값:전송이 성공적으로 이루어 졌을 경우 보낸 문자열의 크기(단위:byte) 실패시 -1
    int sendDataAuto();
};

class ServerSock : public Sock //서버 클래스
{
private:
public:
    ServerSock(); //포트를 바인딩 하고 직접적으로 서버를 여는 생성자
};
