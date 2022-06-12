#include <time.h>
#include <math.h>
#include <iostream>
#include <algorithm>

using namespace std;

void ShakerSort_time(int arr[], int n, double &time)
{
    clock_t start, end;

    start = clock();

    int up = 0,
        down = n - 1,
        hv = 0; // store the last position of each swap.

    while (up < down)
    {
        for (int i = up; i < down; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                swap(arr[i], arr[i + 1]);
                hv = i;
            }
        }
        down = hv;
        for (int j = down; j > up; j--)
        {
            if (arr[j - 1] > arr[j])
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

void createGap(int n, int gap[], int &gap_num)
{
    gap[0] = 1;
    for (int i = 1; gap[i - 1] < n; i++)
    {
        gap[i] = 3 * gap[i - 1] + 1;
        gap_num++;
    }
}

void ShellSort_time(int a[], int n, double &time)
{
    clock_t start, end;

    start = clock();

    int *gap = new int[n],
        gap_num = 0;

    createGap(n, gap, gap_num);

    int p = 0,
        j = 0,
        t = 0,
        x = 0;
    for (p = 0; p < gap_num; p++)
    {
        t = gap[p];
        for (int i = t; i < n; i++)
        {
            x = a[i];
            j = i;
            while (x < a[j - t] && j >= t)
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

void QUICKSORT(int a[], int l, int r)
{
    int i = l - 1, j = r + 1, m = a[(i + j) / 2];
    do
    {
        do
            i++;
        while (a[i] < m);
        do
            j--;
        while (a[j] > m);
        swap(a[i], a[j]);
    } while (i < j);
    swap(a[i], a[j]);
    if (i == j)
    {
        i++;
        j--;
    }
    if (l < j)
        QUICKSORT(a, l, j);
    if (i < r)
        QUICKSORT(a, i, r);
}

void QuickSort_time(int a[], int n, double &time)
{
    clock_t start, end;

    start = clock();
    QUICKSORT(a, 0, n - 1);
    end = clock();

    time = (double)(end - start) / CLOCKS_PER_SEC;
}

void CountingSort_time(int *&a, int n, double &time)
{
    clock_t start, end;

    start = clock();

    // According to randomize code, the elements' range is from 1 to n-1
    int *flag = new int[n]{0};
    int *res = new int[n];

    for (int i = 0; i < n; i++)
        flag[a[i]]++;
    for (int i = 1; i < n; i++)
        flag[i] += flag[i - 1];
    for (int i = 0; i < n; i++)
    {
        res[flag[a[i]] - 1] = a[i];
        flag[a[i]]--;
    }

    delete[] a;
    a = res;
    delete flag;

    end = clock();

    time = (double)(end - start) / CLOCKS_PER_SEC;
    // Ref: https://www.geeksforgeeks.org/counting-sort/
}

void RadixSort_time(int *&a, int n, double &time)
{
    clock_t start, end;

    start = clock();

    int *res = new int[n]{0};

    for (int i = 1; n / i > 0; i *= 10)
    {
        int flag[10] = {0};

        for (int j = 0; j < n; j++)
            flag[(a[j] / i) % 10]++;
        for (int j = 1; j < 10; j++)
            flag[j] += flag[j - 1];
        for (int j = n - 1; j >= 0; j--)
        {
            res[flag[(a[j] / i) % 10] - 1] = a[j];
            flag[(a[j] / i) % 10]--;
        }
        int *temp = a;
        a = res;
        res = temp;
        fill(res,res + n,0);
    }
    delete[] res;

    end = clock();

    time = (double)(end - start) / CLOCKS_PER_SEC;
    // Ref: https://www.geeksforgeeks.org/radix-sort/
}

void findMaxMin(int arr[], int n, int &max, int &minVal)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > arr[max])
            max = i;
        if (arr[i] < minVal)
            minVal = arr[i];
    }
}

void FlashSort_time(int arr[], int n, double &time)
{
    clock_t start, end;

    start = clock();

    int max = 0,
        minVal = arr[0];

    // Find min value and index of max value
    findMaxMin(arr, n, max, minVal);

    // Create bucket to store value
    int bucketNum = floorf((0.125 * n) * 100) / 100;
    int *bucket = new int[bucketNum];
    // Initialize value of bucket with 0
    for (int i = 0; i < bucketNum; i++)
    {
        bucket[i] = 0;
    }

    const float c = (bucketNum - 1.0) / (arr[max] - minVal);
    // Count the number value of each bucket
    for (int i = 0; i < n; i++)
    {
        int temp = floorf((c * (arr[i] - minVal)) * 100) / 100;
        bucket[temp] += 1;
    }
    // Calc the lastest index of each bucket
    for (int i = 1; i < bucketNum; i++)
    {
        bucket[i] += bucket[i - 1];
    }

    swap(arr[max], arr[0]);

    int move = 0, j = 0, flash, k = bucketNum - 1;
    // permutation
    while (move < (n - 1))
    {
        while (j > (bucket[k] - 1))
        {
            ++j;
            k = floorf((c * (arr[j] - minVal) * 100)) / 100;
        }

        if (k < 0)
            break;
        flash = arr[j];
        while (j != bucket[k])
        {
            k = floorf((c * (flash - minVal)) * 100) / 100;
           	int t;
			int hold = arr[t = --bucket[k]];
			arr[t] = flash;
			flash = hold;
			++move;
        }
    }
    // Insertion sort
    for (int idx = 1; idx < n; idx++)
    {
        int hold = arr[idx];
        int idx_temp = idx - 1;
        while (idx_temp >= 0 && arr[idx_temp] > hold)
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

void buildHeap(int arr[], int n, int i)
{
    int max = i;
    int l = i * 2;
    int r = (i * 2) + 1;

    // find node has max value
    if (l < n && arr[l] > arr[max])
        max = l;
    if (r < n && arr[r] > arr[max])
        max = r;

    if (max != i)
    { // swap max to parent, calling recursive
        swap(arr[max], arr[i]);
        buildHeap(arr, n, max); // recursive to child node
    }
}

void HeapSort_time(int arr[], int sz, double &time)
{
    clock_t start, end;

    start = clock();

    for (int i = (sz / 2) - 1; i >= 0; i--)
    { // array has n elements -> has n/2 parent element
        buildHeap(arr, sz, i);
    }
    for (int j = sz - 1; j > 0; j--)
    {
        swap(arr[0], arr[j]);
        buildHeap(arr, j, 0);
    }

    end = clock();
    time = (double)(end - start) / CLOCKS_PER_SEC;
}

void BubbleSort_time(int arr[], int sz, double &time)
{
    clock_t start, end;

    start = clock();

    for (int i = 0; i < sz - 1; i++)
    {
        for (int j = sz - 1; j > i; j--)
        {
            if (arr[j] < arr[j - 1])
                swap(arr[j], arr[j - 1]);
        }
    }

    end = clock();
    time = (double)(end - start) / CLOCKS_PER_SEC;
}

void InsertionSort_time(int arr[], int sz, double &time)
{
    clock_t start, end;

    start = clock();

    int i, j;
    int key;

    for (int i = 1; i < sz; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }

    end = clock();
    time = (double)(end - start) / CLOCKS_PER_SEC;
}
void SelectionSort_time(int arr[], int n, double &time){
    clock_t start, end;
    time = 0;

    start = clock();
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min])
                min = j;
            if (min != i && j == n - 1) {
                int temp = arr[min];
                arr[min] = arr[i];
                arr[i] = temp;
            }
        }
    }
    end = clock();

    time = (double)(end - start) / CLOCKS_PER_SEC;
}
void MERGE(int arr[], int l, int m, int r){
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int* Lrr = new int[n1];
    int* Rrr = new int[n2];
    for (i = 0; i < n1; i++){
        Lrr[i] = arr[l + i];
    }
    for (j = 0; j < n2; j++){
        Rrr[j] = arr[m + j + 1];
    }
    i = 0, j = 0, k = l;
    while ((i < n1) && (j < n2)){
        arr[k++] = ((Lrr[i] <= Rrr[j]) ? Lrr[i++] : Rrr[j++]);
    }
    while (i < n1){
        arr[k++] = Lrr[i++];
    }
    while (j < n2){
        arr[k++] = Rrr[j++];
    }
    delete[]Lrr;
    delete[]Rrr;
}
void MERGESORT(int arr[], int l, int r){
    if (l < r){
        int m = l + (r - l) / 2;
        MERGESORT(arr, l, m);
        MERGESORT(arr, m + 1, r);
        MERGE(arr, l, m, r);
    }
}
void MergeSort_time(int arr[], int n, double &time){
    clock_t start, end;
    time = 0;

    start = clock();
    MERGESORT(arr, 0, n - 1);
    end = clock();

    time = (double)(end - start) / CLOCKS_PER_SEC;
}