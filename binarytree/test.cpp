#include "BinaryTree.h"
#include <iostream>
using namespace std;

int main()
{
    BinaryTree<char> t1;
    cin >> t1;
    cout << t1 << endl;
    cout << "h = " << t1.Height() << endl << "s = " << t1.Size() << endl;
    BinaryTree<char> t2(t1);
    cout << t2 << endl;
    cout << t2.IsEmpty() << endl;
    const char b = 'B';
    cout << t2.Find(b)->data << endl;

    return 0;
}