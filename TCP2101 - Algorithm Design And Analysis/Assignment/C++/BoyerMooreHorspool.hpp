#ifndef BoyerMooreHorspool_hpp
#define BoyerMooreHorspool_hpp

#include <iostream>
#include <string>
#include "MatchTable.hpp"

using namespace std;

class BoyerMooreHorspool {
    
private:
    
    int matchSize, size;
    int* matchLocations;
    string text, pattern;
    MatchTable* table;
    
    void run();
    void push_back(const int&);
    
public:
    
    BoyerMooreHorspool(const string &input, const string &pattern);
    ~BoyerMooreHorspool();
    
    void printLocations() const;
    void simulate() const;
    
};

#endif /* BoyerMoore_hpp */
