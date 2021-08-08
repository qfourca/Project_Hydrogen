#include "Server.h"

ServerSock serverSock;
char buffer[BUFSIZ];
std::queue<ClientSock> clientWaitQueue;
std::mutex socketQueueMutex;
int arrayIndex = 0;
struct ReadThreadManagement management[READTHREADSIZE];
bool speed = false;

extern void MainFunction()
{
    ClientSock clientSock;
    for (;;)
    {
        for (; management[arrayIndex].clientSock.thisSocket != -1;)
        {
            //speed = true;
            usleep(SLEEPTIME);
        }
        clientSock.AcceptConnection(serverSock.thisSocket);
        if (arrayIndex >= READTHREADSIZE - 1)
            arrayIndex = 0;
        else
            arrayIndex++;
        management[arrayIndex].clientSock.thisSocket = clientSock.thisSocket;
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
            for (int i = 0; i < READTHREADSIZE; i++)
                printf("%d", management[i].clientSock.thisSocket);
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
            //myClient.SendFile("send/header.txt");
            //std::cout << tempClient.Interpreter() << std::endl;
            myClient.Interpreter(); //데이터를 처리하고 그에 맞는 데이터를 전송하는 함수
            close(myClient.thisSocket);
        }
        else
            usleep(SLEEPTIME);
    }
}

extern void Input(int myAccessPoint)
{
    for (;;)
    {
        if (management[myAccessPoint].clientSock.thisSocket != -1)
        {
            //management[myAccessPoint].readThreadMutex.lock();
            if (read(management[myAccessPoint].clientSock.thisSocket,
                     management[myAccessPoint].clientSock.recivedData, BUFSIZ) > 0)
            {
                socketQueueMutex.lock();
                clientWaitQueue.push(management[myAccessPoint].clientSock);
                socketQueueMutex.unlock();
                for (int i = 0; i < BUFSIZ; i++)
                {
                    management[myAccessPoint].clientSock.recivedData[i] = 0;
                };
            }
            management[myAccessPoint].clientSock.thisSocket = -1;
            //management[myAccessPoint].readThreadMutex.unlock();
        }
        else
            usleep(SLEEPTIME);
    }
}