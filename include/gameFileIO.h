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
    bool readMatrix(int (&matrix)[9][9]);
    bool writeMatrix(int (&matrix)[9][9]);

public:
    bool readMatrixas1D(int (&matrix)[81]);
    bool writeMatrixas1D(int (&matrix)[81]);


public:
    int GetLastError();
    enum {OPERATEMODEERROR=1, MATRIXSIZEINFILEERROR, MATRIXELEMENTERROR};
private:
    int lastError;
};