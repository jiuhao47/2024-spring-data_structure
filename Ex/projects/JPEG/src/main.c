#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "definations.h"
#include "structures.h"
bool file_read(unsigned char **buffer, int *fileSizeOut);
void Piece(unsigned char *array, int start, int end, char *piece);
int main()
{
    unsigned char *buffer = NULL;
    int fileSize;
    file_read(&buffer, &fileSize);
    for (int i = 0; i < fileSize; i++)
    {
        if (buffer[i] == 0xff)
        {
            if (buffer[i + 1] == MARKER_APP0 || buffer[i + 1] == MARKER_DQT || buffer[i + 1] == MARKER_SOF0)
            {
                printf("ff %x\n", buffer[i + 1]);
                int length = ((short)buffer[i + 2] << 8) + ((short)buffer[i + 3]);
                for (int j = 0; j < length; j++)
                {
                    printf("%x ", buffer[i + 4 + j]);
                }
                printf("\n");
            }
        }
    }
    free(buffer);
    return 0;
}

// 以char(8位)为从array中start位置读取length长度的字符，并存储到piece中
void Piece(unsigned char *array, int start, int length, char *piece)
{
    for (int i = 0; i < length; i++)
    {
        piece[i] = array[i + start];
    }
    piece[length] = '\0';
}

// 从指定文件（FILE_PLACE）中读取内容至缓冲区buffer
bool file_read(unsigned char **buffer, int *fileSizeOut)
{
    FILE *file = fopen(FILE_PLACE, "rb");
    if (file == NULL)
    {
        printf("Failed to open file\n");
        return false;
    }
    fseek(file, 0, SEEK_END);    // 将文件位置指针移动到文件的末尾
    long fileSize = ftell(file); // 获取当前的文件位置，即文件的总大小
    fseek(file, 0, SEEK_SET);    // 将文件位置指针移动回文件的开始
    *fileSizeOut = fileSize;
    printf("File size: %ld bytes\n", fileSize);
    *buffer = (unsigned char *)malloc(sizeof(unsigned char) * fileSize);
    size_t bytesRead = fread(*buffer, 1, fileSize, file);
    printf("Read %zu bytes\n", bytesRead);
    fclose(file);
    return true;
}