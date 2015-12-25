#ifndef ATTRACTION_H
#define ATTRACTION_H

#include <string>

using namespace std;

class Attraction
{
    public:
        Attraction();
        virtual ~Attraction();
        void display();
    private:
        int id;
        int typeID;
        string name;
};

#endif // ATTRACTION_H
