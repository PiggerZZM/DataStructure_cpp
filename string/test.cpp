#include "AString.h"
#include <iostream>
using namespace std;

int main()
{
    char str[10] = "abc";
    AString mystr(str);
    AString mystr1 = mystr(1,1);
    mystr += mystr1;
    char ch = mystr[3];
    int len = mystr.Length();
    int index_b = mystr.Find(mystr1);
    printf("%d,%d,%c\n",index_b,len,ch);
    AString b("b");
    AString xybb("xybb");
    mystr.replace(b,xybb);
    mystr.replace(xybb,b);

    return 0;
}