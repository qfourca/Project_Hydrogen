#include "Main.h"

int main()
{
    printl("Main Function Start\n", PRINTOUT); //main함수의 시작을 알림

    for (int i = 0; i < READTHREADSIZE; i++)
    {
        management[i].clientSock._sock_descriptor = -1;
        management[i].readArray = std::thread(Input, i); //입력 쓰레드 실행
    }
    for (int i = 0; i < SENDTHREADSIZE; i++)
    {
        sendThread[i] = std::thread(SendDataFunction); //전송 쓰레드 실행
        printl("SendData Thread Opened\n", PRINTOUT);
    }

    std::thread mainThread(MainFunction); //주 쓰레드 실행
    printl("Main Thread Opened\n", PRINTOUT);

    CommandReader(); //명령어 처리기 프로그램의 전체적인 흐름을 제어한다

    mainThread.join();
    for (int i = 0; i < SENDTHREADSIZE; i++)
        sendThread[i].join();
    for (int i = 0; i < READTHREADSIZE; i++)
        management[i].readArray.join();

    printl("Server closed successfully\n", PRINTOUT);
    return 0;
}

extern void MainFunction()
{
    ClientSock clientSock;
    int arrayIndex = 0;
    for (;;)
    {
        for (; management[arrayIndex].clientSock._sock_descriptor != -1;) //입력 배열이 비지 않았을 경우
            usleep(delayTime);                                            //delayTime 만큼 휴식
        clientSock.acceptConnection(serverSock._sock_descriptor);         //연결 받기
        if (arrayIndex >= READTHREADSIZE - 1)                             //다음으로 입력받을 쓰레드가 없을경우
            arrayIndex = 0;                                               //0으로 돌아가기
        else                                                              //있을 경우
            arrayIndex++;                                                 //다음 쓰레드로 넘어가기
        management[arrayIndex].clientSock._sock_descriptor = clientSock._sock_descriptor;
        //지금의 소켓 디스크럽터를 넣어 주기
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
            close(serverSock._sock_descriptor); //소켓 닫기
            exit(0);
        }
        else if (!strcmp(command, "speed"))
            std::cout << "delay time is " << delayTime << std::endl;
        else if (!strcmp(command, "speeddef"))
        {
            std::cout << "input delay time : ";
            unsigned int temp_delay_time;
            std::cin >> temp_delay_time;
            if (temp_delay_time <= 0)
                std::cout << "Error\n";
            else
            {
                delayTime = temp_delay_time;
            }
        }
        else if (!strcmp(command, "info"))
            for (int i = 0; i < READTHREADSIZE; i++)
                std::cout << management[i].clientSock._sock_descriptor << std::endl;
        else
            std::cout << "Unknown Command\n"; //알지 못하는 명령어가 들어왔을 때
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
            printl("----------------------------------------------------\n", DONTTIME);
            printl(myClient._data._recived_data, false);
            printl("----------------------------------------------------\n", DONTTIME);
            myClient.sendDataAuto();
            close(myClient._sock_descriptor);
        }
        else
            usleep(delayTime);
    }
}

extern void Input(int myAccessPoint)
{
    char str[64];
    sprintf(str, "input Thread No.%d Started \n", myAccessPoint);
    printl(str, PRINTOUT);
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
