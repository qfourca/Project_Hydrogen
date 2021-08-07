#include "Server.h"

int main()
{
    printf("Main Function Started\n"); //main함수의 시작을 알림

    std::thread sendThread[SENDTHREADSIZE]; //전송 쓰레드 선언

    for (int i = 0; i < READTHREADSIZE; i++)
    {
        clientSockWithReadThread[i].thisSocket = -1;
        readArray[i] = std::thread(Input, i);
        printf("inputThread %d opened\n", i + 1); //inputThread실행
    }
    for (int i = 0; i < SENDTHREADSIZE; i++)
    {
        sendThread[i] = std::thread(SendDataFunction); //sendThread실행
    }
    printf("SendData Thread Opened\n\n");

    std::thread mainThread(MainFunction);
    printf("mainThread Opened\n"); //accept 가 들어있는 함수 실행

    CommandReader();
    mainThread.join();
    for (int i = 0; i < SENDTHREADSIZE; i++)
    {
        sendThread[i].join();
    }
    for (int i = 0; i < READTHREADSIZE; i++)
    {
        readArray[i].join();
    }
}
