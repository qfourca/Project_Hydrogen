#include "Server.h"
int main()
{
    std::thread mainThread(MainFunction);
    std::thread sendDataThread(SendDataFunction);
    //std::thread recieveDataThread(RecieveDataFunction);

    CommandReader();
    sendDataThread.join();
    mainThread.join();
}
