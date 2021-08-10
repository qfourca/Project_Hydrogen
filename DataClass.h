#include "Defines.h"
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
class Data
{
private:
    int working_idx = 0; //현재 작업중인 인덱스
    int ProcessRequestMethod();
    int ProcessFileName();

public:
    int request_method;
    char request_file[FILENAMESIZE];
    char recived_data[BUFSIZ];
    int protocol;

    int ProcessData();
};
