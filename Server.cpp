#include "Server.h"

ServerSock serverSock;
std::queue<ClientSock> clientWaitQueue;
std::mutex socketQueue_mutex;
int arrayIndex = 0;
struct ThreadManagement management[READTHREADSIZE];
std::thread sendThread[SENDTHREADSIZE]; //전송 쓰레드 선언
bool speed = false;

extern void MainFunction()
{
    ClientSock clientSock;
    for (;;)
    {
        for (; management[arrayIndex].clientSock._sock_descriptor != -1;)
        {
            //speed = true;
            usleep(SLEEPTIME);
        }
        clientSock.acceptConnection(serverSock._sock_descriptor);
        if (arrayIndex >= READTHREADSIZE - 1)
            arrayIndex = 0;
        else
            arrayIndex++;
        management[arrayIndex].clientSock._sock_descriptor = clientSock._sock_descriptor;
    }
}

extern int CommandReader()
{
    ClientSock clientSock;
    char command[128];
    for (;;)
    {
        std::cin >> command;
        if (!strcmp(command, "end"))
        {
            close(serverSock._sock_descriptor);
            exit(0);
        }
        else if (!strcmp(command, "info"))
        {
            std::cout << clientSock._recive_data.errors.size() << std::endl;
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
            socketQueue_mutex.lock();
            clientWaitQueue.pop();
            socketQueue_mutex.unlock();
            printf("----------------------------------------------------\n");
            printf("%s", myClient._recive_data._recived_data);
            printf("----------------------------------------------------\n");
            //myClient.sendFile("send/header.txt");
            //std::cout << tempClient.interpreter() << std::endl;
            myClient.interpreter(); //데이터를 처리하고 그에 맞는 데이터를 전송하는 함수
            close(myClient._sock_descriptor);
        }
        else
            usleep(SLEEPTIME);
    }
}

extern void Input(int myAccessPoint)
{
    for (;;)
    {
        if (management[myAccessPoint].clientSock._sock_descriptor != -1)
        {
            //management[myAccessPoint].readThreadMutex.lock();
            if (read(management[myAccessPoint].clientSock._sock_descriptor,
                     management[myAccessPoint].clientSock._recive_data._recived_data, BUFSIZ) > 0)
            {
                socketQueue_mutex.lock();
                clientWaitQueue.push(management[myAccessPoint].clientSock);
                socketQueue_mutex.unlock();
                for (int i = 0; i < BUFSIZ; i++)
                {
                    management[myAccessPoint].clientSock._recive_data._recived_data[i] = 0;
                };
            }
            management[myAccessPoint].clientSock._sock_descriptor = -1;
            //management[myAccessPoint].readThreadMutex.unlock();
        }
        else
            usleep(SLEEPTIME);
    }
}
