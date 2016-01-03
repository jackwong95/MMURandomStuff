#include "Shopping.h"

Shopping::Shopping(int _id, int _typeID, string _name)
:Attraction(_id, _typeID, _name)
{
    //ctor
}

Shopping::~Shopping()
{
    //dtor
}

void Shopping::addMall(string toAdd)
{
    malls.push_back(toAdd);
}
void Shopping::removeMall(string toRemove)
{
    for(int i = 0; i < (int)malls.size(); i ++)
    {
        malls.erase(malls.begin(), malls.begin()+3);
    }
}

void Shopping::display()
{
    Attraction::display();
    cout << "Attraction type : shopping " << endl;
    for(int i = 0; i < (int)malls.size(); i ++)
    {
        cout << "Attraction mall " << (i+1) << ": " << malls.at(i) << endl;
    }
}
