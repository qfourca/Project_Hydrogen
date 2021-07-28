#include "Server.h"
int main()
{
    std::thread Thread1(tempFunction);
    CommandReader();
    Thread1.join();
}
