typedef struct SOF
{
    unsigned char marker;            // 标记代码
    unsigned short length;           // 数据长度
    unsigned char precision;         // 精度
    unsigned short height;           // 图像高度
    unsigned short width;            // 图像宽度
    unsigned char components;        // 颜色分量数
    unsigned char component_info[0]; // 颜色分量信息
} SOF;

typedef struct SOS
{
    unsigned char marker;            // 标记代码
    unsigned short length;           // 数据长度
    unsigned char components;        // 颜色分量数
    unsigned char start_spectral;    // 起始光谱选择
    unsigned char end_spectral;      // 结束光谱选择
    unsigned char approx;            // 逼近值
    unsigned char component_info[0]; // 颜色分量信息
} SOS;

typedef struct APP0
{
    unsigned short marker;       // 标记代码
    unsigned short length;       // 数据长度
    unsigned char identifier[5]; // 标识符
    unsigned short version;      // 版本号
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

typedef struct DHT
{
    unsigned char marker;   // 标记代码
    unsigned short length;  // 数据长度
    unsigned char table[0]; // 霍夫曼表
} DHT;

typedef struct HuffmanTree
{
    unsigned char value; // 值
    struct HuffmanTree *left;
    struct HuffmanTree *right;
} HuffmanTree;

typedef struct Stack
{
    int data;
    struct Stack *next;
} Stack;