#include "Server.h"
int main()
{
    std::thread mainThread1(MainFunction);
    std::thread mainThread2(MainFunction);
    std::thread sendDataThread(SendDataFunction);

    CommandReader();

    sendDataThread.join();
    mainThread1.join();
    mainThread2.join();
}
