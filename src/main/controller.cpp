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
    srand(time(NULL));

    ParamCheck();

    switch (processMode)
    {
    case SOLVE:
        while (true)
        {
            int matrix[9][9];
            if(!gameInput->readMatrix(matrix))
            {
                if(gameInput->GetLastError()==GameFile::EOFERROR) break;
                else {cout<<"Failed in reading matrix from file, error code:"<<gameInput->GetLastError()<<"\n";continue;}
            }

            int solvedMatrix[9][9];
            SolveGame(matrix,solvedMatrix);
            if(!gameOutput->writeMatrix(solvedMatrix))
                cout<<"Failed in writing matrix to file, error code:"<<gameOutput->GetLastError()<<"\n";
        }
        
        break;

    case GENERATE:
        for(int i=1;i<=generatorConfig.gameCount;i++)
        {
            if(generatorConfig.solved)
            {
                int matrix[9][9];
                CreateSolvedGame(matrix);
                if(!gameOutput->writeMatrix(matrix))
                    cout<<"Failed in writing matrix to file, error code:"<<gameOutput->GetLastError()<<"\n";
            }
            else
            {
                int spaceCount=
                    generatorConfig.spaceCountLowerBound+
                    rand()%(generatorConfig.spaceCountUpperBound-generatorConfig.spaceCountLowerBound);
                int matrix[9][9];
                CreateUnsolvedGame(matrix,spaceCount,generatorConfig.solutionUniqueness);
                if(!gameOutput->writeMatrix(matrix))
                    cout<<"Failed in writing matrix to file, error code:"<<gameOutput->GetLastError()<<"\n";
            }
        }
        break;

    default:
        exit(0);
        break;
    };
}