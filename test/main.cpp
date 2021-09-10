#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
char data[BUFSIZ];
int main()
{
    int fd = ("in.txt", O_RDWR);
    if (fd == -1)
        perror("ERROR");
    printf("%d", fd);
    //read(fd, data, BUFSIZ);
    //printf("%s", data);
    // int close(fd);
    // return 0;
}