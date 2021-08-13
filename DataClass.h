#include "Defines/Defines.h"
#include "Defines/ErrorDefines.h"
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <vector>
struct Error
{
    char _contents[ERROR_BUF];
    int _codeName;
};
struct History
{
    long long int _method_history[CONNECTTION_REQUEST_MACOR_COUNT];
};

class Data
{
private:
    int working_idx = 0; //현재 작업중인 인덱스
    int ProcessRequestMethod();
    int ProcessFileName();

public:
    int _request_method;
    char _request_file[FILENAMESIZE];
    char _recived_data[BUFSIZ];

    static std::vector<Error> errors;

    int ProcessData();
};
