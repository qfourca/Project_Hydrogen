#include "SockClass.h"
#include <algorithm>
#include <ctime>
#include <queue>
#include <vector>

#define LOGFOLDER "logs/"

struct ThreadManagement
{
    ClientSock clientSock;
    std::thread readArray;
    std::mutex readThreadMutex;
};

int delayTime = 1; //딜레이 시간
ServerSock serverSock;
char recieveBuffer[BUFSIZ];
std::mutex socketQueue_mutex;
int arrayIndex;
struct ThreadManagement management[READTHREADSIZE];
std::thread sendThread[SENDTHREADSIZE]; //전송 쓰레드 선언
std::queue<ClientSock> clientWaitQueue;

void MainFunction();
void SendDataFunction();
void Input(int myAccessPoint);
int CommandReader();

void printl(const char *);
