#include "SparseMatrix.h"
#include <iostream>
using namespace std;

int main()
{
    SparseMatrix<int> sm(12);
    SparseMatrix<int> sm2(3,4);
    sm = sm2;
    sm.FastTranspose();
    sm2.Transpose();
    sm.Add(sm2);
    return 0;
}