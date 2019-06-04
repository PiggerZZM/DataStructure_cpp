#include <iostream>
#include <cstring>
void Hanoi(int n, String A, String B, String C)
{
    // 将A的n个盘子借助B移动到C
    if (n == 1)
        cout << "Move top disk from peg" << A << "to peg" << C << endl;
    else
    {
        Hanoi(n-1, A, C, B);
        cout << "Move top disk form peg" << A << "to peg" << C << endl;
        Hanoi(n-1, B, A, C);
    }
}
