#include <time.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <chrono>

using namespace std;

void ShakerSort(int arr[], int n, int &comparison, double &time)
{
    int up = 0,
        down = n - 1,
        hv = 0; // store the last position of each swap.

    clock_t start, end;
    comparison = 0;
    time = 0;

    start = clock();
    while (++comparison && up < down)
    {
        for (int i = up;++comparison, i < down; i++)
        {
            if (++comparison && arr[i] > arr[i + 1])
            {
                swap(arr[i], arr[i + 1]);
                hv = i;
            }
        }
        down = hv;
        for (int j = down;++comparison, j > up; j--)
        {
            if (++comparison && arr[j - 1] > arr[j])
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

void createGap(int n, int gap[], int &gap_num, int &comparison)
{
    gap[0] = 1;
    for (int i = 1; ++comparison, gap[i - 1] < n; i++)
    {
        gap[i] = 3 * gap[i - 1] + 1;
        gap_num++;
    }
}

void ShellSort(int a[], int n, int &comparison, double &time)
{
    clock_t start, end;
    comparison = 0, time = 0;

    int *gap = new int[n],
        gap_num = 0;
    start = clock();
    createGap(n, gap, gap_num, comparison);

    int p = 0,
        j = 0,
        t = 0,
        x = 0;
    for (p = 0;++comparison, p < gap_num; p++)
    {
        t = gap[p];
        for (int i = t;++comparison, i < n; i++)
        {
            x = a[i];
            j = i;
            while (++comparison && ++comparison && x < a[j - t] && j >= t)
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

void QUICKSORT(int a[], int l, int r, int &comparison)
{
    int i = l - 1, j = r + 1, m = a[(i + j) / 2];
    do
    {
        do
            i++;
        while (++comparison && a[i] < m);
        do
            j--;
        while (++comparison && a[j] > m);
        swap(a[i], a[j]);
    } while (++comparison && i < j);
    swap(a[i], a[j]);
    if (++comparison && i == j)
    {
        i++;
        j--;
    }
    if (++comparison && l < j)
        QUICKSORT(a, l, j, comparison);
    if (++comparison && i < r)
        QUICKSORT(a, i, r, comparison);
}

void QuickSort(int a[], int n, int &comparison, double &time)
{
    clock_t start, end;
    comparison = 0;
    time = 0;

    start = clock();
    QUICKSORT(a, 0, n - 1, comparison);
    end = clock();

    time = (double)(end - start) / CLOCKS_PER_SEC;
}

void CountingSort(int *&a, int n, int &comparison, double &time)
{
    clock_t start, end;
    comparison = 0;

    // According to randomize code, the elements' range is from 1 to n-1
    int *flag = new int[n]{0};
    int *res = new int[n];

    start = clock();
    for (int i = 0; ++comparison, i < n; i++)
        flag[a[i]]++;
    for (int i = 1; ++comparison, i < n; i++)
        flag[i] += flag[i - 1];
    for (int i = 0; ++comparison, i < n; i++)
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

void RadixSort(int *&a, int n, int &comparison, double &time)
{
    clock_t start, end;
    comparison = 0;

    start = clock();
    for (int i = 1; ++comparison, i <= pow(10, (int)log10(n) + 1); i *= 10)
    {
        int *res = new int[n]{0};
        int flag[10] = {0};

        for (int j = 0; ++comparison, j < n; j++)
            flag[(a[j] / i) % 10]++;
        for (int j = 1; ++comparison, j < 10; j++)
            flag[j] += flag[j - 1];
        for (int j = n - 1; ++comparison, j >= 0; j--)
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
void findMaxMin(int arr[], int n, int &comparison, int &max, int &minVal)
{

    for (int i = 0;++comparison, i < n; i++)
    {
        if (++comparison && arr[i] > arr[max])
            max = i;
        if (++comparison && arr[i] < minVal)
            minVal = arr[i];
    }
}
void FlashSort(int arr[], int n, int &comparison, double &time)
{
    clock_t start, end;
    comparison = 0, time = 0;

    start = clock();

    int max = 0,
        minVal = arr[0];

    // Find min value and index of max value
    findMaxMin(arr, n, comparison, max, minVal);

    // Create bucket to store value
    int bucketNum = (int)(0.45 * n);
    int *bucket = new int[bucketNum];
    // Initialize value of bucket with 0
    for (int i = 0;++comparison, i < bucketNum; i++)
    {
        bucket[i] = 0;
    }

    const float c = (bucketNum - 1) / (arr[max] - minVal);
    //Count the number value of each bucket
    for (int i = 0;++comparison, i < n; i++)
    {
        int temp = int(c * (arr[i] - minVal));
        bucket[temp] += 1;
    }
    //Calc the lastest index of each bucket
    for (int i = 1;++comparison, i < bucketNum; i++)
    {
        bucket[i] += bucket[i - 1];
    }

    swap(arr[max], arr[0]);

    int move = 0, j = 0, flash, k = bucketNum - 1;
    // permutation
    while (++comparison && move < (n - 1))
    {
        while (++comparison && j > (bucket[k] - 1))
        {
            ++j;
            k = int(c * (arr[j] - minVal));
        }

        if (++comparison && k < 0)
            break;
        flash = arr[j];
        while (++comparison && j != bucket[k])
        {
            k = int(c * (flash - minVal));
            --bucket[k];
            swap(bucket[k], flash);
            ++move;
        }
    }
    //Insertion sort
    for (int idx = 1;++comparison, idx < n; idx++)
    {
        int hold = arr[idx];
        int idx_temp = idx - 1;
        while (++comparison && ++comparison && idx_temp >= 0 && arr[idx_temp] > hold)
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

void buildHeap(int arr[], int n, int i, int &comparison, double &time){
    int max = i;
    int l = i * 2;
    int r = (i * 2) + 1;
    
    // find node has max value
    if(++comparison && l < n && ++comparison && arr[l] > arr[max]) max = l;
    if(++comparison && r < n && ++comparison && arr[r] > arr[max]) max = r;

    if(++comparison && max != i){ // swap max to parent, calling recursive
        swap(arr[max], arr[i]);
        buildHeap(arr, n, max, comparison, time); // recursive to child node
    }
}

void HeapSort(int arr[], int sz, int &comparison, double &time){
    comparison = 0;
    time = 0;

    clock_t start, end;
    start = clock();

    
    for(int i = (sz / 2) - 1; ++comparison && i >= 0; i--){ // array has n elements -> has n/2 parent element
        buildHeap(arr, sz, i, comparison, time);
    }
    for(int j = sz - 1; ++comparison && j > 0; j--){
        swap(arr[0], arr[j]);
        buildHeap(arr, j, 0, comparison, time);
    }

    end = clock();
    time = (double)(end - start) / CLOCKS_PER_SEC;
}

void BubbleSort(int arr[], int sz, int &comparison, double &time){
    comparison = 0;
    time = 0;

    clock_t start, end;
    start = clock();

    for(int i = 0; ++comparison && i < sz-1; i++){
        for(int j = sz-1; ++comparison && j > i; j--){
            if(++comparison && arr[j] < arr[j-1]) swap(arr[j], arr[j-1]);
        }
    }

    end = clock();
    time = (double)(end - start) / CLOCKS_PER_SEC;
}

void InsertionSort(int arr[], int sz, int &comparison, double &time){
    comparison = 0;
    time = 0;

    int i, j;
    int key;

    clock_t start, end;
    start = clock();

    for(int i = 1; ++comparison && i < sz; i++){
        key = arr[i];
        j = i - 1;

        while( ++comparison && j >= 0 && ++comparison && arr[j] > key){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }

    end = clock();
    time = (double)(end - start) / CLOCKS_PER_SEC;
}