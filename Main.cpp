#include "Argument.h"
#include <cstring>

int main(int argc, char **argv)
{
    // int argc = 6;
    // char **argv = new char* [argc];
    // for (int i = 0; i < argc; i++) argv[i] = new char [1000];

    // strcpy(argv[0],"Main.exe"); 
    // strcpy(argv[1],"-a"); 
    // strcpy(argv[2],"flash-sort"); 
    // strcpy(argv[3],"70000"); 
    // strcpy(argv[4],"-rand"); 
    // strcpy(argv[5],"-both"); 

    processArg(argc,argv);
    return 0;
}