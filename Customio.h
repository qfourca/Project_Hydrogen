#include <iostream>
#include <cstdio>
namespace cus
{
    class Custumio
    {
    private:
        char sendBuffer[BUFSIZ];
        char recieveBuffer[BUFSIZ];

    public:
        int InputFileInSendBuffer(const char *fileName);
        int InputStringInSendBuffer(const char *string);
    };
};
