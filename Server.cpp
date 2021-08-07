#include "Server.h"

ServerSock serverSock;
char buffer[BUFSIZ];
std::queue<ClientSock> clientWaitQueue;
std::mutex socketQueueMutex;
int arrayIndex = 0;
ClientSock clientSockWithReadThread[READTHREADSIZE];
std::thread readArray[READTHREADSIZE];
std::mutex readThreadMutex[READTHREADSIZE];
bool speed = false;

extern void MainFunction()
{
    ClientSock clientSock;
    for (;;)
    {
        for (; clientSockWithReadThread[arrayIndex].thisSocket != -1;)
        {
            //speed = true;
            usleep(10);
        }
        clientSock.AcceptConnection(serverSock.thisSocket);
        if (arrayIndex >= READTHREADSIZE - 1)
            arrayIndex = 0;
        else
            arrayIndex++;
        clientSockWithReadThread[arrayIndex].thisSocket = clientSock.thisSocket;
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
    ClientSock myClient;
    for (;;)
    {
        if (!clientWaitQueue.empty())
        {
            myClient = clientWaitQueue.front();
            socketQueueMutex.lock();
            clientWaitQueue.pop();
            socketQueueMutex.unlock();
            printf("----------------------------------------------------\n");
            printf("%s", myClient.recivedData);
            printf("----------------------------------------------------\n");
            myClient.SendFile("send/header.txt");
            //std::cout << tempClient.Interpreter() << std::endl;
            myClient.Interpreter(); //데이터를 처리하고 그에 맞는 데이터를 전송하는 함수
            close(myClient.thisSocket);
        }
        else
            usleep(10);
    }
}

extern void Input(int myAccessPoint)
{
    for (;;)
    {
        readThreadMutex[myAccessPoint].lock();
        if (read(clientSockWithReadThread[myAccessPoint].thisSocket, clientSockWithReadThread[myAccessPoint].recivedData, BUFSIZ) > 0)
        {
            socketQueueMutex.lock();
            clientWaitQueue.push(clientSockWithReadThread[myAccessPoint]);
            socketQueueMutex.unlock();
            for (int i = 0; i < BUFSIZ; i++)
            {
                clientSockWithReadThread[myAccessPoint].recivedData[i] = 0;
            };
        }
        clientSockWithReadThread[myAccessPoint].thisSocket = -1;
        readThreadMutex[myAccessPoint].unlock();
    }
}