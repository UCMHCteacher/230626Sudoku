#pragma once

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
