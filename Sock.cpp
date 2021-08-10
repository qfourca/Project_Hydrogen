#include "SockClass.h"
#define FOLDER 5

////////////////////////----------------------------------////////////////////
unsigned int Sock::adressLen = sizeof(sockaddr_in); //주소의 길이
Sock::Sock()
{
    memset(&sock_adress, 0, sizeof(sock_adress));
    sock_descriptor = socket(PF_INET, SOCK_STREAM, 0);
}

///////////////////------------------------------------////////////////////////

int ClientSock::AcceptConnection(int serverSocket)
{
    sock_descriptor = accept(serverSocket, (struct sockaddr *)&sock_adress, &adressLen);
    return 0;
}

void ClientSock::AcceptSocket(int serverSocket)
{
    sock_descriptor = accept(serverSocket, (struct sockaddr *)&sock_adress, &adressLen);
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
    int sendedFileSize = sendfile(sock_descriptor, inFileDescriptor, SEEK_SET, 2147479552);
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
    int sendedDataSize = send(sock_descriptor, dataName, strlen(dataName), MSG_DONTROUTE);
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
    keep_conection = false;
    int sockopt = 1;
    if (setsockopt(sock_descriptor, IPPROTO_TCP, TCP_CORK, (const char *)&sockopt, sizeof(sockopt)) == -1)
    {
        perror("ClientSocket Setting Error\n");
        exit(1);
    }
}

char *ClientSock::searchString(const char *string)
{
    return strstr(recivedData.recived_data, string) + strlen(string);
}

int ClientSock::Interpreter()
{
    recivedData.ProcessData();
    printf("%s\n", recivedData.request_file);
    if (recivedData.request_file[0] == 0)
    {
        printf("NULL\n");
        strcpy(recivedData.request_file, "send/index.html");
    }
    keep_conection = !strncmp(searchString("Connection: "), "keep-alive", 10);
    if (SendFile(recivedData.request_file) == -1)
    {
        printf("\x1b[31m I Can't found File\n\x1b[0m");
        SendFile("send/index.html");
    }
    return DEFAULT;
}

////////////////////-------------------------//////////////////////////

ServerSock::ServerSock()
{
    sock_adress.sin_family = AF_INET;
    sock_adress.sin_port = htons(PORT);
    if ((sock_adress.sin_addr.s_addr = INADDR_ANY) == -1)
    {
        perror("Wrong IP adress");
        exit(1);
    }
    if (bind(sock_descriptor, (struct sockaddr *)&sock_adress, sizeof(sock_adress)) == -1)
    {
        perror("Can not Bind");
        exit(1);
    }
    else
    {
        printf("Bind Successed!\n");
    }
    if (listen(sock_descriptor, 5) == -1)
    {
        perror("listen Fail");
        exit(1);
    }
    else
    {
        printf("Listen Successed\n");
    }
    printf("Server Open! %s:%u\n\n", MYIP, ntohs(sock_adress.sin_port));
}
/////////////////////////////////////////////////