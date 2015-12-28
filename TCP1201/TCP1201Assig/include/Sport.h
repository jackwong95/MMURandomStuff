#ifndef SPORT_H
#define SPORT_H

#include "Attraction.h"

class Sport : public Attraction
{
    public:
        Sport(int _id = -1, int _typeID = -1, int _ageLimit = -1, string _name="Untitled");
        virtual ~Sport();
        void display();
        void setAgeLimit(int ageLimit);
        int getAgeLimit() {return ageLimit;}
    private:
        int ageLimit;
};

#endif // SPORT_H
