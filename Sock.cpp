#include "SockClass.h"
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
    int inFile = open(fileName, O_RDONLY);
    fstat(inFile, &stbuf);
    int sendedFileSize = sendfile(thisSocket, inFile, SEEK_SET, BUFSIZ);
    if (sendedFileSize == -1)
    {
        perror("Failed to send message\n");
        close(inFile);
        return -1;
    }
    else
    {
        printf("%d bytes data sended sucessfully! filename : %s\n", sendedFileSize, fileName);
        close(inFile);
        return sendedFileSize;
    }
}

int ClientSock::PutInRecivedData(const char *input)
{
    return strcmp(recivedData, input);
}
ClientSock::ClientSock()
{
}

////////////////////-------------------------//////////////////////////

ServerSock::ServerSock()
{
    thisSocketAdress.sin_family = AF_INET;
    thisSocketAdress.sin_port = htons(PORT);
    if ((thisSocketAdress.sin_addr.s_addr = inet_addr(MYIP)) == -1)
    {
        perror("Wrong IP adress");
        exit(1);
    }
    if (bind(thisSocket, (struct sockaddr *)&thisSocketAdress, sizeof(thisSocketAdress)) == -1)
    {
        perror("Can not Bind");
        exit(1);
    }
    if (listen(thisSocket, 5) == -1)
    {
        perror("listen Fail");
        exit(1);
    }
    printf("Server Open! %s:%u\n\n", MYIP, ntohs(thisSocketAdress.sin_port));
}
/////////////////////////////////////////////////