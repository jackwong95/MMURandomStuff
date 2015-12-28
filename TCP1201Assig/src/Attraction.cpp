#include "Attraction.h"

Attraction::Attraction(int _id, int _typeID, string _name)
:id(_id), typeID(_typeID), name(_name)
{
    //ctor
}

Attraction::~Attraction()
{
    //dtor
}

void Attraction::display()
{
    cout << "Attraction name : " << name << endl;
    cout << "Attraction id : " << id << endl;
}

void Attraction::setID(int _id)
{
    id = _id;
}

void Attraction::setName(string _name)
{
    name = _name;
}
