#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include "DataGenerator.h"
#include "Sort_comp.h"
#include "Sort_time.h"

using namespace std;

struct ModeA
{
    string algorithm;
    string givenInput;
    int inputSize;
    string inOrder;
    string outParameter;

    ModeA()
    {
        algorithm = givenInput = inOrder = outParameter = "";
        inputSize = 0;
    }
};

struct ModeC
{
    string algo1;
    string algo2;
    string givenInput;
    int inputSize;
    string inOrder;

    ModeC()
    {
        algo1 = algo2 = givenInput = inOrder = "";
        inputSize = 0;
    }
};

bool validGivenInput(string filename)
{
    for (int i = 0; i < filename.length(); i++)
    if (filename[i] < '0' || filename[i] > '9') return 1;
    return 0;
}

bool validInputOrder(string order)
{
    if (order == "-rand" || order == "-rev" || order == "-nsorted" || order == "-sorted") return 1;
    return 0;
}

int getInputOrder(string order)
{
    if (order == "-rand") return 0;
    if (order == "-sorted") return 1;
    if (order == "-rev") return 2;
    if (order == "-nsorted") return 3;
    return -1;
}

string makeBeautifulName(string algorithm)
{
    algorithm[0] = toupper(algorithm[0]);

    int pos = algorithm.find("-");
    algorithm[pos] = ' ';
    algorithm[pos + 1] = toupper(algorithm[pos + 1]);
    return algorithm;
}

string displayCommainNum(unsigned long long num)
{
    string res = "";
    
    while (num != 0)
    {
        string temp = to_string(num % 1000);
        num /= 1000;

        while (temp.length() != 3 && num != 0) temp = '0' + temp;
        res = temp + res;
        if (num != 0) res = ',' + res;
    }
    
    return res;
}

void callSortFunction(string algorithm, int a[], int n, unsigned long long &comparison, double &time)
{
    int *b = new int [n];
    for (int i = 0; i < n; i++) b[i] = a[i];
    
    if (algorithm == "selection-sort")
    {
        // compare sorting here
        // time sorting here
    }  

    if (algorithm == "insertion-sort") 
    {   
        InsertionSort_comp(a,n,comparison);
        InsertionSort_time(b,n,time);
    }  

    if (algorithm == "bubble-sort") 
    {
        BubbleSort_comp(a,n,comparison);
        BubbleSort_time(b,n,time);
    }  

    if (algorithm == "shaker-sort") 
    {
        ShakerSort_comp(a,n,comparison);
        ShakerSort_time(b,n,time);
    } 

    if (algorithm == "shell-sort") 
    {
        ShellSort_comp(a,n,comparison);
        ShellSort_time(b,n,time);
    }  

    if (algorithm == "heap-sort") 
    {
        HeapSort_comp(a,n,comparison);
        HeapSort_time(b,n,time);
    } 

    if (algorithm == "merge-sort")
    {
        // compare sorting here
        // time sorting here
    } 

    if (algorithm == "counting-sort") 
    {
        CountingSort_comp(a,n,comparison);
        CountingSort_time(b,n,time);
    }  

    if (algorithm == "quick-sort") 
    {
        QuickSort_comp(a,n,comparison);
        QuickSort_time(b,n,time);
    }  

    if (algorithm == "radix-sort") 
    {
        RadixSort_comp(a,n,comparison);
        RadixSort_time(b,n,time);
    }  

    if (algorithm == "flash-sort") 
    {
        FlashSort_comp(a,n,comparison);
        FlashSort_time(b,n,time);
    }  

    delete []b;
}

ModeA inputAlgorithmMode(int argc, char **argv)
{
    ModeA res;
    res.algorithm = argv[2];

    res.givenInput = argv[3];
    if (!validGivenInput(res.givenInput))
    {
        res.inputSize = stoi(res.givenInput);
        res.givenInput = "";
    } 

    res.inOrder = argv[4];
    if (validInputOrder(res.inOrder)) res.outParameter = argv[5]; else
    {
        res.outParameter = res.inOrder;
        res.inOrder = "";
    }
    return res;
}

void printResult(string algorithm, string filename, int inOrder, int size, string outParameter, unsigned long long comparison, double time)
{
    cout << "==================================" << endl;
    cout << "Algorithm:\t" << makeBeautifulName(algorithm) << endl;
    if (filename != "") cout << "Input File:\t" << filename << endl;
    cout << "Input Size:\t" << displayCommainNum(size) << endl;
    if (inOrder != -1) cout << "Input Order:\t";
    switch (inOrder)
    {
        case 0: 
            cout << "Randomize" << endl;
            break;
        case 1:
            cout << "Sorted" << endl;
            break;
        case 2:
            cout << "Reversed" << endl;
            break;
        case 3: 
            cout << "Nearly Sorted" << endl;
            break;
    }
    cout << "----------------------------------" << endl;
    cout << "Running time:\t";
    if (outParameter == "-both" || outParameter == "-time") cout << time << " s" << endl; else cout << "Not Required" << endl;
    cout << "Comparisons:\t";
    if (outParameter == "-both" || outParameter == "-comp") cout << displayCommainNum(comparison) << endl; else cout << "Not Required" << endl;
    cout << "==================================" << endl << endl;
}

