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

int Data::urlDecoder(char *input, char *output)
{
    int num = 0, i, hexv, index = 0;
    int retval = 0;
    while (*input)
    {
        if (*input == '%')
        {
            num = 0;
            retval = 0;

            for (i = 0; i < 2; i++)
            {
                *input++;
                if (*(input) < ':')
                {
                    num = *(input)-48;
                }
                else if (*(input) > '@' && *(input) < '[')
                {
                    num = (*(input) - 'A') + 10;
                }
                else
                {
                    num = (*(input) - 'a') + 10;
                }

                if ((16 * (1 - i)))
                    num = (num * 16);
                retval += num;
            }
            output[index] = retval;
            index++;
        }
        else if (*input == '+')
        {
            output[index] = ' ';
            index++;
        }
        else
        {
            output[index] = *input;
            index++;
        }
        *input++;
    }
    return index;
}
int Data::urlDecoder(char *arg)
{
    char *output;
    int ret = urlDecoder(arg, output);
    arg = output;
    return ret;
}
int Data::urlDecoder()
{
    return urlDecoder(_recived_data);
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
int Data::host()
{
    char *start = strstr(_recived_data, HOST);
    start += strlen(HOST);
    start++;
    if (!strcmp(start, "localhost"))
        return LOCALHOST;
    else
        return ERROR;
}
