#include <time.h>

void swap(int &num1, int &num2)
{
    int temp = num1;
    num1 = num2;
    num2 = temp;
}

void SHAKERSORT(int arr[], int n, int &comparision)
{
    int up = 0,
        down = n - 1,
        hv = 0;
    while (++comparision && up < down)
    {
        for (int i = up; i < down; i++)
        {
            ++comparision;
            if (++comparision && arr[i] > arr[i + 1])
            {
                swap(arr[i], arr[i + 1]);
                hv = i;
            }
        }
        down = hv;
        for (int j = down; j > up; j--)
        {
            ++comparision;
            if (++comparision && arr[j - 1] > arr[j])
            {
                swap(arr[j - 1], arr[j]);
                hv = j;
            }
        }
        up = hv;
    }
}
void ShakerSort(int arr[], int n, int &comparision, double &time)
{
    clock_t start, end;
    comparision = 0;
    time = 0;

    start = clock();
    SHAKERSORT(arr, n, comparision);
    end = clock();

    time = (double)(end - start)/CLOCKS_PER_SEC;
}

void QUICKSORT(int a[], int l, int r, int &comparision)
{
    if (++comparision && l >= r)
        return;
    int i = l, j = r, m = a[(i + j) / 2];
    while (++comparision && i < j)
    {
        while (++comparision && a[i] < m)
            i++;
        while (++comparision && a[j] > m)
            j--;
        if (++comparision && i <= j)
        {
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }
    QUICKSORT(a, l, j, comparision);
    QUICKSORT(a, i, r, comparision);
}

void QuickSort(int a[], int n, int &comparision, double &time)
{
    clock_t start, end;
    comparision = 0;
    time = 0;

    start = clock();
    QUICKSORT(a, 0, n, comparision);
    end = clock();

    time = (double)(end - start) / CLOCKS_PER_SEC;
}

void CountingSort(int a[],int n,int &comparision,double &time)
{
    clock_t start, end;
    comparision = 0;

    // According to randomize code, the elements' range is from 1 to n-1 
    int *flag = new int [n]{0};
    int *res = new int [n];

    start = clock();
    for (int i = 0; ++comparision, i < n; i++) flag[a[i]]++;
    for (int i = 1; ++comparision, i < n; i++) flag[i] += flag[i-1];
    for (int i = 0; ++comparision, i < n; i++) 
    {
        res[flag[a[i]] - 1] = a[i];
        flag[a[i]]--;
    }
    end = clock();

    for (int i = 0; i < n; i++) a[i] = res[i];
    delete flag;
    delete res;

    time = (double) (end - start) / CLOCKS_PER_SEC;
    // Ref: https://www.geeksforgeeks.org/counting-sort/
}
