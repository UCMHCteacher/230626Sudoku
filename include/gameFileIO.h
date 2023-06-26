#pragma once

#include<string>
#include<fstream>
#include<iostream>

using std::string;
using std::fstream;
using std::ios_base;


class GameFile
{
public:
    enum {IN,OUT};

public:
    GameFile(string fileName,int mode);
    ~GameFile();

private:
    fstream fileOperator;

public:
    bool getMatrix(int** matrix);
    bool putMatrix(int** matrix);

public:
    int GetLastError();
    enum {MATRIXFORMATERROR=1, };
private:
    int lastError;
};