#ifndef ATTRACTION_H
#define ATTRACTION_H

#include <string>
#include <iostream>

using namespace std;

class Attraction
{
    public:
        Attraction(int _id = -1, int _typeID = -1, string _name="Untitled");
        virtual ~Attraction();
        virtual void display();
        void setID(int _id);
        void setName(string _name);
        int getTypeID(){ return typeID;}
        int getID() {return id;}
        string getName() {return name;}
    private:
        int id;
        int typeID;
        string name;
};

#endif // ATTRACTION_H
