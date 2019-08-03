#include "BSTree.h"
#include<iostream>
using namespace std;

int main()
{
    BSTree<int,int> bst(-1);
    bst.PrintTree();
    cout << endl;
    cout << "max = " << bst.Max() << endl;
    cout << "min = " << bst.Min() << endl;
    bst.Insert(10);
    bst.Remove(10);
    bst.PrintTree();

    return 0;
}