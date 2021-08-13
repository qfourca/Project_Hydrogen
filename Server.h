#include "SockClass.h"
#include <algorithm>
#include <queue>
#include <vector>

extern ServerSock serverSock;
extern ClientSock clientSock;
extern char recieveBuffer[BUFSIZ];
extern std::mutex socketQueue_mutex;
extern int arrayIndex;
extern bool speed;
extern struct ThreadManagement management[READTHREADSIZE];
extern std::thread sendThread[SENDTHREADSIZE]; //전송 쓰레드 선언

void MainFunction();
void SendDataFunction();
void Input(int myAccessPoint);
int CommandReader();

struct ThreadManagement
{
    ClientSock clientSock;
    std::thread readArray;
    std::mutex readThreadMutex;
};
