struct SOF
{
    unsigned char marker;                // 标记代码
    unsigned short length;               // 数据长度
    unsigned char precision;             // 精度
    unsigned short height;               // 图像高度
    unsigned short width;                // 图像宽度
    unsigned char components;            // 颜色分量数
    unsigned char component_id[3];       // 颜色分量id
    unsigned char sampling_factor[3];    // 颜色水平垂直采量因子
    unsigned char quantization_table[3]; // 当前分量使用的量化表ID
} SOF;

typedef struct APP0
{
    unsigned char marker;        // 标记代码
    unsigned short length;       // 数据长度
    unsigned char identifier[5]; // 标识符
    unsigned char version[2];    // 版本号
    unsigned char unit;          // 密度单位
    unsigned short x_density;    // 水平像素密度
    unsigned short y_density;    // 垂直像素密度
    unsigned char x_thumbnail;   // 缩略图水平像素数
    unsigned char y_thumbnail;   // 缩略图垂直像素数
    unsigned char thumbnail[0];  // 缩略图数据
} APP0;

typedef struct APPn
{
    unsigned char marker;  // 标记代码
    unsigned short length; // 数据长度
    unsigned char data[0]; // 数据
} APPn;

typedef struct DQT
{
    unsigned char marker;   // 标记代码
    unsigned short length;  // 数据长度
    unsigned char table[0]; // 量化表

} DQT;