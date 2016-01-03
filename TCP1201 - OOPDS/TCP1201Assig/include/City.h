#ifndef CITY_H
#define CITY_H

#include <iostream>

#include <string>
#include <vector>
#include "Attraction.h"

using namespace std;

class City
{
    public:
        City(int _id = -1, string _name="Untitled");
        virtual ~City();
        void display();
        void setID(int x);
        void setName(string name);
        void addAttraction(Attraction* att);
        vector<Attraction*> getAttraction(){return attractions;}
        int getID(){ return id; }
        string getName(){ return name; }
    private:
        int id;
        string name;
        vector<Attraction*> attractions;
};

#endif // CITY_H