#include "minheap.h"
#include <iostream>
using namespace std;

int main()
{
    int x;
    int arr[10] = {2,8,9,41,3,22,6,1,23,9};
    MinHeap<int> mh(arr,10);
    mh.Insert(99);
    mh.RemoveMin(x);
    
    return 0;
}