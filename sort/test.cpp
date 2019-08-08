#include "DataList.h"
#include <iostream>
using namespace std;

int main()
{
    DataList<int> L(10),L1(10);
    cin >> L;
    L.HeapSort();
    cout << L;

    return 0;
}