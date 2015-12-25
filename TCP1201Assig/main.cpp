#include <iostream>
#include <vector>
#include "Ultility.h"

using namespace Ultility;
using namespace std;


int main()
{
    //int _id, int _population, int _touristNumber, int _numberOfAttractions, string _name
    vector<City*> cities;
    cities.push_back(new City(10, 3, 6, "MY CITY!"));
    cities.push_back(new City(10, 3, 6, "MY CITY4!"));
    cities.push_back(new City());
    Ultility::displayCity(&cities);

    for (int i = 0; i < cities.size(); i++)
    {
        delete cities[i];
    }

    return 0;
}
