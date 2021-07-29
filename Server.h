#include "SockClass.h"
#include <queue>
#define PORT 80
#define MYIP "192.168.35.149"

extern ServerSock serverSock;
extern ClientSock clientSock;
extern char sendBuffer[BUFSIZ];
extern char recieveBuffer[BUFSIZ];

void MainFunction();
void SendDataFunction();
int ReadData();

int SendMessage(int socket);
int CommandReader();
