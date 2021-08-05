#include "SockClass.h"
#define FOLDER 5
////////////////////////----------------------------------////////////////////
Sock::Sock()
{
    memset(&thisSocketAdress, 0, sizeof(thisSocketAdress));
    thisSocket = socket(PF_INET, SOCK_STREAM, 0);
}

///////////////////------------------------------------////////////////////////

int ClientSock::AcceptConnection(int serverSocket)
{
    thisSocket = accept(serverSocket, (struct sockaddr *)&thisSocketAdress, &adressLen);
    return 0;
}
sockaddr *ClientSock::ReturnSockAdressP()
{
    return (struct sockaddr *)&thisSocketAdress;
}
void ClientSock::AcceptSocket(int serverSocket)
{
    thisSocket = accept(serverSocket, ReturnSockAdressP(), &adressLen);
}
int ClientSock::SendFile(const char *fileName)
{
    /*
    char temp[6] = "send/";
    for (int i = 0; fileName[i] != '\0'; i++)
    {
        if (fileName[i] == '/')
        {
            goto Jump;
        }
    }
    strcat(temp, fileName);
Jump:;*/
    struct stat stbuf;
    int inFileDescriptor = open(fileName, O_RDONLY);
    if (inFileDescriptor == -1)
    {
        return -1;
    }
    fstat(inFileDescriptor, &stbuf);
    int sendedFileSize = sendfile(thisSocket, inFileDescriptor, SEEK_SET, 2147479552);
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

int ClientSock::PutInRecivedData(const char *input)
{
    return strcmp(recivedData, input);
}
ClientSock::ClientSock()
{
    int sockopt = 1;
    if (setsockopt(thisSocket, IPPROTO_TCP, TCP_CORK, (const char *)&sockopt, sizeof(sockopt)) == -1)
    {
        perror("ClientSocket Setting Error\n");
        exit(1);
    }
}
int ClientSock::whereIsSlash()
{
    int address = 0;
    for (; recivedData[address] != '/'; address++)
    {
    }
    for (++address; recivedData[address] == ' '; address++)
    {
    }
    return address;
}
int ClientSock::returnFileName(char *fileName)
{
    int startIndex = whereIsSlash();
    int endIndex = startIndex;
    for (; recivedData[endIndex] != ' '; endIndex++)
    {
    }
    strcpy(fileName, "send/");
    for (int inputIndex = FOLDER; startIndex < endIndex; startIndex++)
    {
        fileName[inputIndex] = recivedData[startIndex];
        inputIndex++;
    }
    return 0;
}
int ClientSock::Interpreter()
{
    char temp[512] = {0};
    returnFileName(temp);
    printf("%s\n", temp);
    if (SendFile(temp) == -1)
    {
        printf("\x1b[31m I Can't found File\n\x1b[0m");
        SendFile("send/index.html");
    }
    //printf("%s\n", temp);
    return DEFAULT;
    //SendFile("send/header.txt");
    //printf("%c\n", recivedData[whereIsSlash()]);
    /*
    switch (recivedData[whereIsSlash()])
    {
    case 'H':
        SendFile("send/main.html");
        return DEFAULT;
    case 'f':
        SendFile("send/favicon.ico");
        return FAVICON;
    case 'm':
        SendFile("send/mycss.css");
        return CSS;
    default:
        SendFile("send/main.html");
        return ERROR;
    }
    */
}

////////////////////-------------------------//////////////////////////

ServerSock::ServerSock()
{
    thisSocketAdress.sin_family = AF_INET;
    thisSocketAdress.sin_port = htons(PORT);
    if ((thisSocketAdress.sin_addr.s_addr = INADDR_ANY) == -1)
    {
        perror("Wrong IP adress");
        exit(1);
    }
    if (bind(thisSocket, (struct sockaddr *)&thisSocketAdress, sizeof(thisSocketAdress)) == -1)
    {
        perror("Can not Bind");
        exit(1);
    }
    else
    {
        printf("Bind Successed!\n");
    }
    if (listen(thisSocket, 5) == -1)
    {
        perror("listen Fail");
        exit(1);
    }
    else
    {
        printf("Listen Successed\n");
    }
    printf("Server Open! %s:%u\n\n", MYIP, ntohs(thisSocketAdress.sin_port));
}
/////////////////////////////////////////////////