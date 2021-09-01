#include "DataClass.h"

int Data::requestMethod()
{
    char method[32];
    if (strlen(method) == 3)
    {
        if (method[0] == 'G')
            return GET;
        else if (method[0] == 'P')
            return PUT;
    }
    else if (strlen(method) == 4)
    {
        if (method[0] == 'P')
            return POST;
        else if (method[0] == 'H')
            return HEAD;
    }
    else if (strlen(method) == 5)
    {
        if (method[0] == 'P')
            return PATCH;
        else if (method[0] == 'T')
            return TRACE;
    }
    else if (strlen(method) == 6)
    {
        if (method[0] == 'C')
            return CONNECT;
        else if (method[0] == 'D')
            return DELETE;
    }
    else if (strlen(method) == 7 && method[0] == 'O')
        return OPCTIONS;
    return UNKNOWN;
}
char *Data::fileName()
{
    strcpy(filename, SENDFOLDER); //앞에 폴더의 경로 붙이기
    char *ptrFilename = filename;
    char *ptrRecieve = _recived_data;
    ptrFilename += FOLDERLONG;
    while (*ptrRecieve != '/')
        ptrRecieve++;
    ptrRecieve++;
    for (; *ptrRecieve != ' '; ptrRecieve++)
    {
        *ptrFilename = *ptrRecieve;
        ptrFilename++;
    }
    return filename;
}
