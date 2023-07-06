#include "controller.h"



int processMode=NONE;

void setProcessMode(int newMode)
{
    if(processMode!=NONE)
    {
        cout<<"Command is defined twice or more!\n";
        exit(0);
    }
    processMode=newMode;
}
int getProcessMode()
{
    return processMode;
}



GeneratorConfig generatorConfig;

GameFile* gameInput;
GameFile* gameOutput;



void ParamCheck()
{
    // space count check
    if(generatorConfig.spaceCountLowerBound==0 && generatorConfig.spaceCountUpperBound==0)
    {
        switch (generatorConfig.difficulty)
        {
        case 2:
            generatorConfig.spaceCountLowerBound=26;
            generatorConfig.spaceCountUpperBound=30;
            break;
        case 3:
            generatorConfig.spaceCountLowerBound=31;
            generatorConfig.spaceCountUpperBound=35;
            break;
        default:// case 0,1
            generatorConfig.spaceCountLowerBound=21;
            generatorConfig.spaceCountUpperBound=25;
            break;
        }
    }

    if(gameOutput==nullptr)
        gameOutput=new GameFile("sudoku.txt",GameFile::OUT);
}


void StartProcess()
{
    ParamCheck();
    ;
}