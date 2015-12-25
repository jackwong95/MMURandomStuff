#ifndef CITY_H
#define CITY_H

#include <iostream>

#include <string>
#include <vector>

using namespace std;

class Attraction;

class City
{
    public:
        static int globalCityID;
        City(int _population=-1, int _touristNumber=-1, int _numberOfAttractions=-1, string _name="Untitled");
        virtual ~City();
        void display();
        void setID(int x);
    protected:
    private:
        int id;
        int population;
        int touristNumber;
        int numberOfAttractions;
        string name;
        vector<Attraction>* attractions;
};

#endif // CITY_H
