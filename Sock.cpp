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

int ClientSock::acceptConnection(int serverSocket)
{
    _sock_descriptor = accept(serverSocket, (struct sockaddr *)&_sock_adress, &_adressLen);
    return 0;
}

void ClientSock::acceptSocket(int serverSocket)
{
    _sock_descriptor = accept(serverSocket, (struct sockaddr *)&_sock_adress, &_adressLen);
}

int ClientSock::sendFile(const char *fileName)
{
    struct stat stbuf;
    int inputFile_descriptor = open(fileName, O_RDONLY);
    if (inputFile_descriptor == -1)
    {
        return -1;
    }
    fstat(inputFile_descriptor, &stbuf);
    int sendedFileSize = sendfile(_sock_descriptor, inputFile_descriptor, SEEK_SET, 2147479552);
    if (sendedFileSize == -1)
    {
        perror("Failed to send message\n");
        close(inputFile_descriptor);
        return -1;
    }
    else
    {
        printf("%d bytes data sended sucessfully! filename : %s\n", sendedFileSize, fileName);
        close(inputFile_descriptor);
        return sendedFileSize;
    }
}

int ClientSock::sendData(const char *dataName)
{
    int send_data_size = send(_sock_descriptor, dataName, strlen(dataName), MSG_DONTROUTE);
    if (send_data_size == -1)
    {
        perror("Failed to send message\n");
        return -1;
    }
    else
    {
        printf("data \" %s \" sended sucessfully!\n", dataName);
        return send_data_size;
    }
}

ClientSock::ClientSock()
{
    int sock_opction = 1;
    if (setsockopt(_sock_descriptor, IPPROTO_TCP, TCP_CORK, (const char *)&sock_opction, sizeof(sock_opction)) == -1)
    {
        perror("ClientSocket Setting Error\n");
        exit(1);
    }
}

char *ClientSock::searchString(const char *string)
{
    return strstr(_recive_data._recived_data, string) + strlen(string);
}

int ClientSock::interpreter()
{
    _recive_data.processData();
    printf("\x1b[31m %d \n\x1b[0m", _recive_data._request_method);
    printf("%s\n", _recive_data._request_file);
    if (_recive_data._request_file[0] == 0)
    {
        printf("NULL\n");
        strcpy(_recive_data._request_file, "send/index.html");
    }
    //keep_conection = !strncmp(searchString("Connection: "), "keep-alive", 10);
    if (sendFile(_recive_data._request_file) == -1)
    {
        printf("\x1b[31m I Can't found File\n\x1b[0m");
        sendFile("send/index.html");
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