#include "SockClass.h"
#include <queue>
#include <vector>
#include <algorithm>

#define SLEEPTIME 1
#define PORT 80
#define MYIP "192.168.35.149"
#define READTHREADSIZE 4
#define SENDTHREADSIZE 1

extern ServerSock serverSock;
extern ClientSock clientSock;
extern char sendBuffer[BUFSIZ];
extern char recieveBuffer[BUFSIZ];
extern std::mutex socketQueueMutex;
extern int arrayIndex;
extern bool speed;
extern struct ReadThreadManagement management[READTHREADSIZE];

struct ReadThreadManagement
{
    ClientSock clientSock;
    std::thread readArray;
    std::mutex readThreadMutex;
};

void MainFunction();
void SendDataFunction();
int ReadData();
void Input(int myAccessPoint);
int SendMessage(ClientSock clientSock);
int CommandReader();
