#ifndef LastOccurenceTable_hpp
#define LastOccurenceTable_hpp

#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

class LastOccurenceTable {
    
private:
    
    static const int non = 32, ascii = 127 - non;
    int table[ascii];
    string pattern;
    
    void init();
    
public:
    
    LastOccurenceTable(const string&);
    
    int skip(char) const;
    void print() const;
};

#endif /* LastOccurenceTable_hpp */
