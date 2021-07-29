#include "Server.h"

ServerSock serverSock;
char buffer[BUFSIZ];
std::queue<ClientSock> clientWaitQueue;

extern void MainFunction()
{

    serverSock.SocketDefine();
    serverSock.SockAdressClear();
    serverSock.BindAndListenSocketInPort(PORT);

    while (true)
    {
        ClientSock clientSock;
        clientSock.AcceptConnection(serverSock.thisSocket);
        if (read(clientSock.thisSocket, clientSock.OutRecivedData(), BUFSIZ) > 0)
        {
            clientWaitQueue.push(clientSock);
        }
    }
}

extern int CommandReader()
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

extern void SendDataFunction()
{
    for (;;)
    {
        if (clientWaitQueue.size() > 0)
        {
            //printf("%ld", clientWaitQueue.size());
            int temp;
            ClientSock tempClient = clientWaitQueue.front();
            printf("----------------------------------------------------\n");
            printf("%s", tempClient.OutRecivedData());
            printf("----------------------------------------------------\n");
            temp = tempClient.SendFile("send/header.txt");
            if (temp == -1)
                perror("Failed to send message\n");
            else
                printf("%d bytes data sended sucessfully!\n", temp);

            temp = tempClient.SendFile("send/main.html");
            if (temp == -1)
                perror("Failed to send message\n");
            else
                printf("%d bytes data sended sucessfully!\n", temp);
            clientWaitQueue.pop();
            //printf("remained : %ld", clientWaitQueue.size());
        }
    }
}