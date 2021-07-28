#include "Customio.h"
int cus::Custumio::InputFileInSendBuffer(const char *fileName)
{
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        perror("File Reading Error");
        return 0;
    }
    for (int i = 0; i < BUFSIZ; i++)
    {
        fscanf(file, "%c", &buffer[i]);
    }
    fclose(file);
    return 1;
}