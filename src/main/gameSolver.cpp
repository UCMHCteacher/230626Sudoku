#include "gameSolver.h"


int CountOneBit(short num)
{
    int count=0;
    while (num)
	{
		if ((num & 1) == 1)
			count++;
		num = num >> 1;
	}
	return count;
}


/**
 * @brief Solve the questionMatrix and save the result in solvedMatrix
 * 
 * @param [in]questionMatrix a 9*9 matrix
 * @param [out]solvedMatrix a 9*9 matrix
 * @return TRUE: question have unique solution and solved
 * @return FALSE: question is not completely solved
 */
bool SolveGame(int questionMatrix[9][9],int (&solvedMatrix)[9][9])
{
    short questionMatrixasbit[9][9];
    for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
            {
                if(questionMatrix[i][j]!=0) questionMatrixasbit[i][j] = pow(2,questionMatrix[i][j]-1);
                else questionMatrixasbit[i][j]=0;
            }

    short sum, sum_row, sum_col, sum_squ;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            if (questionMatrixasbit[i][j] == 0) // 排除已填的空
            {
                sum_squ = 0;
                for (int i0 = i / 3 * 3; i0 < i / 3 * 3 + 3; i0++) // 遍历小九宫，找出已有数
                    for (int j0 = j / 3 * 3; j0 < j / 3 * 3 + 3; j0++)
                            sum_squ += questionMatrixasbit[i0][j0]; // 宫中不可能数集合
                sum_row = 0;
                for (int j0 = 0; j0 < 9; j0++) // 遍历行，找出已有数
                        sum_row += questionMatrixasbit[i][j0]; // 行不可能数集合
                sum_col = 0;
                for (int i0 = 0; i0 < 9; i0++) // 遍历列，找出已有数
                        sum_col += questionMatrixasbit[i0][j]; // 列不可能数集合
                sum = sum_squ | sum_row | sum_col;	 // 行、列、宫不可能数并集
                sum = ~sum;			 // 从n中排除不可能数,原理：&1不变，&0变成0
                if(CountOneBit(sum)==1)
                {
                    solvedMatrix[i][j]=log2(sum)+1;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                solvedMatrix[i][j]=questionMatrix[i][j];
            }
            
        }
    
    return true;
}