#ifndef CULTURE_H
#define CULTURE_H

#include "Attraction.h"

class Culture : private Attraction
{
    public:
        Culture();
        virtual ~Culture();
    protected:
    private:
        double entranceFee;
};

#endif // CULTURE_H
