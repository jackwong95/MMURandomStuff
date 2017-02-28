#include "Analysis.hpp"

/** Constructor to initiate private variables.
 *
 * Input: text, the text input
 *        pattern, the pattern to be matched
 *
 */
Analysis::Analysis(const string& text, const string& pattern) {
    
    this->text = text;
    this->pattern = pattern;
    
    this->naiveRun();
    this->boyerMooreRun();
    this->horspoolRun();
}


/** Function to calculate naiveTime
 *
 */
void Analysis::naiveRun() {
    
    int n = (int) text.length(), m = (int) pattern.length();
    
    auto start = chrono::system_clock::now();
    
    for (int i = 0; i < n - m; ++i)
        for (int j = 0; j < m; ++j)
            if (text[i+j] != pattern[j]) break;
    
    auto end = chrono::system_clock::now();
    this->naive = chrono::duration_cast<std::chrono::microseconds>(end - start);
}


/** Function to calculate boyerMooreTime
 *
 */
void Analysis::boyerMooreRun() {
    
    int n = (int) text.length(), m = (int) pattern.length();
    
    auto start = chrono::system_clock::now();
    
    LastOccurenceTable table(this->pattern);
    
    int i = m - 1;
    int j = m - 1;
    
    while (i < n) {
        
        if (text[i] == pattern[j]) {
            
            if (j == 0) {
                i = i + m;
                j = m - 1;
            }
            else {
                --i;
                --j;
            }
        }
        else {
            i = i + m - min(j, table.skip(text[i]) + 1);
            j = m - 1;
        }
    }
    
    auto end = chrono::system_clock::now();
    this->boyerMoore = chrono::duration_cast<std::chrono::microseconds>(end - start);
}



/** Function to calculate horspoolRun
 *
 */
void Analysis::horspoolRun() {
    
    int n = (int) text.length(), m = (int) pattern.length();
    
    auto start = chrono::system_clock::now();
    
    MatchTable table(this->pattern);
    
    int i = m - 1;
    while (i < n) {
        
        int t = m - 1;
        for (int j = i; j > i - m; --j) {
            if (text[j] != pattern[t]) break;
            
            --t;
        }
        
        i += table.skip(text[i]);
    }
    
    auto end = chrono::system_clock::now();
    this->horspool = chrono::duration_cast<std::chrono::microseconds>(end - start);
}

chrono::duration<double, micro> Analysis::naiveTime() { return this->naive; }
chrono::duration<double, micro> Analysis::boyerMooreTime() { return this->boyerMoore; }
chrono::duration<double, micro> Analysis::horspoolTime() { return this->horspool; }
