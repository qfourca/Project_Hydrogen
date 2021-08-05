#include "Server.h"

ServerSock serverSock;
char buffer[BUFSIZ];
std::queue<ClientSock> clientWaitQueue;
std::mutex socketQueueMutex;
int arrayIndex = 1;

ClientSock array[ARRAYSIZE];
std::thread threadArray[ARRAYSIZE];

extern void MainFunction()
{
    for (;;)
    {

        ClientSock clientSock;
        clientSock.AcceptConnection(serverSock.thisSocket);
        /*
        if (read(clientSock.thisSocket, clientSock.recivedData, BUFSIZ) > 0)
        {
            clientWaitQueue.push(clientSock);
        }
        */

        array[arrayIndex] = clientSock;
        if (arrayIndex >= ARRAYSIZE - 1)
            arrayIndex = 1;
        else
            arrayIndex++;
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
            //socketQueueMutex.lock();
            ClientSock tempClient = clientWaitQueue.front();
            clientWaitQueue.pop();
            //socketQueueMutex.unlock();
            printf("----------------------------------------------------\n");
            printf("%s", tempClient.recivedData);
            printf("----------------------------------------------------\n");

            //std::cout << tempClient.Interpreter() << std::endl;
            tempClient.Interpreter();
            close(tempClient.thisSocket);
        }
    }
}

extern void Input(int myAccessPoint)
{
    for (;;)
    {
        if (array[myAccessPoint].thisSocket != -1)
        {
            if (read(array[myAccessPoint].thisSocket, array[myAccessPoint].recivedData, BUFSIZ) > 0)
            {
                socketQueueMutex.lock();
                clientWaitQueue.push(array[myAccessPoint]);
                socketQueueMutex.unlock();
            }
            array[myAccessPoint].thisSocket = -1;
        }
    }
}