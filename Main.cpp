#include "Server.h"
int main()
{
    std::thread mainThread1(MainFunction);
    //printf("Thread One Opened\n");
    std::thread mainThread2(MainFunction);
    //printf("Thread Two Opened\n");

    std::thread sendDataThread(SendDataFunction);
    //printf("SendData Thread Opened\n\n");

    CommandReader();

    sendDataThread.join();
    mainThread1.join();
    mainThread2.join();
}
