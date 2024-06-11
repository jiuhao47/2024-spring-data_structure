#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxlen 25
// �ڵ�Ľṹ
typedef struct HTNode
{
    char data;
    int weight; // Ȩ��
    int parent;
    int lchild;
    int rchild;
    struct HTNode *next;
} HTNode, *HuffmanTree;

// �ַ�
typedef struct
{
    char data;
    int weight;
} Charater;
// ����������Ľṹ
typedef struct
{
    char data;
    char code[maxlen];
} *HuffmanCode;

HTNode *Search(HTNode *head, int x);
void CreateHuffmanTree(HuffmanTree *HT, Charater weightin[], int n);
void HuffmanCoding(HuffmanTree HT, HuffmanCode *HC, int n);
void Select(HuffmanTree HT, int *s1, int *s2, int n);
void DestroyHuffmanTree(HuffmanTree *HT, int n);
void DertroyHuffmanCode(HuffmanCode *HC, int n);

// ���ҹ��������ĵ�x���ڵ�(������ͷ�ڵ㣬��HT[x])
HTNode *Search(HTNode *head, int x)
{
    int i;
    HTNode *nodex = head; // ָHT[x]����ڵ�
    for (i = 0; i < x; i++)
    { // ��ͷ�ڵ�head�����ҵ�����head�ĵ�x���ڵ�
        nodex = nodex->next;
    }
    return nodex;
}

// �������������
// weightin������n���ַ���Ȩ�أ������������HT
void CreateHuffmanTree(HuffmanTree *HT, Charater weightin[], int n)
{
    if (n < 1)
    { // �ַ���С��1ʱ�����˳�
        printf("NO CHARACTER\n");
        return;
    }
    int i;
    int m = 2 * n - 1; // ����Huffman���Ľڵ���Ŀ

    // ��ʼ������������
    HTNode *head = (HTNode *)malloc(sizeof(HTNode)); // ����������ͷ�ڵ�
    (*HT) = head;
    head->next = NULL;
    head->data = '\0';
    head->parent = -1;
    head->lchild = 0;
    head->rchild = 0;

    for (i = 1; i <= m; i++)
    { // �����ڵ������������Ŀռ�,������ʼ�Ĺ�������
        HTNode *p = (HTNode *)malloc(sizeof(HTNode));
        (*HT)->next = p;
        (*HT) = p;
        if (i <= n)
        {                                       // Ҷ�ӽڵ�HT[1]-HT[n]
            p->weight = weightin[i - 1].weight; // Ҷ�ӽڵ��Ȩ�ظ�ֵ
            p->data = weightin[i - 1].data;     // Ҷ�ӽڵ���ַ���ֵ
            printf("i%d:%c %d\n", i, p->data, p->weight);
        }
        else
        {                  // �ڲ��ڵ�HT[n+1]-HT[m]
            p->weight = 0; // ���ڲ��ڵ��Ȩ�س�ʼ��Ϊ0
            p->data = '\0';
            printf("i%d:%c %d\n", i, p->data, p->weight);
        }
        p->parent = 0; // ��ʼ��˫�׽ڵ�
        p->lchild = 0; // ��ʼ�����ӽڵ�
        p->rchild = 0; // ��ʼ���Һ��ӽڵ�
        p = NULL;      // ��������ָ��
    }
    (*HT) = head;
    // ��������������
    for (i = n + 1; i <= m; i++)
    { // �����ڲ��ڵ�HT[n+1]-HT[m]
        int s1, s2;
        Select((*HT), &s1, &s2, i - 1);                  // ��HT[1]-HT[i-1]ѡ��parentΪ0��Ȩ����С�������ڵ㣬�����Ϊs1��s2
        HTNode *nodes1 = Search((*HT), s1);              // ����HT[s1]����ڵ�
        HTNode *nodes2 = Search((*HT), s2);              // ����HT[s2]����ڵ�
        HTNode *nodei = Search((*HT), i);                // ����HT[i]����ڵ�
        nodes1->parent = i;                              // ����s1�ڵ�ĸ��ڵ�Ϊi
        nodes2->parent = i;                              // ����s2�ڵ�ĸ��ڵ�Ϊi
        nodei->lchild = s1;                              // ����i�ڵ������Ϊs1
        nodei->rchild = s2;                              // ����i�ڵ���Һ���Ϊs2
        nodei->weight = nodes1->weight + nodes2->weight; // ����i�ڵ��ȨֵΪs1��s2��Ȩֵ֮��
    }
}

