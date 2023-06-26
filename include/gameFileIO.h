#pragma once

#include<string>

using std::string;


class GameFile
{
public:
    enum {IN,OUT};

public:
    GameFile(string fileName,int mode);
    ~GameFile();
;
};