#include "Server.h"

ServerSock serverSock;
char buffer[BUFSIZ];
std::queue<ClientSock> clientWaitQueue;
std::mutex socketQueueMutex;

extern void MainFunction()
{
    for (;;)
    {
        socketQueueMutex.lock();
        ClientSock clientSock;
        clientSock.AcceptConnection(serverSock.thisSocket);
        socketQueueMutex.unlock();
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
        else
        {
            printf("Unknown Command\n");
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
            clientWaitQueue.pop();
            printf("----------------------------------------------------\n");
            printf("%s", tempClient.recivedData);
            printf("----------------------------------------------------\n");

            //std::cout << tempClient.Interpreter() << std::endl;
            tempClient.Interpreter();
            close(tempClient.thisSocket);
        }
    }
}