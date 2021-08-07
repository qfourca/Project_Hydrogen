#include "SockClass.h"
#include <queue>
#include <vector>
#include <algorithm>

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
extern ClientSock clientSockWithReadThread[READTHREADSIZE];
extern std::thread readArray[READTHREADSIZE];
extern std::mutex readThreadMutex[READTHREADSIZE];
extern bool speed;

void MainFunction();
void SendDataFunction();
int ReadData();
void Input(int myAccessPoint);
int SendMessage(ClientSock clientSock);
int CommandReader();
