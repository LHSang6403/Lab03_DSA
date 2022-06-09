#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include "DataGenerator.h"
#include "Sort.h"

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

void callSortFunction(string algorithm, int a[], int n, int &comparison, double &time)
{
    if (algorithm == "selection-sort");
    if (algorithm == "insertion-sort");
    if (algorithm == "bubble-sort") BubbleSort(a,n,comparison,time);
    if (algorithm == "shaker-sort") ShakerSort(a,n,comparison,time);
    if (algorithm == "shell-sort") ShellSort(a,n,comparison,time);
    if (algorithm == "heap-sort") HeapSort(a,n,comparison,time);
    if (algorithm == "merge-sort");
    if (algorithm == "counting-sort") CountingSort(a,n,comparison,time);
    if (algorithm == "quick-sort") QuickSort(a,n,comparison,time);
    if (algorithm == "radix-sort") RadixSort(a,n,comparison,time);
    if (algorithm == "flash-sort") FlashSort(a,n,comparison,time);
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

void printResult(string algorithm, string filename, int inOrder, int size, string outParameter, int comparison, double time)
{
    cout << "==================================" << endl;
    cout << "Algorithm: " << makeBeautifulName(algorithm) << endl;
    if (filename != "") cout << "Input File: " << filename << endl;
    cout << "Input Size: " << size << endl;
    if (inOrder != -1) cout << "Input Order: ";
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
    cout << "Running time: ";
    if (outParameter == "-both" || outParameter == "-time") cout << time << endl; else cout << "Not Required" << endl;
    cout << "Comparisons: ";
    if (outParameter == "-both" || outParameter == "-comp") cout << comparison << endl; else cout << "Not Required" << endl;
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
    ModeA arg = inputAlgorithmMode(argc,argv);
    int comparison = 0;
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
    
}

ModeC inputComparisonMode(int argc, char **argv)
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

void processComparisonMode(int argc, char **argv)
{
    ModeC arg = inputComparisonMode(argc,argv);

    int *a1 = NULL, *a2 = NULL;
    int comp1 = 0, comp2 = 0;
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
}

void processArg(int argc, char **argv)
{
    if (strcmp(argv[1],"-a") == 0) processAlgorithmMode(argc,argv); else 
    if (strcmp(argv[1],"-c") == 0) processComparisonMode(argc,argv); else 
    cout << "Invalid Argument" << endl;
}