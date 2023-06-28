#include"GameFileIO.h"

GameFile::GameFile(string fileName,int mode)
{
    openMode=mode;
    switch (mode)
    {
    case IN:
        fileOperator.open(fileName,ios_base::in);
        if(!fileOperator.is_open())
        {
            cout<<"File "+fileName+" open failed!\n";
            exit(0);
        }
        break;

    case OUT:
        fileOperator.open(fileName,ios_base::out);
        break;
    
    default:
        cout<<"Why are you challenging this?\n";
        exit(0);
        break;
    };

    lastError=0;
}

GameFile::~GameFile(){}

int GameFile::GetLastError()
{
    return lastError;
}




/**
 * @brief Read matrix from file
 * 
 * @param [out]matrix a 9*9 int matrix
 * @return TRUE: matrix is read from file successfully. 
 * @return FALSE: matrix is not successfully read from file , you can use GetLastError() to get error info.
 * @warning Notice that matrix should be a 9*9 int and shouldn't be a pointer(int**). Or it will make an compile error.
 */
bool GameFile::readMatrix(int (&matrix)[9][9])
{
    if(openMode==OUT)
    {
        lastError=OPERATEMODEERROR;
        return false;
    }


    string matrixString;
    std::getline(fileOperator,matrixString,',');
    fileOperator.get();

    if(matrixString.length()!=90)
    {
        lastError=MATRIXSIZEINFILEERROR;
        return false;
    }
    for(int i=0;i<90;i++)
    {
        if(i%10==9 && matrixString[i]!='\n')
        {
            lastError=MATRIXELEMENTERROR;
            return false;
        }
        if(i%10!=9 && (matrixString[i]<'0' || matrixString[i]>'9'))
        {
            lastError=MATRIXELEMENTERROR;
            return false;
        }
    }

    stringstream matrixStringStream(matrixString);

    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            matrix[i][j]=matrixStringStream.get()-'0';
        matrixStringStream.get();

    return true;
}

/**
 * @brief Write matrix to file
 * 
 * @param [in]matrix a 9*9 int matrix
 * @return TRUE:matrix is write to file successfully. 
 * @return FALSE:matrix is not written, you can use GetLastError() to get error info.
 * @warning Notice that matrix should be a 9*9 int and shouldn't be a pointer(int**). Or it will make an compile error.
 */
bool GameFile::writeMatrix(int (&matrix)[9][9])
{
    if(openMode==IN)
    {
        lastError=OPERATEMODEERROR;
        return false;
    }

    stringstream matrixStringStream;
    for(int i=0;i<9;i++) {
        for(int j=0;j<9;j++) {
            if(matrix[i][j]<0 || matrix[i][j]>9) {
                lastError=MATRIXELEMENTERROR;
                return false;
            }
            matrixStringStream<<matrix[i][j];
        }
        matrixStringStream<<'\n';
    }
    matrixStringStream<<",\n";

    fileOperator<<matrixStringStream.str();

    return true;
}





/**
 * @brief Read matrix from file
 * 
 * @param [out]matrix a 81 int array
 * @return TRUE: matrix is read from file successfully. 
 * @return FALSE: matrix is not successfully read from file , you can use GetLastError() to get error info.
 * @warning Notice that matrix should be a 81 int and shouldn't be a pointer(int*). Or it will make an compile error.
 */
bool GameFile::readMatrixas1D(int (&matrix)[81])
{
    if(openMode==OUT)
    {
        lastError=OPERATEMODEERROR;
        return false;
    }


    string matrixString;
    std::getline(fileOperator,matrixString,',');
    fileOperator.get();

    if(matrixString.length()!=90)
    {
        lastError=MATRIXSIZEINFILEERROR;
        return false;
    }
    for(int i=0;i<90;i++)
    {
        if(i%10==9 && matrixString[i]!='\n')
        {
            lastError=MATRIXELEMENTERROR;
            return false;
        }
        if(i%10!=9 && (matrixString[i]<'0' || matrixString[i]>'9'))
        {
            lastError=MATRIXELEMENTERROR;
            return false;
        }
    }

    stringstream matrixStringStream(matrixString);

    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            matrix[i*9+j]=matrixStringStream.get()-'0';
        matrixStringStream.get();

    return true;
}

/**
 * @brief Write matrix to file
 * 
 * @param [in]matrix a 81 int array
 * @return TRUE:matrix is write to file successfully. 
 * @return FALSE:matrix is not written, you can use GetLastError() to get error info.
 * @warning Notice that matrix should be a 81 int and shouldn't be a pointer(int*). Or it will make an compile error.
 */
bool GameFile::writeMatrixas1D(int (&matrix)[81])
{
    if(openMode==IN)
    {
        lastError=OPERATEMODEERROR;
        return false;
    }

    stringstream matrixStringStream;
    for(int i=0;i<9;i++) {
        for(int j=0;j<9;j++) {
            if(matrix[i*9+j]<0 || matrix[i*9+j]>9) {
                lastError=MATRIXELEMENTERROR;
                return false;
            }
            matrixStringStream<<matrix[i*9+j];
        }
        matrixStringStream<<'\n';
    }
    matrixStringStream<<",\n";

    fileOperator<<matrixStringStream.str();

    return true;
}