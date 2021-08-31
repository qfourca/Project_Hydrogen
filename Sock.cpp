#include "SockClass.h"

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
    int file_descriptor = open(fileName, O_RDONLY);
    if (file_descriptor == -1)
    {
        return -1;
    }
    fstat(file_descriptor, &stbuf);
    int send_file_size = sendfile(_sock_descriptor, file_descriptor, SEEK_SET, 2147479552);
    if (send_file_size != -1)
        printf("%d bytes data sended sucessfully! filename : %s\n", send_file_size, fileName);
    close(file_descriptor);
    return send_file_size;
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
    return strstr(_data._recived_data, string) + strlen(string);
}

int ClientSock::interpreter()
{
    printf("%s\n", _data.fileName());
    if (!strcmp(_data.fileName(), SENDFOLDER))
        sendFile("send/index.html");
    else
    {
        int temp = sendFile(_data.fileName());
        if (temp == -1)
        {
            perror("ERROR!");
            sendData("404");
        }
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