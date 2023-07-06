#pragma once

#include"GameFileIO.h"


class GeneratorConfig
{
public:
    int gameCount;


    bool solved;


    int difficulty;

    int spaceCountUpperBound;
    int spaceCountLowerBound;

    bool solutionUniqueness;

    bool solutionFixed;


    GeneratorConfig()
    {
        gameCount=1;
        solved=false;
        solutionUniqueness=false;
        solutionFixed=false;

        difficulty=0;
        spaceCountLowerBound=0;
        spaceCountUpperBound=0;
    };
};



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


void StartProcess();