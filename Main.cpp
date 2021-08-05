#include "Server.h"

int main()
{
    printf("Main Function Started\n");
    std::thread mainThread(MainFunction);
    printf("mainThread Opened\n");

    for (int i = 0; i < ARRAYSIZE; i++)
    {
        array[i].thisSocket = -1;
        threadArray[i] = std::thread(Input, i);
        printf("inputThread %d opened\n", i + 1);
    }

    std::thread sendDataThread(SendDataFunction);
    printf("SendData Thread Opened\n\n");

    CommandReader();

    sendDataThread.join();
    mainThread.join();

    for (int i = 0; i < ARRAYSIZE; i++)
    {
        threadArray[i].join();
    }
}