string convertNuminFilename(int num)
{
    if (num == 0) return "1";
    if (num == 1) return "3";
    if (num == 2) return "4";
    if (num == 3) return "2";
    return "";
}

void processAlgorithmMode(int argc, char **argv)
{
    cout << "==o==o==o==o==o==o==o==o==o==o==o==o==" << endl;
    cout << "||                                  ||" << endl;
    cout << "||          ALGORITHM MODE          ||" << endl;
    cout << "||                                  ||" << endl;
    cout << "==o==o==o==o==o==o==o==o==o==o==o==o==" << endl;

    ModeA arg = inputAlgorithmMode(argc,argv);
    unsigned long long comparison = 0;
    double time = 0;

    int *a = NULL;

    if (arg.givenInput != "") 
    {
        ifstream fi(arg.givenInput);
        fi >> arg.inputSize;
        a = new int [arg.inputSize];

        for (int i = 0; i < arg.inputSize; i++) fi >> a[i];

        callSortFunction(arg.algorithm,a,arg.inputSize,comparison,time);
        printResult(arg.algorithm,arg.givenInput,getInputOrder(arg.inOrder),arg.inputSize,arg.outParameter,comparison,time);
    } else 
    {
        a = new int [arg.inputSize];
        if (arg.inOrder != "") 
        {
            GenerateData(a,arg.inputSize,getInputOrder(arg.inOrder)); 
            ofstream fo("input.txt");
            
            fo << arg.inputSize << endl;
            for (int i = 0; i < arg.inputSize; i++) fo << a[i] << " ";
            
            fo.close();

            callSortFunction(arg.algorithm,a,arg.inputSize,comparison,time);
            printResult(arg.algorithm,arg.givenInput,getInputOrder(arg.inOrder),arg.inputSize,arg.outParameter,comparison,time);
        } else
        {
            // Print all mode 
            for (int i = 0; i < 4; i++)
            {
                ofstream fo("input_" + convertNuminFilename(i) + ".txt"); 
                fo << arg.inputSize << endl;

                GenerateData(a,arg.inputSize,i);
                for (int j = 0; j < arg.inputSize; j++) fo << a[j] << " ";
                fo.close();

                callSortFunction(arg.algorithm,a,arg.inputSize,comparison,time);
                printResult(arg.algorithm,"",i,arg.inputSize,arg.outParameter,comparison,time);
            }
        }
    }
    
    delete []a;
}

ModeC inputCompareMode(int argc, char **argv)
{
    ModeC res;

    res.algo1 = argv[2];
    res.algo2 = argv[3];
    res.givenInput = argv[4];
    if (!validGivenInput(res.givenInput))
    {
        res.inputSize = stoi(res.givenInput);
        res.givenInput = "";
    }

    if (res.inputSize != 0) res.inOrder = argv[5];

    return res;
}

void processCompareMode(int argc, char **argv)
{
    cout << "==o==o==o==o==o==o==o==o==o==o==o==o==" << endl;
    cout << "||                                  ||" << endl;
    cout << "||           COMPARE MODE           ||" << endl;
    cout << "||                                  ||" << endl;
    cout << "==o==o==o==o==o==o==o==o==o==o==o==o==" << endl;
    
    ModeC arg = inputCompareMode(argc,argv);

    int *a1 = NULL, *a2 = NULL;
    unsigned long long comp1 = 0, comp2 = 0;
    double time1 = 0, time2 = 0;
    
    if (arg.givenInput == "")
    {
        a1 = new int [arg.inputSize];
        a2 = new int [arg.inputSize];

        GenerateData(a1,arg.inputSize,getInputOrder(arg.inOrder));

        ofstream fo("input.txt");
        fo << arg.inputSize << endl;
        for (int i = 0; i < arg.inputSize; i++) 
        {   
            a2[i] = a1[i];
            fo << a1[i] << " ";
        }
    } else 
    {
        ifstream fi(arg.givenInput);
        fi >> arg.inputSize;

        a1 = new int [arg.inputSize];
        a2 = new int [arg.inputSize];

        for (int i = 0; i < arg.inputSize; i++)
        {
            fi >> a1[i];
            a2[i] = a1[i];
        }
    }

    callSortFunction(arg.algo1,a1,arg.inputSize,comp1,time1);
    callSortFunction(arg.algo2,a2,arg.inputSize,comp2,time2);

    printResult(arg.algo1,arg.givenInput,getInputOrder(arg.inOrder),arg.inputSize,"-both",comp1,time1);
    printResult(arg.algo2,arg.givenInput,getInputOrder(arg.inOrder),arg.inputSize,"-both",comp2,time2);

    delete []a1;
    delete []a2;
}

void processArg(int argc, char **argv)
{
    if (strcmp(argv[1],"-a") == 0) processAlgorithmMode(argc,argv); else 
    if (strcmp(argv[1],"-c") == 0) processCompareMode(argc,argv); else 
    cout << "Invalid Argument" << endl;
}