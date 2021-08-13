#include "SockClass.h"
#define FOLDER 5

////////////////////////----------------------------------////////////////////
unsigned int Sock::_adressLen = sizeof(sockaddr_in); //주소의 길이
Sock::Sock()
{
    memset(&_sock_adress, 0, sizeof(_sock_adress));
    _sock_descriptor = socket(PF_INET, SOCK_STREAM, 0);
}

///////////////////------------------------------------////////////////////////

int ClientSock::AcceptConnection(int serverSocket)
{
    _sock_descriptor = accept(serverSocket, (struct sockaddr *)&_sock_adress, &_adressLen);
    return 0;
}

void ClientSock::AcceptSocket(int serverSocket)
{
    _sock_descriptor = accept(serverSocket, (struct sockaddr *)&_sock_adress, &_adressLen);
}

int ClientSock::SendFile(const char *fileName)
{
    struct stat stbuf;
    int inFileDescriptor = open(fileName, O_RDONLY);
    if (inFileDescriptor == -1)
    {
        return -1;
    }
    fstat(inFileDescriptor, &stbuf);
    int sendedFileSize = sendfile(_sock_descriptor, inFileDescriptor, SEEK_SET, 2147479552);
    if (sendedFileSize == -1)
    {
        perror("Failed to send message\n");
        close(inFileDescriptor);
        return -1;
    }
    else
    {
        printf("%d bytes data sended sucessfully! filename : %s\n", sendedFileSize, fileName);
        close(inFileDescriptor);
        return sendedFileSize;
    }
}

int ClientSock::SendData(const char *dataName)
{
    int sendedDataSize = send(_sock_descriptor, dataName, strlen(dataName), MSG_DONTROUTE);
    if (sendedDataSize == -1)
    {
        perror("Failed to send message\n");
        return -1;
    }
    else
    {
        printf("data \" %s \" sended sucessfully!\n", dataName);
        return sendedDataSize;
    }
}

ClientSock::ClientSock()
{
    int sockopt = 1;
    if (setsockopt(_sock_descriptor, IPPROTO_TCP, TCP_CORK, (const char *)&sockopt, sizeof(sockopt)) == -1)
    {
        perror("ClientSocket Setting Error\n");
        exit(1);
    }
}

char *ClientSock::searchString(const char *string)
{
    return strstr(recivedData._recived_data, string) + strlen(string);
}

int ClientSock::Interpreter()
{
    recivedData.ProcessData();
    printf("\x1b[31m %d \n\x1b[0m", recivedData._request_method);
    printf("%s\n", recivedData._request_file);
    if (recivedData._request_file[0] == 0)
    {
        printf("NULL\n");
        strcpy(recivedData._request_file, "send/index.html");
    }
    //keep_conection = !strncmp(searchString("Connection: "), "keep-alive", 10);
    if (SendFile(recivedData._request_file) == -1)
    {
        printf("\x1b[31m I Can't found File\n\x1b[0m");
        SendFile("send/index.html");
    }
    return DEFAULT;
}

////////////////////-------------------------//////////////////////////

ServerSock::ServerSock()
{
    _sock_adress.sin_family = AF_INET;
    _sock_adress.sin_port = htons(PORT);
    if ((_sock_adress.sin_addr.s_addr = INADDR_ANY) == -1)
    {
        perror("Wrong IP adress");
        exit(1);
    }
    if (bind(_sock_descriptor, (struct sockaddr *)&_sock_adress, sizeof(_sock_adress)) == -1)
    {
        perror("Can not Bind");
        exit(1);
    }
    else
    {
        printf("Bind Successed!\n");
    }
    if (listen(_sock_descriptor, 5) == -1)
    {
        perror("listen Fail");
        exit(1);
    }
    else
    {
        printf("Listen Successed\n");
    }
    printf("Server Open! %s:%u\n\n", MYIP, ntohs(_sock_adress.sin_port));
}
/////////////////////////////////////////////////