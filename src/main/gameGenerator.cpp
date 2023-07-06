#include"gameGenerator.h"


/**
 * @brief Generate a random arrange from 1 to length for a fixed length array
 * 
 * @tparam [autoset]length 
 * @param [out]array fixed length int array, which is to be set to a random arrange
 * @return nothing, not even a indicator
 * @warning Do not use a pointer as param
 */
template <int length>
void GetRandomArrange(int (&array)[length])
{
    srand(time(NULL));

    for (int loc=0; loc<length; loc++)
        array[loc]=loc+1;

    for(int i=0; i<length; i++)
    {
        int swapLocationa=rand()%length;
        int swapLocationb=rand()%length;
        std::swap(array[swapLocationa],array[swapLocationb]);
    }
}


/**
 * @brief Create a solved game matrix
 * 
 * @param [out]matrix 
 * @return nothing, not even a indicator
 * @warning Notice that matrix should be a 9*9 int and shouldn't be a pointer(int**). Or it will make an compile error.
 */
void CreateSolvedGame(int (&matrix)[9][9])
{
    int baseLine[9];
    GetRandomArrange(baseLine);

    int baseShiftper3Line[3];
    GetRandomArrange(baseShiftper3Line);

    int addShiftfor3Lines[3];

    for(int row=0;row<9;row++)
    {
        if(row%3==0) GetRandomArrange(addShiftfor3Lines);

        for(int col=0;col<9;col++)
            matrix[row][col]=
            baseLine[
                (col+
                baseShiftper3Line[row/3]+
                addShiftfor3Lines[row%3]*3)%9
            ];
    }
}


/**
 * @brief Create an unsolved game matrix
 * 
 * @param [out]matrix 
 * @param [in]isUnique to set whether the solution is unique or not
 * @return nothing, not even a indicator
 * @warning Notice that matrix should be a 9*9 int and shouldn't be a pointer(int**). Or it will make an compile error.
 */
void CreateUnsolvedGame(int (&matrix)[9][9],int spaceCount,bool isUnique)
{
    st:srand(time(NULL));
    CreateSolvedGame(matrix);

    int nums=spaceCount;
    while(nums)
    {
        int row=rand()%9;
        int col=rand()%9;
        if(matrix[row][col]!=0)
        {
            matrix[row][col]=0;
            nums--;
        }
    }


    if(isUnique)
    {
        int solvedMatrix[9][9];
        if(!SolveGame(matrix,solvedMatrix))
            goto st;
    }
}