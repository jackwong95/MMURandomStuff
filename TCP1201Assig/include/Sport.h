#ifndef SPORT_H
#define SPORT_H

#include "Attraction.h"

class Sport : private Attraction
{
    public:
        Sport();
        virtual ~Sport();
    protected:
    private:
        int ageLimit;
};

#endif // SPORT_H
