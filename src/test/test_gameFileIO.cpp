#include<iostream>

#include"gameFileIO.h"

int main()
{
    GameFile outFile("out.txt",GameFile::OUT);

    int mat1[81]={1,2,3,4,9};
    if(outFile.writeMatrixas1D(mat1)) cout<<"success!\n";
    else cout<<"failed, Error code:"<<outFile.GetLastError()<<'\n';
    outFile.writeMatrixas1D(mat1);

    int mat2[81]={9,1,3,10};
    if(outFile.writeMatrixas1D(mat2)) cout<<"success!\n";
    else cout<<"failed, Error code:"<<outFile.GetLastError()<<'\n';

    if(outFile.readMatrixas1D(mat2) ) cout<<"success!\n";
    else cout<<"failed, Error code:"<<outFile.GetLastError()<<'\n';
    
    // int mat3[12]={};
    // if(outFile.writeMatrixas1D(mat3)) cout<<"success!\n";


    GameFile inFile("in.txt",GameFile::IN);

    int mat4[81]={};
    if(inFile.readMatrixas1D(mat4) ) cout<<"success!\n";
    else cout<<"failed, Error code:"<<inFile.GetLastError()<<'\n';
    cout<<mat4[0]<<'\n';

    int mat5[81]={};
    if(inFile.readMatrixas1D(mat5) ) cout<<"success!\n";
    else cout<<"failed, Error code:"<<inFile.GetLastError()<<'\n';
    cout<<mat5[0]<<'\n';

    if(inFile.writeMatrixas1D(mat5) ) cout<<"success!\n";
    else cout<<"failed, Error code:"<<inFile.GetLastError()<<'\n';

    int mat6[81]={};
    if(inFile.readMatrixas1D(mat6) ) cout<<"success!\n";
    else cout<<"failed, Error code:"<<inFile.GetLastError()<<'\n';
    // cout<<mat5[0]<<'\n';

    int mat7[81]={};
    if(inFile.readMatrixas1D(mat7) ) cout<<"success!\n";
    else cout<<"failed, Error code:"<<inFile.GetLastError()<<'\n';
    if(inFile.readMatrixas1D(mat7) ) cout<<"success!\n";
    else cout<<"failed, Error code:"<<inFile.GetLastError()<<'\n';

    // int mat1[9][9]={{1,2,3,4,5},{3,4,5}};
    // if(outFile.writeMatrix(mat1)) cout<<"success!\n";
    // else cout<<"failed, Error code:"<<outFile.GetLastError()<<'\n';
    return 0;

}