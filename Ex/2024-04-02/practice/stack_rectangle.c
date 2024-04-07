/**
 * @ IIE, CAS.
 * @ Info  全为1的面积最大的子矩阵
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct Stack
{
    int val;
    struct Stack *next;
} Stack;

void push(Stack **head, int val)
{
    if (!(*head))
    {
        *head = (Stack *)malloc(sizeof(Stack));
        (*head)->val = val;
        (*head)->next = NULL;
    }
    else
    {
        Stack *p = (Stack *)malloc(sizeof(Stack));
        p->val = val;
        p->next = (*head);
        (*head) = p;
    }
}

bool pop(Stack **head, int *val)
{
    if (!(*head))
    {
        return false;
        // Empty Stack
    }
    else
    {
        *val = (*head)->val;
        Stack *p = (*head);
        (*head) = p->next;
        free(p);
        return true;
    }
}
int largestRectangleArea(int *heights, int heightsSize, int heightsColSize)
{
    /*
        for (int i = 0; i < heightsSize; i++)
        {
            printf("%d ", heights[i]);
        }
        printf("\n");
    */
    int maxArea = 0;
    for (int h = 1; h <= heightsColSize; h++)
    {
        for (int j = 0; j < heightsSize; j++)
        {
            if (heights[j] >= h)
            {
                int left = j;
                while (left > 0 && heights[left - 1] >= h)
                {
                    left--;
                }
                int right = j;
                while (right < heightsSize - 1 && heights[right + 1] >= h)
                {
                    right++;
                }
                int area = h * (right - left + 1);
                // printf("area=%d\n", area);
                maxArea = MAX(maxArea, area);
            }
        }
    }
    // printf("maxArea=%d\n", maxArea);
    return maxArea;
}
int maximalRectangle(char **matrix, int matrixSize, int *matrixColSize)
{
    if (matrixSize == 0)
    {
        return 0;
    }
    for (int i = 0; i < matrixSize; i++)
    {
        for (int j = 0; j < matrixColSize[i]; j++)
        {
            matrix[i][j] -= '0';
        }
    }
    int maxArea = 0;
    for (int i = 0; i < matrixSize; i++)
    {
        for (int j = 0; j < matrixColSize[i]; j++)
        {
            if (j > 0)
            {
                matrix[i][j] = matrix[i][j] == 0 ? 0 : matrix[i][j - 1] + 1;
            }
            else
            {
                matrix[i][j] = matrix[i][j];
            }
        }
    }
    /*
    for (int i = 0; i < matrixSize; i++)
    {
        for (int j = 0; j < matrixColSize[i]; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    */
    for (int j = 0; j < matrixColSize[0]; j++)
    {
        int *height = (int *)malloc(sizeof(int) * matrixSize);
        for (int i = 0; i < matrixSize; i++)
        {
            height[i] = matrix[i][j];
        }
        maxArea = MAX(maxArea, largestRectangleArea(height, matrixSize, matrixColSize[0]));
        // printf("maxArea=%d\n", maxArea);
    }

    return maxArea;
    // 省略函数内部实现
}
int main()
{
    int m, n;
    // m为行数，n为列数
    /*
        0 0 0
        0 0 0
    */
    scanf("%d %d", &m, &n);
    char **matrix = (char **)malloc(m * sizeof(char *));
    int *matrixColSize = (int *)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++)
    {
        matrix[i] = (char *)malloc((n + 1) * sizeof(char));
        scanf("%s", matrix[i]);
        matrixColSize[i] = n;
    }
    int maxRectangle = maximalRectangle(matrix, m, matrixColSize);
    printf("%d", maxRectangle);
    return 0;
}