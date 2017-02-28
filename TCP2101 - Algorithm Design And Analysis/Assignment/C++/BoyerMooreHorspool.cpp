#include "BoyerMooreHorspool.hpp"

/** Constructor.
 *
 * Input: input, the input string.
 *        pattern, the pattern to be found.
 *
 */
BoyerMooreHorspool::BoyerMooreHorspool(const string &input, const string &pattern) {
    
    this->matchSize = 10;
    this->size = 0;
    this->matchLocations = new int[matchSize];
    this->text = input;
    this->pattern = pattern;
    this->table = new MatchTable(pattern);
    
    this->run();
}


/** Destructor to free memory.
 *
 */
BoyerMooreHorspool::~BoyerMooreHorspool() {
    
    delete this->matchLocations;
    this->matchLocations = nullptr;
    
    delete this->table;
    this->table = nullptr;
}


/** Function to insert an integer to matchLocations and will resize matchLocations if needed to.
 *
 * Input: index, an integer
 *
 */
void BoyerMooreHorspool::push_back(const int &index) {
    
    if (matchSize == 0) ++matchSize;
    
    if (++size > matchSize) {
        
        // resize
        int* temp = matchLocations;
        
        matchSize *= 2;
        matchLocations = new int[matchSize];
        
        for (int i = 0; i < size; ++i) {
            
            matchLocations[i] = temp[i];
        }
        
        delete temp;
        temp = nullptr;
    }
    
    matchLocations[size-1] = index;
}


/** Function to print the first index locations where the pattern matches.
 *
 */
void BoyerMooreHorspool::printLocations() const {
    
    bool none = true;
    cout << "Matched at locations: ";
    for (int i = 0; i < size; ++i) {
        
        none = false;
        cout << matchLocations[i];
        
        if (i < size - 1) cout << ", ";
    }
    if (none) cout << " NULL";
    cout << endl;
}


/** Function to run Boyer-Moore String Search Algorithm.
 *
 */
void BoyerMooreHorspool::run() {
    
    for (int i = (int) pattern.size() - 1; i < (int) text.size(); ) {
        
        int t = (int) pattern.size() - 1;
        for (int j = i; j > i - (int) pattern.size(); --j, --t) {
            
            if (text[j] != pattern[t]) break;
        }
        
        if (t == -1) push_back(i - (int) pattern.size() + 1);
        i += table->skip(text[i]);
    }
}


/** Function to display the running algorithm
 *
 */
void BoyerMooreHorspool::simulate() const {
    
    table->print();
    
    int c = 1;
    cout << "\nSimulating:\n";
    for (int i = (int) pattern.size() - 1; i < (int) text.size(); ++c) {
        
        string pause;
        getline(cin, pause);
        cout << c << ". " << this->text << endl;
        for (int j = 10; j <= c; j *= 10) cout << " ";
        for (int j = 0; j <= i - (int) pattern.size() + 3; ++j) cout << " ";
        cout << pattern << endl << endl;
        
        int t = (int) pattern.size() - 1;
        for (int j = i; j > i - (int) pattern.size(); --j, --t) {
            
            if (text[j] != pattern[t]) break;
        }
        if (t == -1) cout << "   ** Match Found **\n" << endl;
        
        i += table->skip(text[i]);
    }
    
    cout << "\nStats:\n";
    cout << "+---+---+\n";
    cout << "| n |";
    printf("%3d|\n", (int) text.size());
    cout << "+---+---+\n";
    cout << "| m |";
    printf("%3d|\n", (int) pattern.size());
    cout << "+---+---+\n";
    
    cout << "\nwhere n is the length of text.";
    cout << "\n      m is the length of pattern.";
    cout << "\n\nTotal operations = " << (c-1) << endl;
}
