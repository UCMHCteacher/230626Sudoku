#include<unistd.h>
#include<iostream>
#include<sstream>
#include<algorithm>

#include"controller.h"

using std::cout;
using std::string;
using std::stringstream;






void printUsage()
{
    cout<<
        "Usage:\tsudoku.exe  [-c [number]] | [-s filename] | [-n [number] [-m difficulty] [-u] [-r number]]  [-o filename] [-h]\n"
        "-c\tgenerate solved games, with a number followed to set how many games you want\n"
        "-s\tsolve the games in the file\n"
        "-n\tgenerate unsolved games, with a number followed to set how many games you want\n"
        "\t-m\tset the difficulty of the unsolved games\n"
        "\t-u\tset the uniqueness of the unsolved games' solution\n"
        "\t-r\tset the spacenumber of the unsolved games\n"
        "-o\tset output file path\n"
        "-h\tshow this help message\n";
}


int main(int argc,char* argv[])
{
    gameInput=nullptr;
    gameOutput=nullptr;

    int opt;
    if(argc==1)// no argument followed
    {
        printUsage();
        return 0;
    }

    // argument parser with process state setter
    while ((opt=getopt(argc,argv,"c::s:n::m:ur:o:hf")) != -1)
    {
        switch (opt)
        {

        case 'c':
            setProcessMode(GENERATE);
            //change generator config
            generatorConfig.solved=true;
            // generatorConfig.solutionFixed=false;
            if(optarg!=NULL) generatorConfig.gameCount=atoi(optarg);
            break;

        case 's':
            setProcessMode(SOLVE);
            //change input
            gameInput=new GameFile(optarg,GameFile::IN);
            break;

        case 'n':
            setProcessMode(GENERATE);
            //change generator config
            generatorConfig.solved=false;
            // generatorConfig.solutionFixed=true;
            if(optarg!=NULL) generatorConfig.gameCount=atoi(optarg);
            break;
        case 'm':
            if(getProcessMode()!=GENERATE || generatorConfig.solved!=false)
            {
                cout<<"This argument needs a precondition of generating unsolved games!\n";
                exit(0);
            }
            generatorConfig.difficulty=atoi(optarg);
            if(generatorConfig.difficulty>3 || generatorConfig.difficulty<1){
                cout<<
                    "Difficulty of unsolved games should be set between 1 and 3.\n"
                    "Difficulty is now set to 1.\n";
                generatorConfig.difficulty=1;
            }
            break;
        case 'u':
            if(getProcessMode()!=GENERATE || generatorConfig.solved!=false)
            {
                cout<<"This argument needs a precondition of generating unsolved games!\n";
                exit(0);
            }
            generatorConfig.solutionUniqueness=true;
            break;
        case 'r':
            if(getProcessMode()!=GENERATE || generatorConfig.solved!=false)
            {
                cout<<"This argument needs a precondition of generating unsolved games!\n";
                exit(0);
            }
            {
                string optstr(optarg);
                optstr.replace(optstr.find("~"),1," ");
                stringstream spaceCountStringStream(optstr);
                spaceCountStringStream>>generatorConfig.spaceCountUpperBound>>generatorConfig.spaceCountLowerBound;
            }
            {
                bool spaceBoundChanged=false;
                if(generatorConfig.spaceCountLowerBound<20) {generatorConfig.spaceCountLowerBound=20;spaceBoundChanged=true;}
                if(generatorConfig.spaceCountLowerBound>55) {generatorConfig.spaceCountLowerBound=55;spaceBoundChanged=true;}
                if(generatorConfig.spaceCountUpperBound<20) {generatorConfig.spaceCountUpperBound=20;spaceBoundChanged=true;}
                if(generatorConfig.spaceCountUpperBound>55) {generatorConfig.spaceCountUpperBound=55;spaceBoundChanged=true;}
                if(generatorConfig.spaceCountLowerBound>generatorConfig.spaceCountUpperBound) 
                    {std::swap(generatorConfig.spaceCountLowerBound,generatorConfig.spaceCountUpperBound);spaceBoundChanged=true;}

                if(spaceBoundChanged)
                    cout<<
                        "Space bound of unsolved games should be set between 20 and 55.\n"
                        "Space bound is now set to "<<generatorConfig.spaceCountLowerBound<<"~"<<generatorConfig.spaceCountUpperBound<<".\n";
            }
            break;

        case 'o':
            if(gameOutput!=nullptr)
            {
                cout<<"Output filename is defined twice or more!\n";
                exit(0);
            }
            gameOutput=new GameFile(optarg,GameFile::OUT);
            break;

        case 'h':
            printUsage();
            exit(0);
            break;
        default:
            printUsage();
            exit(0);
            break;
        }
    }


    StartProcess();


    return 0;
}