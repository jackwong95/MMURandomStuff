#include "BoyerMoore.hpp"

/** Constructor.
 *
 * Input: input, the input string.
 *        pattern, the pattern to be found.
 *
 */
BoyerMoore::BoyerMoore(const string &input, const string &pattern) {
    
    this->matchSize = 10;
    this->size = 0;
    this->matchLocations = new int[matchSize];
    this->text = input;
    this->pattern = pattern;
    this->table = new LastOccurenceTable(pattern);
    
    this->run();
}


/** Destructor to free memory.
 *
 */
BoyerMoore::~BoyerMoore() {
    
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
void BoyerMoore::push_back(const int &index) {
    
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
void BoyerMoore::printLocations() const {
    
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
void BoyerMoore::run() {
    
    int i = (int) pattern.size() - 1;
    int j = (int) pattern.size() - 1;
    
    while (i < text.size()) {
        
        // If last character match, go back and check all.
        if (text[i] == pattern[j]) {
            
            if (j == 0) {
                push_back(i);
                i = i + (int) pattern.size();
                j = (int) pattern.size() - 1;
            }
            else {
                --i;
                --j;
            }
        }
        // If mismatch. (jump and reset j)
        else {
            i = i + (int) pattern.size() - min(j, table->skip(text[i]) + 1);
            j = (int) pattern.size() - 1;
        }
    }
}


/** Function to display the running algorithm
 *
 */
void BoyerMoore::simulate() const {
    
    table->print();
    
    int c = 1;
    cout << "\nSimulating:\n";
    
    int i = (int) pattern.size() - 1;
    int j = (int) pattern.size() - 1;
    
    bool print = true;
    while (i < text.size()) {
        
        if (print) {
            string pause;
            getline(cin, pause);
            cout << c << ". " << this->text << endl;
            for (int k = 10; k <= c; k *= 10) cout << " ";
            for (int k = 0; k <= i - (int) pattern.size() + 3; ++k) cout << " ";
            cout << pattern << endl << endl;
        }
        
        if (text[i] == pattern[j]) {
            if (j == 0) {
                print = true;
                cout << "   ** Match Found **\n" << endl;
                i = i + (int) pattern.size();
                j = (int) pattern.size() - 1;
            }
            else {
                print = false;
                --i;
                --j;
            }
        }
        else {
            print = true;
            i = i + (int) pattern.size() - min(j, table->skip(text[i]) + 1);
            j = (int) pattern.size() - 1;
        }
        if (print) ++c;
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
