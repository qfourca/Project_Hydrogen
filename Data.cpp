#include "DataClass.h"
std::vector<Error> Data::errors;

int Data::ProcessRequestMethod()
{
    char method[20];
    for (working_idx = 0; _recived_data[working_idx] != '/' && _recived_data[working_idx] != ' '; working_idx++)
    {
    }
    if (!strncmp(method, "GET", working_idx))
        return GET;
    else if (!strncmp(method, "CONNECT", working_idx))
        return CONNECT;
    else if (!strncmp(method, "DELETE", working_idx))
        return DELETE;
    else if (!strncmp(method, "POST", working_idx))
        return POST;
    else if (!strncmp(method, "HEAD", working_idx))
        return HEAD;
    else if (!strncmp(method, "OPCTIONS", working_idx))
        return OPCTIONS;
    else if (!strncmp(method, "PATCH", working_idx))
        return PATCH;
    else if (!strncmp(method, "PUT", working_idx))
        return PUT;
    else if (!strncmp(method, "TRACE", working_idx))
        return TRACE;
    else
    {
        struct Error tempError;
        tempError._codeName = UNKNOWM_METHOD;
        int error_long = strlen(method);
        if (error_long > ERROR_BUF)
        {
            for (int i = ERROR_BUF - 1; i > ERROR_BUF - 4; i--)
                tempError._contents[i] = '.';
            error_long = ERROR_BUF - 3;
        }
        strncpy(tempError._contents, method, error_long);
        errors.push_back(tempError);
        return UNKNOWN;
    }
}
int Data::ProcessFileName()
{
    for (; _recived_data[working_idx] != '/'; working_idx++)
    {
    }
    working_idx++;
    if (_recived_data[working_idx] == ' ')
    {
        _request_file[0] = 0;
        return -1;
    }
    else
    {
        strcpy(_request_file, SENDFOLDER);
        int i;
        for (i = strlen(SENDFOLDER); _recived_data[working_idx] != ' '; working_idx++)
        {
            _request_file[i] = _recived_data[working_idx];
            i++;
        }
        return i;
    }
}

int Data::ProcessData()
{
    _request_method = ProcessRequestMethod();
    ProcessFileName();
    return 0;
}