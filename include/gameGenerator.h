#pragma once

#include <time.h>
#include <cstdlib>
#include <algorithm>

void CreateSolvedGame(int (&matrix)[9][9]);

void CreateUnsolvedGame(int (&matrix)[9][9],int spaceCount,bool isUnique);