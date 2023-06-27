#pragma once

#include<string>
#include<fstream>
#include<iostream>
#include<sstream>

using std::string;
using std::fstream;
using std::ios_base;
using std::cout;
using std::stringstream;


class GameFile
{
public:
    enum {IN,OUT};

public:
    GameFile(string fileName,int mode);
    ~GameFile();

private:
    fstream fileOperator;
    int openMode;

public:
    bool getMatrix(int (&matrix)[9][9]);
    bool putMatrix(int matrix[9][9]);

public:
    int GetLastError();
    enum {MATRIXFORMATERROR=1, MODEERROR, MATRIXELEMENTERROR};
private:
    int lastError;
};