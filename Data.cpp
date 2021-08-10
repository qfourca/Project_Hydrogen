#include "DataClass.h"

int Data::ProcessRequestMethod()
{
    char requestMethod[20];
    for (workIndex = 0; recivedData[workIndex] != '/' && recivedData[workIndex] != ' '; workIndex++)
    {
    }
    strncpy(requestMethod, recivedData, workIndex);
    if (!strcmp(requestMethod, "GET"))
        return GET;
    else if (!strcmp(requestMethod, "CONNECT"))
        return CONNECT;
    else if (!strcmp(requestMethod, "DELETE"))
        return DELETE;
    else if (!strcmp(requestMethod, "POST"))
        return POST;
    else if (!strcmp(requestMethod, "HEAD"))
        return HEAD;
    else if (!strcmp(requestMethod, "OPCTIONS"))
        return OPCTIONS;
    else if (!strcmp(requestMethod, "PATCH"))
        return PATCH;
    else if (!strcmp(requestMethod, "PUT"))
        return PUT;
    else if (!strcmp(requestMethod, "TRACE"))
        return TRACE;
    else
        return UNKNOWN;
}
int Data::ProcessFileName()
{
    for (; recivedData[workIndex] != '/'; workIndex++)
    {
    }
    workIndex++;
    if (recivedData[workIndex] == ' ')
    {
        requestFile[0] = 0;
        return -1;
    }
    else
    {
        strcpy(requestFile, SENDFOLDER);
        int i;
        for (i = strlen(SENDFOLDER); recivedData[workIndex] != ' '; workIndex++)
        {
            requestFile[i] = recivedData[workIndex];
            i++;
        }
        return i;
    }
}

int Data::ProcessData()
{
    requestMethod = ProcessRequestMethod();
    ProcessFileName();
    return 0;
}