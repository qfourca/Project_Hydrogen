#include "Server.h"

int main()
{
    printf("Main Function Started\n");
    std::thread mainThread1(MainFunction);
    printf("Thread One Opened\n");
    //std::thread mainThread2(MainFunction);
    //printf("Thread Two Opened\n");

    for (int i = 0; i < ARRAYSIZE; i++)
    {
        array[i].thisSocket = -1;
        threadArray[i] = std::thread(Sex, i);
    }
    std::thread sendDataThread(SendDataFunction);
    printf("SendData Thread Opened\n\n");

    CommandReader();

    sendDataThread.join();

    mainThread1.join();
    for (int i = 0; i < ARRAYSIZE; i++)
    {
        threadArray[i].join();
    }
    //mainThread2.join();
}
