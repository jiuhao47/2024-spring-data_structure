#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXSIZE 1000000
typedef int KeyType;
typedef struct RedType
{
    KeyType key;
} RedType;

typedef struct SqList
{
    RedType r[MAXSIZE + 1];
    int length;
} SqList;

void ListDisplay(SqList *L)
{
    for (int i = 1; i <= L->length; i++)
    {
        printf("%d ", L->r[i].key);
    }
    printf("\n");
}
void insert_sort(int *array, int size)
{
    for (int i = 1; i < size; i++)
    {
        int key = array[i];
        int j = i - 1;
        while (j >= 0 && array[j] > key)
        {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

void B_insert_sort(int *array, int size)
{
    for (int i = 1; i < size; i++)
    {
        int key = array[i];
        int low = 0;
        int high = i - 1;
        while (low <= high)
        {
            int mid = (low + high) / 2;
            if (array[mid] > key)
            {
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        for (int j = i - 1; j > low; j--)
        {
            array[j] = array[j - 1];
        }
        array[low] = key;
    }
}
void shellsort(int *array, int length)
{
    int i, j, gap;
    int temp;
    for (gap = length / 2; gap > 0; gap /= 2)
    {
        for (i = gap; i < length; i += 1)
        {
            for (j = i - gap; j >= 0 && array[j] > array[j + gap]; j -= gap)
            {
                temp = array[j + gap];
                array[j + gap] = array[j];
                array[j] = temp;
            }
        }
    }
}

void quicksort(int *array, int low, int high)
{
    if (low < high)
    {
        int i = low;
        int j = high;
        int pivot = array[low];
        while (i < j)
        {
            while (i < j && array[j] >= pivot)
            {
                j--;
            }
            if (i < j)
            {
                array[i++] = array[j];
            }
            while (i < j && array[i] <= pivot)
            {
                i++;
            }
            if (i < j)
            {
                array[j--] = array[i];
            }
        }
        array[i] = pivot;
        quicksort(array, low, i - 1);
        quicksort(array, i + 1, high);
    }
}

void selectsort(int *array, int length)
{
    int i, j, min;
    int temp;
    for (i = 0; i < length - 1; i++)
    {
        min = i;
        for (j = i + 1; j < length; j++)
        {
            if (array[j] < array[min])
            {
                min = j;
            }
        }
        if (min != i)
        {
            temp = array[i];
            array[i] = array[min];
            array[min] = temp;
        }
    }
}

void heapSort(int *a, int n)
{
    int i, temp;
    for (i = n / 2; i > 0; i--)
    {
        int j = i;
        temp = a[j];
        int k = 2 * j;
        while (k <= n)
        {
            if (k < n && a[k] < a[k + 1])
                k++;
            if (temp >= a[k])
                break;
            a[j] = a[k];
            j = k;
            k = 2 * j;
        }
        a[j] = temp;
    }
    for (i = n; i > 1; i--)
    {
        temp = a[1];
        a[1] = a[i];
        a[i] = temp;
        int j = 1;
        temp = a[j];
        int k = 2 * j;
        while (k < i)
        {
            if (k < i - 1 && a[k] < a[k + 1])
                k++;
            if (temp >= a[k])
                break;
            a[j] = a[k];
            j = k;
            k = 2 * j;
        }
        a[j] = temp;
    }
}

void merge(int *a, int low, int mid, int high)
{
    int *temp = (int *)malloc((high - low + 1) * sizeof(int));
    int i = low, j = mid + 1, k = 0;

    while (i <= mid && j <= high)
    {
        if (a[i] <= a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while (i <= mid)
        temp[k++] = a[i++];

    while (j <= high)
        temp[k++] = a[j++];

    for (i = low, k = 0; i <= high;)
        a[i++] = temp[k++];

    free(temp);
}

void mergeSort(int *a, int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        mergeSort(a, low, mid);
        mergeSort(a, mid + 1, high);
        merge(a, low, mid, high);
    }
}

void radixSort(int *a, int n)
{
    int max = a[1];
    for (int i = 2; i <= n; i++)
    {
        if (a[i] > max)
            max = a[i];
    }
    int exp = 1;
    int *temp = (int *)malloc(sizeof(int) * (n + 1));
    int *count = (int *)malloc(sizeof(int) * 10);
    while (max / exp > 0)
    {
        for (int i = 0; i < 10; i++)
            count[i] = 0;
        for (int i = 1; i <= n; i++)
            count[a[i] / exp % 10]++;
        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];
        for (int i = n; i >= 1; i--)
            temp[count[a[i] / exp % 10]--] = a[i];
        for (int i = 1; i <= n; i++)
            a[i] = temp[i];
        exp *= 10;
    }
    free(temp);
    free(count);
}

int main()
{
    clock_t start, end;
    double cpu_time_used;
    int length;
    SqList L;
    // printf("Please enter the length of Sqlist: ");
    scanf("%d", &length);
    while (length > MAXSIZE)
    {
        // printf("The length is too long, please enter again");
        scanf("%d", &length);
    }
    L.length = length;
    int input_mode;
    // printf("Please enter the input mode:\n1 for manual input\n2 for random input\n3 for ordered input\n4 for reversed ordered input\n:");
    scanf("%d", &input_mode);
    if (input_mode == 1)
    {
        // printf("Please enter the elements of Sqlist: \n");
        for (int i = 1; i <= length; i++)
        {
            // printf("%dth:", i);
            scanf("%d", &L.r[i].key);
        }
    }
    else if (input_mode == 2)
    {
        for (int i = 1; i <= length; i++)
        {
            L.r[i].key = rand() % length;
        }
    }
    else if (input_mode == 3)
    {
        for (int i = 1; i <= length; i++)
        {
            L.r[i].key = i;
        }
    }
    else if (input_mode == 4)
    {
        for (int i = 1; i <= length; i++)
        {
            L.r[i].key = length - i;
        }
    }
    else
    {
        // printf("Invalid input mode");
        return 0;
    }
    // ListDisplay(&L);
    int sort_mode;
    // printf("Please enter the sort mode:\n1 for insert sort\n2 for binary insert sort\n:");
    scanf("%d", &sort_mode);
    if (sort_mode == 1)
    {
        start = clock();
        shellsort(&L.r[0].key, L.length + 1);
        end = clock();
        // ListDisplay(&L);
    }
    else if (sort_mode == 2)
    {
        start = clock();
        quicksort(&L.r[0].key, 1, L.length);
        end = clock();
        // ListDisplay(&L);
    }
    else if (sort_mode == 3)
    {
        start = clock();
        selectsort(&L.r[0].key, L.length + 1);
        end = clock();
        // ListDisplay(&L);
    }
    else if (sort_mode == 4)
    {
        start = clock();
        insert_sort(&L.r[1].key, L.length);
        end = clock();
        // ListDisplay(&L);
    }
    else if (sort_mode == 5)
    {
        start = clock();
        B_insert_sort(&L.r[1].key, L.length);
        end = clock();
        // ListDisplay(&L);
    }
    else if (sort_mode == 6)
    {
        start = clock();
        heapSort(&L.r[0].key, L.length);
        end = clock();
        // ListDisplay(&L);
    }
    else if (sort_mode == 7)
    {
        start = clock();
        mergeSort(&L.r[0].key, 1, L.length);
        end = clock();
        // ListDisplay(&L);
    }
    else if (sort_mode == 8)
    {
        start = clock();
        radixSort(&L.r[0].key, L.length);
        end = clock();
        // ListDisplay(&L);
    }
    else
    {
        // printf("Invalid sort mode");
        return 0;
    }
    cpu_time_used = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC;
    printf("%f\n", cpu_time_used);

    /*printf("%s %s Time used: %f ms\n", input_mode == 1 ? "Manual input" : input_mode == 2 ? "Random input"
                                                                      : input_mode == 3   ? "Ordered input"
                                                                                          : "Reversed ordered input",
           sort_mode == 1 ? "Shell sort" : sort_mode == 2 ? "Quick sort"
                                       : sort_mode == 3   ? "Select sort"
                                       : sort_mode == 4   ? "Insert sort"
                                       : sort_mode == 5   ? "Binary insert sort"
                                       : sort_mode == 6   ? "Heap sort"
                                       : sort_mode == 7   ? "Merge sort"
                                                          : "Radix sort",
           cpu_time_used);
    */
}