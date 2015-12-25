#include "City.h"
#include "Attraction.h"


City::City(int _population, int _touristNumber, int _numberOfAttractions, string _name) :
    population(_population), touristNumber(_touristNumber), numberOfAttractions(_numberOfAttractions)
    , name(_name)
{
        attractions = new vector<Attraction>();
}

void City::setID(int x)
{
    id = x;
}

void City::display()
{
    cout << "City Name : " << name << " , " << "City ID : " << id << endl;
}


City::~City()
{
    delete attractions;
    attractions = NULL;
}
