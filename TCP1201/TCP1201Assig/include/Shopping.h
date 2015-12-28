#ifndef SHOPPING_H
#define SHOPPING_H

#include <vector>
#include <string>

#include "Attraction.h"

using namespace std;

class Shopping : public Attraction
{
    public:
        Shopping(int _id = -1, int _typeID = -1, string _name="Untitled");
        virtual ~Shopping();
        void display();
        void addMall(string toAdd);
        void removeMall(string toRemove);
        vector<string> getMalls() {return malls;}
    private:
        vector<string> malls;

};

#endif // SHOPPING_H
