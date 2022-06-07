#include "DataGenerator.h"
#include "Sort.h"
#include <iostream>

using namespace std;

int main()
{
    int n = 1000000;
    int *a = new int [n];
    GenerateData(a,n,0);
    int QuickSort_comparision = 0;
    double QuickSort_time = 0;
    QuickSort(a,n,QuickSort_comparision,QuickSort_time);
    cout << QuickSort_comparision << " " << QuickSort_time;
    return 0;
}