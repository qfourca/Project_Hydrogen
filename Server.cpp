#include "Server.h"

ServerSock serverSock;
char buffer[BUFSIZ];
std::queue<ClientSock> clientWaitQueue;
std::queue<ClientSock> recvWaitQueue;

extern void MainFunction()
{

    serverSock.SocketDefine();
    serverSock.SockAdressClear();
    serverSock.BindAndListenSocketInPort(PORT);

    for (;;)
    {
        ClientSock clientSock;
        clientSock.AcceptConnection(serverSock.thisSocket);
        if (read(clientSock.thisSocket, clientSock.recivedData, BUFSIZ) > 0)
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
        else if (!strcmp(command, "info"))
        {
            printf("%ld개의 전송을 대기중입니다\n", clientWaitQueue.size());
        }
    }
}

extern void SendDataFunction()
{
    for (;;)
    {
        if (!clientWaitQueue.empty())
        {
            int temp;
            ClientSock tempClient = clientWaitQueue.front();
            printf("----------------------------------------------------\n");
            printf("%s", tempClient.recivedData);
            printf("----------------------------------------------------\n");

            tempClient.SendFile("send/header.txt");
            tempClient.SendFile("send/main.html");

            clientWaitQueue.pop();
            close(tempClient.thisSocket);
        }
    }
}
extern void RecieveDataFunction()
{
    std::vector<std::thread> threadSTL();
    for (;;)
    {
        if (!recvWaitQueue.empty())
        {
        }
    }
}