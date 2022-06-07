#include "Sort.h"

void SharkerSort(int *&arr, int n)
{
    int up = 0,
        down = n - 1,
        hv = 0;
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
}
