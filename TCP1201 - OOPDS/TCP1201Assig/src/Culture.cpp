#include "Culture.h"

Culture::Culture(int _id, int _typeID, double _entranceFee, string _name)
:Attraction(_id, _typeID, _name), entranceFee(_entranceFee)
{
    //ctor
}

Culture::~Culture()
{
    //dtor
}

void Culture::setEntranceFee(double _entranceFee)
{
    entranceFee = _entranceFee;
}

void Culture::display()
{
    Attraction::display();
    cout << "Attraction type : culture " << endl;
    cout << "Attraction entrance fee : " << entranceFee << endl;
}
