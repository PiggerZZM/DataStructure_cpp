#include "Graphmtx.h"
#include "Graphlnk.h"
#include <iostream>

int main()
{
    Graphmtx<int,int> G(10);
    cin >> G;
    MinSpanTree<int,int> MST;
    G.Kruskal(MST);
    
    return 0;
}