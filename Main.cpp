#include "DataGenerator.h"
#include "Sort.h"
#include <iostream>

using namespace std;

int main()
{
    int n = 100000;
    int *a = new int [n];
    GenerateData(a,n,2);
    int comparison = 0;
    double time = 0;

    // QuickSort(a,n,comparison,time);
    FlashSort(a, n, comparison, time);
    //for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << endl << comparison << " " << time;

    return 0;
}