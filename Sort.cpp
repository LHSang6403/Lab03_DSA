#include <time.h>

void swap(int &num1, int &num2)
{
    int temp = num1;
    num1 = num2;
    num2 = temp;
}

void QUICKSORT(int a[],int l,int r,int &comparison)
{
    if (++comparison && l >= r) return;
    int i = l, j = r, m = a[(i + j) / 2];
    while (++comparison && i < j)
    {
        while (++comparison && a[i] < m) i++;
        while (++comparison && a[j] > m) j--;
        if (++comparison && i <= j)
        {
            swap(a[i],a[j]);
            i++;
            j--;
        }
    }
    QUICKSORT(a,l,j,comparison);
    QUICKSORT(a,i,r,comparison);
}

void QuickSort(int a[],int n,int &comparison,double &time)
{
    clock_t start, end;
    comparison = 0;
    time = 0;

    start = clock();
    QUICKSORT(a,0,n,comparison);
    end = clock();

    time = (double) (end - start) / CLOCKS_PER_SEC;
}