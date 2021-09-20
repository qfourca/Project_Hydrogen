#include "main.h"

int main()
{
    printf("Main Function Start\n"); //main함수의 시작을 알림

    for (int i = 0; i < READTHREADSIZE; i++)
    {
        management[i].clientSock._sock_descriptor = -1;
        management[i].readArray = std::thread(Input, i);
        printf("inputThread %d opened\n", i + 1); //입력 쓰레드 실행
    }
    for (int i = 0; i < SENDTHREADSIZE; i++)
    {
        sendThread[i] = std::thread(SendDataFunction); //전송 쓰레드 실행
        printf("SendData Thread Opened\n\n");
    }

    std::thread mainThread(MainFunction); //연결 쓰레드 실행
    printf("mainThread Opened\n");

    int command_reader = CommandReader(); //명령어 처리기 프로그램의 전체적인 흐름을 제어한다
    if (!CommandReader())
        printf("begin to stop server");
    else
        printf("Something Error Occur when close server Error Code : %d", command_reader);

    mainThread.join();
    for (int i = 0; i < SENDTHREADSIZE; i++)
    {
        sendThread[i].join();
    }
    for (int i = 0; i < READTHREADSIZE; i++)
    {
        management[i].readArray.join();
    }
    printf("Server Closed Sucessfully");
    return 0;
}

extern void MainFunction()
{
    ClientSock clientSock;
    int arrayIndex = 0;
    for (;;)
    {
        for (; management[arrayIndex].clientSock._sock_descriptor != -1;)
        {
            usleep(delayTime);
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
            return 0;
        }
        else if (!strcmp(command, "speed"))
        {
        }
        else if (!strcmp(command, "speeddef"))
        {
        }
        else if (!strcmp(command, "info"))
        {
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
            printf("%s", myClient._data._recived_data);
            printf("----------------------------------------------------\n");
            myClient.interpreter();
            close(myClient._sock_descriptor);
        }
        else
            usleep(delayTime);
    }
}

extern void Input(int myAccessPoint)
{
    for (;;)
    {
        if (management[myAccessPoint].clientSock._sock_descriptor != -1)
        {
            if (read(management[myAccessPoint].clientSock._sock_descriptor,
                     management[myAccessPoint].clientSock._data._recived_data, BUFSIZ) > 0)
            {
                socketQueue_mutex.lock();
                clientWaitQueue.push(management[myAccessPoint].clientSock);
                socketQueue_mutex.unlock();
                for (int i = 0; i < BUFSIZ; i++)
                {
                    management[myAccessPoint].clientSock._data._recived_data[i] = 0;
                };
            }
            management[myAccessPoint].clientSock._sock_descriptor = -1;
        }
        else
            usleep(delayTime);
    }
}
