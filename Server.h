#include "SockClass.h"
#include "Customio.h"
#define PORT 80
#define MYIP "192.168.35.149"

extern ServerSock serverSock;
extern ClientSock clientSock;
extern char sendBuffer[BUFSIZ];
extern char recieveBuffer[BUFSIZ];

void tempFunction();
int SendMessage(int socket);
int CommandReader();
