#include "Sport.h"

Sport::Sport(int _id, int _typeID, int _ageLimit, string _name)
:Attraction(_id, _typeID, _name), ageLimit(_ageLimit)
{
    //ctor
}

Sport::~Sport()
{
    //dtor
}

void Sport::setAgeLimit(int _ageLimit)
{
    ageLimit = _ageLimit;
}

void Sport::display()
{
    Attraction::display();
    cout << "Attraction type : sport " << endl;
    cout << "Attraction age limit : " << ageLimit << endl;
}

