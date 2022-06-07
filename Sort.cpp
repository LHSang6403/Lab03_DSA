#include <time.h>

void swap(int &num1, int &num2)
{
    int temp = num1;
    num1 = num2;
    num2 = temp;
}

void SharkerSort(int arr[], int n)
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

void QUICKSORT(int a[],int l,int r,int &comparision)
{
    if (++comparision && l >= r) return;
    int i = l, j = r, m = a[(i + j) / 2];
    while (++comparision && i < j)
    {
        while (++comparision && a[i] < m) i++;
        while (++comparision && a[j] > m) j--;
        if (++comparision && i <= j)
        {
            swap(a[i],a[j]);
            i++;
            j--;
        }
    }
    QUICKSORT(a,l,j,comparision);
    QUICKSORT(a,i,r,comparision);
}

void QuickSort(int a[],int n,int &comparision,double &time)
{
    clock_t start, end;
    comparision = 0;
    time = 0;

    start = clock();
    QUICKSORT(a,0,n,comparision);
    end = clock();

    time = (double) (end - start) / CLOCKS_PER_SEC;
}