#ifndef Analysis_hpp
#define Analysis_hpp

#include <iostream>
#include <chrono>
#include <string>
#include "LastOccurenceTable.hpp"
#include "MatchTable.hpp"

using namespace std;

class Analysis {
    
private:
    
    string text, pattern;
    chrono::duration<double, micro> naive, boyerMoore, horspool;
    
    void naiveRun();
    void boyerMooreRun();
    void horspoolRun();
    
public:
    
    Analysis(const string& text, const string& pattern);
    
    chrono::duration<double, micro> naiveTime(), boyerMooreTime(), horspoolTime();
};

#endif /* Analysis_hpp */
