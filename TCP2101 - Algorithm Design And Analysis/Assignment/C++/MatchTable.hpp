#ifndef MatchTable_hpp
#define MatchTable_hpp

#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

class MatchTable {
    
private:
    
    static const int non = 32, ascii = 127 - non;
    int table[ascii];
    string pattern;
    
    void init();
    
public:
    
    MatchTable(const string&);
    
    int skip(char) const;
    void print() const;
};

#endif /* MatchTable_hpp */
