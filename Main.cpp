#include "DataGenerator.h"
#include "Sort.h"
#include <iostream>
#include "Argument.h"
#include <cstring>

using namespace std;

int main()
{
    int argc = 5;
    char **argv = NULL;
    argv = new char* [argc];
    for (int i = 0; i < argc; i++) argv[i] = new char [100];

    strcpy(argv[0],"Main");
    strcpy(argv[1],"-a");
    strcpy(argv[2],"quick-sort");
    strcpy(argv[3],"10");
    strcpy(argv[4],"-both");
    //strcpy(argv[5],"-time");

    processArg(argc,argv);
    return 0;
}