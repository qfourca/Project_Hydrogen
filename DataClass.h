#include "Defines.h"
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
class Data
{
private:
    int workIndex = 0;
    int ProcessRequestMethod();
    int ProcessFileName();

public:
    int requestMethod;
    char requestFile[FILENAMESIZE];
    int protocol;
    char recivedData[BUFSIZ];

    int ProcessData();
};
