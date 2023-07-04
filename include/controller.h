#pragma once

#include"GameFileIO.h"


typedef struct GeneratorConfig
{
    int gameCount=1;

    bool solved=false;

    int difficulty;
    int spaceCountUpperBound;
    int spaceCountLowerBound;
    bool solutionUniqueness=false;

    bool solutionFixed=true;
}generatorConfig;



enum {
    NONE=0,
    SOLVE,
    GENERATE
};
void setProcessMode(int newMode);
int getProcessMode();



extern GeneratorConfig generatorConfig;

extern GameFile* gameInput;
extern GameFile* gameOutput;