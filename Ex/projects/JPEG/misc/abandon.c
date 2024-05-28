// 以char(8位)为从array中start位置读取length长度的字符，并存储到piece中
void Piece(unsigned char *array, int start, int length, char *piece)
{
    for (int i = 0; i < length; i++)
    {
        piece[i] = array[i + start];
    }
    piece[length] = '\0';
}