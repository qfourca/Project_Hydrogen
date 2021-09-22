#include "SockClass.h"

int ClientSock::sendDataAuto()
{

    if (!strcmp(_data.fileName(), SENDFOLDER)) //아무것도 없을 때
        sendFile("send/index.html");           //index.html 전송
    else
    {
        int temp = sendFile(_data.fileName());
        if (temp == -1) //파일 전송에 에러가 났을 때
        {
            printl("Error occur when send file :", PRINTERR);
            printl(_data.fileName(), PRINTERR);
            printl("\n", PRINTERR);
            sendString("404 not found"); //404전송
        }
    }
    return DEFAULT;
}

int ClientSock::sendFile(const char *fileName)
{
    struct stat stbuf;
    int file_descriptor = open(fileName, O_RDONLY); //전송할 파일을 읽기 전용으로 열기
    if (file_descriptor == -1)                      //만약 -1(에러) 가 났다면
        return ERROR;                               //에러 반환

    fstat(file_descriptor, &stbuf);
    int send_file_size = sendfile(_sock_descriptor, file_descriptor, SEEK_SET, 2147479552);
    if (send_file_size != -1)
    {
        char printlog[BUFSIZ];
        int len = sprintf(printlog, "%d bytes data sended sucessfully! filename : %s\n", send_file_size, fileName);
        printl(printlog, PRINTOUT);
    }
    close(file_descriptor);
    return send_file_size;
}
int ClientSock::sendString(const char *dataName)
{
    int send_data_size = send(_sock_descriptor, dataName, strlen(dataName), MSG_DONTROUTE);
    if (send_data_size == -1)
    {
        printl("Failed to send message\n", PRINTERR);
        return ERROR;
    }
    else
    {
        char str[64];
        sprintf(str, "data \" %s \" sended sucessfully!\n", dataName);
        printl(str, PRINTOUT);
        return send_data_size;
    }
}
////////////////////////----------------------------------////////////////////
unsigned int Sock::_adressLen = sizeof(sockaddr_in); //주소의 길이
Sock::Sock()
{
    memset(&_sock_adress, 0, sizeof(_sock_adress));
    _sock_descriptor = socket(PF_INET, SOCK_STREAM, 0);
}
///////////////////------------------------------------////////////////////////
int ClientSock::acceptConnection(int serverSocket)
{
    _sock_descriptor = accept(serverSocket, (struct sockaddr *)&_sock_adress, &_adressLen);
    return 0;
}
void ClientSock::acceptSocket(int serverSocket)
{
    _sock_descriptor = accept(serverSocket, (struct sockaddr *)&_sock_adress, &_adressLen);
}

ClientSock::ClientSock()
{
    int sock_opction = 1;
    if (setsockopt(_sock_descriptor, IPPROTO_TCP, TCP_CORK, (const char *)&sock_opction, sizeof(sock_opction)) == -1)
    {
        printl("ClientSocket Setting Error\n", PRINTERR);
        exit(1);
    }
}

char *ClientSock::searchString(const char *string)
{
    return strstr(_data._recived_data, string) + strlen(string);
}

////////////////////-------------------------//////////////////////////

ServerSock::ServerSock()
{
    _sock_adress.sin_family = AF_INET;
    _sock_adress.sin_port = htons(httpPort);
    if ((_sock_adress.sin_addr.s_addr = INADDR_ANY) == -1)
    {
        printl("Wrong IP adress\n", PRINTERR);
        exit(1);
    }
    if (-1 == bind(_sock_descriptor, (struct sockaddr *)&_sock_adress, sizeof(_sock_adress)))
    {
        printl("Can Not Bind\n", PRINTERR);
        exit(1);
    }
    else
        printl("Bind Sucessfully\n", PRINTOUT);

    if (listen(_sock_descriptor, 5) == -1)
    {
        printl("listen fail\n", PRINTERR);
        exit(1);
    }
    else
    {
        printl("Listen Successed\n", PRINTOUT);
    }
    char str[128];
    sprintf(str, "Server Open! %s:%u\n", "localhost", ntohs(_sock_adress.sin_port));
    printl(str, PRINTOUT);
}
/////////////////////////////////////////////////
void printl(const char *input, char flag)
{
    char file_name[64];
    int len = sprintf(file_name, "%s%s%d%s", LOGFOLDER, "log", 1, ".txt");
    unsigned int logFileD = open(file_name, O_WRONLY | O_CREAT | O_APPEND | O_EXCL, S_IRUSR | S_IRGRP);
    if (logFileD == -1)
    {
        struct passwd *sudo;
        sudo = getpwnam("user");
        if (-1 == chown(file_name, sudo->pw_uid, sudo->pw_gid))
            perror("error");
        logFileD = open(file_name, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IRGRP);
    }
    char printlog[BUFSIZ];
    char temp[128];
    len = strlen(input);
    if (flag & DONTTIME)
        strcpy(printlog, input);
    else
    {
        strncpy(temp, len > 70 ? "[%02d:%02d:%02d:%02d]\n%s" : "[%02d:%02d:%02d:%02d] %s", 32);
        len = sprintf(printlog, temp, retTime(DAY), retTime(HOUR), retTime(MIN), retTime(SEC), input);
    }

    if (logFileD >= -1 && logFileD <= 2)
        std::cout << "[ERROR]file open error code : " << logFileD << std::endl;
    else
    {
        if (flag & PRINTOUT)
            write(1, printlog, len);
        if (flag & PRINTERR)
            write(2, printlog, len);
        write(logFileD, printlog, len);
        close(logFileD);
    }
}
int retTime(int arg)
{
    time_t timer = time(NULL);
    struct tm *t = localtime(&timer);
    switch (arg)
    {
    case SEC:
        return t->tm_sec;
    case MIN:
        return t->tm_min;
    case HOUR:
        return t->tm_hour;
    case DAY:
        return t->tm_mday;
    default:
        return ERROR;
    }
}