// ������������룺
// ���ݹ�������HT���������������HC
void HuffmanCoding(HuffmanTree HT, HuffmanCode *HC, int n)
{
    // �������������������������
    (*HC) = (HuffmanCode)malloc((n + 1) * sizeof(HuffmanCode *)); // ����洢����������Ŀռ�
    int i, j;
    char codei[n]; // ��¼HT[i]�Ĺ���������
    char temp[n];  // ��Ϊ����׷��ʱ�����������ǴӺ���ǰ��ģ�����strcat�����ǽ����ַ������ӵ�ԭ�ַ���ĩβ�������Ҫһ���ַ�����Ϊת��
    HTNode *node, *parent;
    for (i = 1; i <= n; ++i)
    {          // ����HT[1]-HT[n]��������Ҷ�ӽڵ�
        j = i; // ��j��whileѭ������HT[i]����׷�ݵ����ڵ�Ϊֹ
        strcpy(codei, "");
        node = Search(HT, j);
        (*HC)[i].data = node->data; // HT[i]���ַ�
        while (node->parent)
        { // HT[j]�и��ڵ㣬����δ׷�ݵ����ڵ�
            parent = Search(HT, node->parent);
            if (parent->lchild == j)
            { // HT[j]���丸�ڵ������
                temp[0] = '0';
                temp[1] = '\0';
                strcat(temp, codei);
                strcpy(codei, temp);
            }
            else if (parent->rchild == j)
            { // HT[j]���丸�ڵ���Һ���
                temp[0] = '1';
                temp[1] = '\0';
                strcat(temp, codei);
                strcpy(codei, temp);
            }
            j = node->parent;
            node = Search(HT, j);
        }
        strcpy((*HC)[i].code, codei);
    }
}

// ��HT[1]-HT[x]ѡ��������δ��������Ȩ����С�������ڵ㲢����Ÿ���s1,s2��
// s1��Ȩ����С�Ľڵ����ţ�s2��Ȩ�صڶ�С�Ľڵ�����
void Select(HuffmanTree HT, int *s1, int *s2, int x)
{
    int i, m;
    int k = 0;
    for (i = 1; i <= x; i++)
    {
        HTNode *nodei = Search(HT, i); // ����HT[i]����ڵ�
        if (nodei->parent == 0)
        { // ��ǰ�ڵ���˫��
            if (k == 0)
            {
                (*s1) = i;
                k++;
            }
            else if (k == 1)
            {
                if ((nodei->weight > 0) && (nodei->weight <= (Search(HT, (*s1)))->weight))
                {
                    m = (*s1);
                    (*s2) = m; // ����s1��s2
                    (*s1) = i;
                }
                else if (nodei->weight > 0)
                {
                    (*s2) = i;
                }
                k++;
            }
            else
            {
                if ((nodei->weight > 0) && (nodei->weight <= (Search(HT, (*s1)))->weight))
                { // ��ǰ�ڵ��Ȩ�ر�s1��Ȩ�ػ�С����һ��С��˵����ǰ�ڵ���Ȩ����С�Ľڵ�
                    m = (*s1);
                    (*s2) = m; // ����s1��s2
                    (*s1) = i;
                }
                else if ((nodei->weight > 0) && (nodei->weight < (Search(HT, (*s2)))->weight))
                { // ��ǰ�ڵ��Ȩ�ر�s1��Ȩ�ش��Ǳ�s2��Ȩ��С��˵����ǰ�ڵ���Ȩ�ش�С�Ľڵ�
                    (*s2) = i;
                }
            }
        }
    }
}

//// �ͷŹ���������ռ�Ŀռ�
void DestroyHuffmanTree(HuffmanTree *HT, int n)
{
    int i;
    int m = 2 * n - 1;
    HTNode *p;
    for (i = 0; i <= m; i++)
    {
        printf("%d ha\n", i);
        p = (*HT);
        printf("hb\n");
        (*HT) = (*HT)->next;
        printf("hc\n");
        free(p);
        printf("hd\n");
    }
    (*HT) = NULL;
};

// �ͷŹ�����������ռ�Ŀռ�
void DertroyHuffmanCode(HuffmanCode *HC, int n)
{
    printf("Delete HC\n");
    free((*HC));
    printf("Delete Success\n");
};

int main()
{
    int n = 8;
    int m = 2 * n - 1;
    int i;
    Charater weightin[] = {{'a', 7}, {'b', 19}, {'c', 2}, {'d', 6}, {'e', 32}, {'f', 3}, {'g', 21}, {'h', 10}};
    HuffmanTree HT;
    HuffmanCode HC;
    CreateHuffmanTree(&HT, weightin, n);
    printf("����������\n");
    for (i = 1; i <= m; i++)
    {
        printf("%c:%d\n", (Search(HT, i))->data, (Search(HT, i))->weight);
    }
    HuffmanCoding(HT, &HC, n);
    printf("����������:\n");
    for (i = 1; i <= n; i++)
    {
        printf("%c:%s\n", HC[i].data, HC[i].code);
    }
    DestroyHuffmanTree(&HT, n);
    DertroyHuffmanCode(&HC, n);
    return 0;
};
