#include "Graphmtx.h"
#include "Graphlnk.h"
#include <iostream>

int main()
{
    Graphmtx<int,int> G(10);
    cin >> G;
    cout << G;
    
    return 0;
}