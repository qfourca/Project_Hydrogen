#include "Server.h"

ServerSock serverSock;
std::queue<ClientSock> clientWaitQueue;
std::mutex socketQueueMutex;
int arrayIndex = 0;
struct ThreadManagement management[READTHREADSIZE];
std::thread sendThread[SENDTHREADSIZE]; //전송 쓰레드 선언
bool speed = false;

extern void MainFunction()
{
    ClientSock clientSock;
    for (;;)
    {
        for (; management[arrayIndex].clientSock.sock_descriptor != -1;)
        {
            //speed = true;
            usleep(SLEEPTIME);
        }
        clientSock.AcceptConnection(serverSock.sock_descriptor);
        if (arrayIndex >= READTHREADSIZE - 1)
            arrayIndex = 0;
        else
            arrayIndex++;
        management[arrayIndex].clientSock.sock_descriptor = clientSock.sock_descriptor;
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
            close(serverSock.sock_descriptor);
            exit(0);
        }
        else if (!strcmp(command, "info"))
        {
            for (int i = 0; i < READTHREADSIZE; i++)
                printf("%d", management[i].clientSock.sock_descriptor);
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
            printf("%s", myClient.recivedData.recived_data);
            printf("----------------------------------------------------\n");
            //myClient.SendFile("send/header.txt");
            //std::cout << tempClient.Interpreter() << std::endl;
            myClient.Interpreter(); //데이터를 처리하고 그에 맞는 데이터를 전송하는 함수
            close(myClient.sock_descriptor);
        }
        else
            usleep(SLEEPTIME);
    }
}

extern void Input(int myAccessPoint)
{
    for (;;)
    {
        if (management[myAccessPoint].clientSock.sock_descriptor != -1)
        {
            //management[myAccessPoint].readThreadMutex.lock();
            if (read(management[myAccessPoint].clientSock.sock_descriptor,
                     management[myAccessPoint].clientSock.recivedData.recived_data, BUFSIZ) > 0)
            {
                socketQueueMutex.lock();
                clientWaitQueue.push(management[myAccessPoint].clientSock);
                socketQueueMutex.unlock();
                for (int i = 0; i < BUFSIZ; i++)
                {
                    management[myAccessPoint].clientSock.recivedData.recived_data[i] = 0;
                };
            }
            management[myAccessPoint].clientSock.sock_descriptor = -1;
            //management[myAccessPoint].readThreadMutex.unlock();
        }
        else
            usleep(SLEEPTIME);
    }
}
