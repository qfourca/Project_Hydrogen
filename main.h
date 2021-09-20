#include "SockClass.h"
#include <algorithm>
#include <queue>
#include <vector>
#include <ctime>

struct ThreadManagement
{
    ClientSock clientSock;
    std::thread readArray;
    std::mutex readThreadMutex;
};

ServerSock serverSock;
char recieveBuffer[BUFSIZ];
std::mutex socketQueue_mutex;
int arrayIndex;
bool speed;
struct ThreadManagement management[READTHREADSIZE];
std::thread sendThread[SENDTHREADSIZE]; //전송 쓰레드 선언
std::queue<ClientSock> clientWaitQueue;

void MainFunction();
void SendDataFunction();
void Input(int myAccessPoint);
int CommandReader();
