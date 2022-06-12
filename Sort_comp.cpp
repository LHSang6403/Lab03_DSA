#include <time.h>
#include <math.h>
#include <iostream>
#include <algorithm>

using namespace std;

void ShakerSort_comp(int arr[], int n, unsigned long long &comparison)
{
    int up = 0,
        down = n - 1,
        hv = 0; // store the last position of each swap.

    comparison = 0;

    while (++comparison && up < down)
    {
        for (int i = up; ++comparison, i < down; i++)
        {
            if (++comparison && arr[i] > arr[i + 1])
            {
                swap(arr[i], arr[i + 1]);
                hv = i;
            }
        }
        down = hv;
        for (int j = down; ++comparison, j > up; j--)
        {
            if (++comparison && arr[j - 1] > arr[j])
            {
                swap(arr[j - 1], arr[j]);
                hv = j;
            }
        }
        up = hv;
    }
}

void createGap(int n, int gap[], int &gap_num, unsigned long long &comparison)
{
    gap[0] = 1;
    for (int i = 1; ++comparison, gap[i - 1] < n; i++)
    {
        gap[i] = 3 * gap[i - 1] + 1;
        gap_num++;
    }
}

void ShellSort_comp(int a[], int n, unsigned long long &comparison)
{
    comparison = 0;

    int *gap = new int[n],
        gap_num = 0;

    createGap(n, gap, gap_num, comparison);

    int p = 0,
        j = 0,
        t = 0,
        x = 0;
    for (p = 0; ++comparison, p < gap_num; p++)
    {
        t = gap[p];
        for (int i = t; ++comparison, i < n; i++)
        {
            x = a[i];
            j = i;
            while (++comparison && x < a[j - t] && ++comparison && j >= t)
            {
                a[j] = a[j - t];
                j = j - t;
            }
            a[j] = x;
        }
    }
    delete[] gap;
}

void QUICKSORT(int a[], int l, int r, unsigned long long &comparison)
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

void QuickSort_comp(int a[], int n, unsigned long long &comparison)
{
    comparison = 0;
    QUICKSORT(a, 0, n - 1, comparison);
}

void CountingSort_comp(int *&a, int n, unsigned long long &comparison)
{
    comparison = 0;

    // According to randomize code, the elements' range is from 1 to n-1
    int *flag = new int[n]{0};
    int *res = new int[n];

    for (int i = 0; ++comparison, i < n; i++)
        flag[a[i]]++;
    for (int i = 1; ++comparison, i < n; i++)
        flag[i] += flag[i - 1];
    for (int i = 0; ++comparison, i < n; i++)
    {
        res[flag[a[i]] - 1] = a[i];
        flag[a[i]]--;
    }

    delete[] a;
    a = res;
    delete flag;

    // Ref: https://www.geeksforgeeks.org/counting-sort/
}

void RadixSort_comp(int *&a, int n, unsigned long long &comparison)
{
    comparison = 0;

    int *res = new int[n]{0};

    for (int i = 1; ++comparison, n / i > 0; i *= 10)
    {
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
        for (int j = 0; ++comparison, j < n; j++)
        {
            a[j] = res[j];
            res[j] = 0;
        }
    }
    delete[] res;

    // Ref: https://www.geeksforgeeks.org/radix-sort/
}

void findMaxMin(int arr[], int n, unsigned long long &comparison, int &max, int &minVal)
{

    for (int i = 0; ++comparison, i < n; i++)
    {
        if (++comparison && arr[i] > arr[max])
            max = i;
        if (++comparison && arr[i] < minVal)
            minVal = arr[i];
    }
}

void FlashSort_comp(int arr[], int n, unsigned long long &comparison)
{
    comparison = 0;

    int max = 0,
        minVal = arr[0];

    // Find min value and index of max value
    findMaxMin(arr, n, comparison, max, minVal);

    // Create bucket to store value
    int bucketNum = floorf((0.125 * n) * 100) / 100;
    int *bucket = new int[bucketNum];
    // Initialize value of bucket with 0
    for (int i = 0; ++comparison, i < bucketNum; i++)
    {
        bucket[i] = 0;
    }

    const float c = (bucketNum - 1.0) / (arr[max] - minVal);
    // Count the number value of each bucket
    for (int i = 0; ++comparison, i < n; i++)
    {
        int temp = floorf((c * (arr[i] - minVal)) * 100) / 100;
        bucket[temp] += 1;
    }
    // Calc the lastest index of each bucket
    for (int i = 1; ++comparison, i < bucketNum; i++)
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
            k = floorf((c * (arr[j] - minVal) * 100)) / 100;
        }

        if (++comparison && k < 0)
            break;
        flash = arr[j];
        while (++comparison && j != bucket[k])
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
    for (int idx = 1; ++comparison, idx < n; idx++)
    {
        int hold = arr[idx];
        int idx_temp = idx - 1;
        while (++comparison && idx_temp >= 0 && ++comparison && arr[idx_temp] > hold)
        {
            arr[idx_temp + 1] = arr[idx_temp];
            idx_temp--;
        }
        arr[idx_temp + 1] = hold;
    }
    delete[] bucket;
}

void buildHeap(int arr[], int n, int i, unsigned long long &comparison)
{
    int max = i;
    int l = i * 2;
    int r = (i * 2) + 1;

    // find node has max value
    if (++comparison && l < n && ++comparison && arr[l] > arr[max])
        max = l;
    if (++comparison && r < n && ++comparison && arr[r] > arr[max])
        max = r;

    if (++comparison && max != i)
    { // swap max to parent, calling recursive
        swap(arr[max], arr[i]);
        buildHeap(arr, n, max, comparison); // recursive to child node
    }
}

void HeapSort_comp(int arr[], int sz, unsigned long long &comparison)
{
    comparison = 0;

    for (int i = (sz / 2) - 1; ++comparison && i >= 0; i--)
    { // array has n elements -> has n/2 parent element
        buildHeap(arr, sz, i, comparison);
    }
    for (int j = sz - 1; ++comparison && j > 0; j--)
    {
        swap(arr[0], arr[j]);
        buildHeap(arr, j, 0, comparison);
    }
}

void BubbleSort_comp(int arr[], int sz, unsigned long long &comparison)
{
    comparison = 0;

    for (int i = 0; ++comparison && i < sz - 1; i++)
    {
        for (int j = sz - 1; ++comparison && j > i; j--)
        {
            if (++comparison && arr[j] < arr[j - 1])
                swap(arr[j], arr[j - 1]);
        }
    }
}

void InsertionSort_comp(int arr[], int sz, unsigned long long &comparison)
{
    comparison = 0;

    int i, j;
    int key;

    for (int i = 1; ++comparison && i < sz; i++)
    {
        key = arr[i];
        j = i - 1;

        while (++comparison && j >= 0 && ++comparison && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}