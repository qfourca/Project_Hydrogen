#include "Server.h"

ServerSock serverSock;
ClientSock clientSock;
char sendBuffer[BUFSIZ];
char recieveBuffer[BUFSIZ];
int sendedFileSize;

extern void tempFunction()
{
    serverSock.SocketDefine();
    serverSock.SockAdressClear();
    serverSock.BindAndListenSocketInPort(PORT);

    while (true)
    {
        clientSock.AcceptConnection(serverSock.thisSocket);
        printf("----------------------------------------------------\n");
        //printf("%d\n", clientAdress.sin_addr.s_addr);
        if (read(clientSock.thisSocket, recieveBuffer, sizeof(recieveBuffer)) > 0)
            printf("%s", recieveBuffer);
        printf("----------------------------------------------------\n");
        sendedFileSize = clientSock.SendFile("send.txt");
        if (!sendedFileSize)
            printf("Failed to send message\n");
        else
            printf("%d bytes data sended sucessfully!\n", sendedFileSize);
        close(clientSock.thisSocket);
    }
}

int CommandReader()
{
    char command[128];
    for (;;)
    {
        std::cin >> command;
        if (!strcmp(command, "end"))
        {
            close(serverSock.thisSocket);
            exit(0);
        }
    }
}
