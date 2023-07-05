#include"gameGenerator.h"
#include<iostream>

template<int length>
extern void GetRandomArrange(int (&array)[length]);


int main()
{
    // test for GetRandomArrange()
    int arr[9];
    GetRandomArrange(arr);
    for(int i=0;i<9;i++)
        std::cout<<arr[i]<<'\t';
    std::cout<<'\n';


    int mat1[9][9];
    CreateSolvedGame(mat1);
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++)
            std::cout<<mat1[i][j];
        std::cout<<'\n';
    }

    return 0;
}