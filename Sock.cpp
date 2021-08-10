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

int ClientSock::SendData(const char *dataName)
{
    int sendedDataSize = send(thisSocket, dataName, strlen(dataName), MSG_DONTROUTE);
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
    if (setsockopt(thisSocket, IPPROTO_TCP, TCP_CORK, (const char *)&sockopt, sizeof(sockopt)) == -1)
    {
        perror("ClientSocket Setting Error\n");
        exit(1);
    }
}

int ClientSock::whereIsSlash()
{
    int address = 0;
    for (; recivedData.recivedData[address] != '/'; address++)
    {
    }
    for (++address; recivedData.recivedData[address] == ' '; address++)
    {
    }
    return address;
}

int ClientSock::skipSpace(char *string, int startPoint)
{
    for (; string[startPoint] != ' '; startPoint++)
    {
    }
    return startPoint;
}
int ClientSock::skipSpace(int startPoint)
{
    for (; recivedData.recivedData[startPoint] != ' '; startPoint++)
    {
    }
    return startPoint;
}

int ClientSock::returnFileName(char *fileName)
{
    int startIndex = whereIsSlash(); //fileName의 시작을 찾는 과정
    int endIndex = startIndex;
    for (; recivedData.recivedData[endIndex] != ' ' && recivedData.recivedData[endIndex] != '\n'; endIndex++) //fileName의 끝을 찾는 과정
    {
    }
    strcpy(fileName, SENDFOLDER);
    for (int inputIndex = FOLDER; startIndex < endIndex; startIndex++) //fileName에 데이터를 넣는 과정
    {
        fileName[inputIndex] = recivedData.recivedData[startIndex];
        inputIndex++;
    }
    return 0;
}

char *ClientSock::searchString(const char *string)
{
    return strstr(recivedData.recivedData, string) + strlen(string);
}

int ClientSock::Interpreter()
{
    recivedData.ProcessData();
    printf("%s\n", recivedData.requestFile);
    if (recivedData.requestFile[0] == 0)
    {
        printf("NULL\n");
        strcpy(recivedData.requestFile, "send/index.html");
    }
    keep_conection = !strncmp(searchString("Connection: "), "keep-alive", 10);
    if (SendFile(recivedData.requestFile) == -1)
    {
        printf("\x1b[31m I Can't found File\n\x1b[0m");
        SendFile("send/index.html");
    }
    return DEFAULT;
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