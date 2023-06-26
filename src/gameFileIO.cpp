#include"GameFileIO.h"

GameFile::GameFile(string fileName,int mode)
{
    switch (mode)
    {
    case IN:
        fileOperator.open(fileName,ios_base::in);
        break;

    case OUT:
        fileOperator.open(fileName,ios_base::out);
        break;
    
    default:
        break;
    };

    lastError=0;
}

GameFile::~GameFile(){}

int GameFile::GetLastError()
{
    return lastError;
}




bool GameFile::getMatrix(int** matrix)
{
    ;
}

bool GameFile::putMatrix(int** matrix)
{
    ;
}

