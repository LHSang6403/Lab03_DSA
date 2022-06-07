#include "DataGenerator.h"
#include "Sort.h"
#include <iostream>

using namespace std;

int main()
{
    int n = 20;
    int *a = new int [n];
    GenerateData(a,n,0);
    int comparision = 0;
    double time = 0;

    
    RadixSort(a,n,comparision,time);
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << endl << comparision << " " << time;

    return 0;
}