#include <iostream>
#include "LinkedList.h"

using namespace std;

int main()
{
    LinkedList<int> ll;
    ll.push_head(1);
    ll.push_tail(2);
    ll.push_head(0);
    ll.push_tail(3);
    cout<<"Popped head : "<<ll.pop_head()<<endl;
    ll.push_head(0);
    ll.removeAt(0);
    ll.push_head(0);
    ll.push_tail(4);
    ll.removeAt(ll.sz()-1);
    ll.push_tail(4);
    cout<<"Popped tail : "<<ll.pop_tail()<<endl;
    ll.push_tail(4);
    ll.display();
    ll.clr();
    cout<<"Cleared list"<<endl;
    ll.display();
    cout<<"Reserved 10 extra spaces from tail"<<endl;
    ll.reserve_from_tail(10);
    ll.display();
    ll.clr();
    cout<<"Cleared list"<<endl;
    ll.display();
    ll.reserve_from_head(3);
    ll.display();
    ll.clr();
    return 0;
}
