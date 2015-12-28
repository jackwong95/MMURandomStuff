#ifndef ULTILITY_H
#define ULTILITY_H

#include <vector>
#include "City.h"

namespace Ultility
{
    void addCity();
    void deleteCity();
    void displayCity(vector<City*>* cities);
    void displayCity(vector<City*>* cities, int idx);
    void displayCityDetails(City* cities);
};

#endif // ULTILITY_H
