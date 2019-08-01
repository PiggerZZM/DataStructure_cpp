#include "UFset.h"
#include <iostream>
using namespace std;

int main()
{
    UFSets us(6);
    us.Union(3,5);
    us.Union(0,1);
    us.Union(us.Find(1),4);
    us.Union(us.Find(4),2);
    cout << us.Find(2) << endl << us.Find(4) << endl << us.Find(5) << endl;
    us.Union(us.Find(5),us.Find(2));
    cout << us.Find(2) << endl << us.Find(4) << endl << us.Find(5) << endl;
    
    return 0;
}