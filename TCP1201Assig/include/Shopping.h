#ifndef SHOPPING_H
#define SHOPPING_H

#include <vector>
#include <string>

#include "Attraction.h"

using namespace std;

class Shopping : private Attraction
{
    public:
        Shopping();
        virtual ~Shopping();
    protected:
    private:
        vector<string>* Malls;

};

#endif // SHOPPING_H
