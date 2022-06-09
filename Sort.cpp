#include <time.h>
#include <math.h>
#include <iostream>
#include <algorithm>

using namespace std;

void ShakerSort(int arr[], int n, int &comparision, double &time)
{
    int up = 0,
        down = n - 1,
        hv = 0; // store the last position of each swap.

    clock_t start, end;
    comparision = 0;
    time = 0;

    start = clock();
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
    end = clock();
    time = (double)(end - start) / CLOCKS_PER_SEC;
}

void createGap(int n, int gap[], int &gap_num, int &comparision)
{
    gap[0] = 1;
    for (int i = 1; gap[i - 1] < n; i++)
    {
        ++comparision;
        gap[i] = 3 * gap[i - 1] + 1;
        gap_num++;
    }
}

void ShellSort(int a[], int n, int &comparision, double &time)
{
    clock_t start, end;
    comparision = 0, time = 0;

    int *gap = new int[n],
        gap_num = 0;
    start = clock();
    createGap(n, gap, gap_num, comparision);

    int p = 0,
        j = 0,
        t = 0,
        x = 0;
    for (p = 0; p < gap_num; p++)
    {
        ++comparision;
        t = gap[p];
        for (int i = t; i < n; i++)
        {
            ++comparision;
            x = a[i];
            j = i;
            while (++comparision && ++comparision && x < a[j - t] && j >= t)
            {
                a[j] = a[j - t];
                j = j - t;
            }
            a[j] = x;
        }
    }
    delete[] gap;

    end = clock();
    time = (double)(end - start) / CLOCKS_PER_SEC;
}

void QUICKSORT(int a[], int l, int r, int &comparision)
{
    int i = l - 1, j = r + 1, m = a[(i + j) / 2];
    do
    {
        do
            i++;
        while (++comparision && a[i] < m);
        do
            j--;
        while (++comparision && a[j] > m);
        swap(a[i], a[j]);
    } while (++comparision && i < j);
    swap(a[i], a[j]);
    if (++comparision && i == j)
    {
        i++;
        j--;
    }
    if (++comparision && l < j)
        QUICKSORT(a, l, j, comparision);
    if (++comparision && i < r)
        QUICKSORT(a, i, r, comparision);
}

void QuickSort(int a[], int n, int &comparision, double &time)
{
    clock_t start, end;
    comparision = 0;
    time = 0;

    start = clock();
    QUICKSORT(a, 0, n - 1, comparision);
    end = clock();

    time = (double)(end - start) / CLOCKS_PER_SEC;
}

void CountingSort(int *&a, int n, int &comparision, double &time)
{
    clock_t start, end;
    comparision = 0;

    // According to randomize code, the elements' range is from 1 to n-1
    int *flag = new int[n]{0};
    int *res = new int[n];

    start = clock();
    for (int i = 0; ++comparision, i < n; i++)
        flag[a[i]]++;
    for (int i = 1; ++comparision, i < n; i++)
        flag[i] += flag[i - 1];
    for (int i = 0; ++comparision, i < n; i++)
    {
        res[flag[a[i]] - 1] = a[i];
        flag[a[i]]--;
    }

    delete a;
    a = res;
    delete flag;

    end = clock();
    time = (double)(end - start) / CLOCKS_PER_SEC;
    // Ref: https://www.geeksforgeeks.org/counting-sort/
}

void RadixSort(int *&a, int n, int &comparision, double &time)
{
    clock_t start, end;
    comparision = 0;

    start = clock();
    for (int i = 1; ++comparision, i <= pow(10, (int)log10(n) + 1); i *= 10)
    {
        int *res = new int[n]{0};
        int flag[10] = {0};

        for (int j = 0; ++comparision, j < n; j++)
            flag[(a[j] / i) % 10]++;
        for (int j = 1; ++comparision, j < 10; j++)
            flag[j] += flag[j - 1];
        for (int j = n - 1; ++comparision, j >= 0; j--)
        {
            res[flag[(a[j] / i) % 10] - 1] = a[j];
            flag[(a[j] / i) % 10]--;
        }

        delete a;
        a = res;
    }
    end = clock();

    time = (double)(end - start) / CLOCKS_PER_SEC;
    // Ref: https://www.geeksforgeeks.org/radix-sort/
}
void findMaxMin(int arr[], int n, int &comparision, int &max, int &minVal)
{

    for (int i = 0; i < n; i++)
    {
        ++comparision;
        if (++comparision && arr[i] > arr[max])
            max = i;
        if (++comparision && arr[i] < minVal)
            minVal = arr[i];
    }
}
void FlashSort(int arr[], int n, int &comparision, double &time)
{
    clock_t start, end;
    comparision = 0, time = 0;

    start = clock();

    int max = 0,
        minVal = arr[0];

    // Find min value and index of max value
    findMaxMin(arr, n, comparision, max, minVal);

    // Create bucket to store value
    int bucketNum = (int)(0.45 * n);
    int *bucket = new int[bucketNum];
    // Initialize value of bucket with 0
    for (int i = 0; i < bucketNum; i++)
    {
        ++comparision;
        bucket[i] = 0;
    }

    const float c = (bucketNum - 1) / (arr[max] - minVal);
    //Count the number value of each bucket
    for (int i = 0; i < n; i++)
    {
        ++comparision;
        int temp = int(c * (arr[i] - minVal));
        bucket[temp] += 1;
    }
    //Calc the lastest index of each bucket
    for (int i = 1; i < bucketNum; i++)
    {
        ++comparision;
        bucket[i] += bucket[i - 1];
    }

    swap(arr[max], arr[0]);

    int move = 0, j = 0, flash, k = bucketNum - 1;
    // permutation
    while (++comparision && move < (n - 1))
    {
        while (++comparision && j > (bucket[k] - 1))
        {
            ++j;
            k = int(c * (arr[j] - minVal));
        }

        if (++comparision && k < 0)
            break;
        flash = arr[j];
        while (++comparision && j != bucket[k])
        {
            k = int(c * (flash - minVal));
            --bucket[k];
            swap(bucket[k], flash);
            ++move;
        }
    }
    //Insertion sort
    for (int idx = 1; idx < n; idx++)
    {
        ++comparision;
        int hold = arr[idx];
        int idx_temp = idx - 1;
        while (++comparision && ++comparision && idx_temp >= 0 && arr[idx_temp] > hold)
        {
            arr[idx_temp + 1] = arr[idx_temp];
            idx_temp--;
        }
        arr[idx_temp + 1] = hold;
    }
    delete[] bucket;

    end = clock();

    time = (double)(end - start) / CLOCKS_PER_SEC;
}