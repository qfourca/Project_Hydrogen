#include "Server.h"

int main()
{
    printf("Main Function Started\n"); //main함수의 시작을 알림

    for (int i = 0; i < READTHREADSIZE; i++)
    {
        management[i].clientSock.sock_descriptor = -1;
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

    CommandReader(); //명령어 처리기 프로그램의 전체적인 흐름을 제어한다

    mainThread.join();
    for (int i = 0; i < SENDTHREADSIZE; i++)
    {
        sendThread[i].join();
    }
    for (int i = 0; i < READTHREADSIZE; i++)
    {
        management[i].readArray.join();
    }
}
