#ifndef CULTURE_H
#define CULTURE_H

#include "Attraction.h"

class Culture : public Attraction
{
    public:
        Culture(int _id = -1, int _typeID = -1, double entranceFee = 0.0d, string _name="Untitled");
        virtual ~Culture();
        void display();
        void setEntranceFee(double entranceFee);
        double getEntranceFee() {return entranceFee;}
    private:
        double entranceFee;
};

#endif // CULTURE_H
