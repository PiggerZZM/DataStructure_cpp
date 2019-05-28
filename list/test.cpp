#include <iostream>
#include <cstdlib>
#include "SeqList.h"
#include "LinkList.h"
#include "DblList.h"
#include "StaticList.h"


using namespace std;

int main()
{
    /*
    // 顺序表的测试
    int x;
    SeqList<int> sl;
    sl.input();
    sl.Insert(2,999);
    sl.Remove(0,x);
    x = sl.Search(999);
    cout << x << endl;
    sl.setData(0,10000);
    sl.getData(0,x);
    cout << x << endl;
    SeqList<int> sl2;
    sl2 = sl;
    sl.output();
    sl2.output();
    */
    
    // 单链表的测试
    LinkList<int> ll(14);
    int y = ll.Length();
    printf("%d\n",y);
    printf("%d\n",ll.Search(14)->data);
    printf("%d\n",ll.Locate(1)->data);
    int x;
    ll.setData(1,16);
    ll.getData(1,x);
    printf("%d\n",x);
    ll.Insert(0,134);
    ll.Insert(2,999);
    ll.output();
   /* LinkList<int> ll2;
    ll2.inputFront(0);
    ll2.output();
    ll2.inputRear(0);
    ll2.output();
    ll2 = ll;
    ll2.output();*/
    printf("%d\n",ll.max()->data);
    printf("%d\n",ll.number(999));
    int a[3] = {0,1,2};
    ll.create(a,3);
    ll.output();
    /*

    // 双向链表的测试，未完，缺output
    
    int x;
    DblList<int> Dl(0);
    Dl.Insert(0,10,1);
    Dl.Remove(1,x,1);
    

   // 静态链表的测试
    StaticList<int> Sl;
    Sl.InitList();
    printf("%d\n",Sl.IsEmpty());
    Sl.Append(10);
    printf("%d\n",Sl.Length());
    int ten_index = Sl.Search(10);
    Sl.Insert(ten_index, 23);
    Sl.Remove(1);
    printf("%d\n",Sl.Length());
    */

    return 0;
}