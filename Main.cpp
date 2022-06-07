#include "DataGenerator.h"
#include "Sort.h"
#include <iostream>

using namespace std;

int main()
{
    int n = 1000000;
    int *a = new int [n];
    GenerateData(a,n,0);
    int comparision = 0;
    double time = 0;
    CountingSort(a,n,comparision,time);
    cout << comparision << " " << time;
    return 0;
}