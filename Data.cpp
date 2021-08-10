#include "DataClass.h"

int Data::ProcessRequestMethod()
{
    char request_method[20];
    for (working_idx = 0; recived_data[working_idx] != '/' && recived_data[working_idx] != ' '; working_idx++)
    {
    }
    strncpy(request_method, recived_data, working_idx);
    if (!strcmp(request_method, "GET"))
        return GET;
    else if (!strcmp(request_method, "CONNECT"))
        return CONNECT;
    else if (!strcmp(request_method, "DELETE"))
        return DELETE;
    else if (!strcmp(request_method, "POST"))
        return POST;
    else if (!strcmp(request_method, "HEAD"))
        return HEAD;
    else if (!strcmp(request_method, "OPCTIONS"))
        return OPCTIONS;
    else if (!strcmp(request_method, "PATCH"))
        return PATCH;
    else if (!strcmp(request_method, "PUT"))
        return PUT;
    else if (!strcmp(request_method, "TRACE"))
        return TRACE;
    else
        return UNKNOWN;
}
int Data::ProcessFileName()
{
    for (; recived_data[working_idx] != '/'; working_idx++)
    {
    }
    working_idx++;
    if (recived_data[working_idx] == ' ')
    {
        request_file[0] = 0;
        return -1;
    }
    else
    {
        strcpy(request_file, SENDFOLDER);
        int i;
        for (i = strlen(SENDFOLDER); recived_data[working_idx] != ' '; working_idx++)
        {
            request_file[i] = recived_data[working_idx];
            i++;
        }
        return i;
    }
}

int Data::ProcessData()
{
    request_method = ProcessRequestMethod();
    ProcessFileName();
    return 0;
}