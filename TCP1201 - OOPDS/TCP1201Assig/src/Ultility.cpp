#include "Ultility.h"

void Ultility::displayCityDetails(City* cities)
{
    cities->display();
}

void Ultility::displayCity(vector<City*>* cities, int idx)
{
    City* tempCity = cities->at(idx);
    displayCityDetails(tempCity);
}

void Ultility::displayCity(vector<City*>* cities)
{
    for(int i = 0; i < (int)cities->size(); i ++)
    {
        City* tempCity = cities->at(i);
        displayCityDetails(tempCity);
    }
}
