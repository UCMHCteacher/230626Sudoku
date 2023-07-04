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