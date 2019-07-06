#include <iostream>
using namespace std;
int Akm(int m, int n)
{
    if(m == 0)
        return n+1;
    else
    {
        if(n == 0)
            return Akm(m-1,1);
        else
            return Akm(m-1,Akm(m,n-1));
    }
    
}

int main()
{
    int x;
    x = Akm(2,3);
    cout << x << endl;

    return 0;
}