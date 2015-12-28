#include "City.h"
#include "Attraction.h"


City::City(int _id, string _name) :
    id(_id), name(_name)
{
}

void City::setID(int x)
{
    id = x;
}

void City::display()
{
    cout << "City Name : " << name << " , " << "City ID : " << id << endl;
}

void City::setName(string _name)
{
    name = _name;
}

void City::addAttraction(Attraction* att)
{
    attractions.push_back(att);
}

City::~City()
{
}
