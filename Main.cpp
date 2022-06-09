#include "DataGenerator.h"
#include "Sort.h"
#include <iostream>

using namespace std;

int main()
{
    int n = 100000;
    int *a = new int [n];
    GenerateData(a,n,2);
    int comparision = 0;
    double time = 0;

    // QuickSort(a,n,comparision,time);
    FlashSort(a, n, comparision, time);
    //for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << endl << comparision << " " << time;

    return 0;
}