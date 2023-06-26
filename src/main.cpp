/**
 * @file main.cpp
 * @author UCMHCteacher
 * @mail UCMHCteacher@163.com
 * @github https://github.com/UCMHCteacher
 * @date June 25 2023
 * 
 */

#include<unistd.h>
#include<iostream>

using std::cout;

enum {
    NONE=0,
    SOLVE,
    GENERATE
};


void printUsage()
{
    cout<<
        "Usage:\tsudoku.exe  [-c [number]]  [-s filename]  [-n [number] [-m difficulty] [-u] [-r spacenumber]]  [-o filename] [-h]\n"
        "-o\tset output file path\n"
        "-c\tgenerate solved games, with a number followed to set how many games you want\n"
        "-s\tsolve the games in the file\n"
        "-n\tgenerate unsolved games, with a number followed to set how many games you want\n"
        "\t-m\tset the difficulty of the unsolved games\n"
        "\t-u\tset the uniqueness of the unsolved games' solution\n"
        "\t-r\tset the spacenumber of the unsolved games\n"
        "-h\tshow this help message\n";
}


int main(int argc,char* argv[])
{
    int processMode=NONE;

    int opt;
    while ((opt=getopt(argc,argv,"c:s:n::m:ur:o:hf")) != -1)
    {
        switch (opt)
        {
        case 's':
            /* code */
            break;
        case 'o':
            /* code */
            break;
        case 'n':
            /* code */
            break;
        case 'm':
            /* code */
            break;
        case 'r':
            /* code */
            break;
        case 'u':
            /* code */
            break;
        case 'c':
            /* code */
            break;
        case 'h':
            printUsage();
            return 0;
            break;
        default:
            cout<<"Parameter input error occurs at \"-"<<char(opt)<<"\"\n";
            printUsage();
            return 0;
            break;
        }
    }



    

    return 0;
}