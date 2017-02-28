#include "LastOccurenceTable.hpp"

/** Constructor.
 *
 * Input: pattern, the string to be matched.
 *
 */
LastOccurenceTable::LastOccurenceTable(const string &pattern) {
    
    this->pattern = pattern;
    fill_n(this->table, ascii, -1);
    this->init();
}


/** Function to get the skip value.
 *
 * Input: character, the character for finding its skip value.
 * Output: an integer which is the skip value for the character.
 *
 */
int LastOccurenceTable::skip(char character) const {
    
    int key = (int) character - non;
    if (key < 0 || key >= ascii) throw new out_of_range("Not a printable ASCII character");
    
    return this->table[key];
}


/** Function for initializing the table.
 *
 * Input: pattern, the string to be matched.
 *
 */
void LastOccurenceTable::init() {
    
    for (int i = 0; i < (int) pattern.size(); ++i) {
        
        int key = (int) pattern[i] - non;
        if (key < 0 || key >= ascii) throw new out_of_range("Not a printable ASCII character");
        
        this->table[key] = i;
    }
}


/** Function to print the keys and its corresponding skip value in a table.
 *
 */
void LastOccurenceTable::print() const {
    
    cout << "\nTable:\n";
    
    int unique = 0;
    for (int i = 0; i < ascii; ++i)
        if (table[i] < (int) pattern.size() && table[i] >= 0)
            ++unique;
    
    for (int i = 0; i <= unique; ++i) cout << "+---";
    cout << "+\n|";
    
    for (int i = 0; i < ascii; ++i)
        if (table[i] < (int) pattern.size() && table[i] >= 0)
            cout << " " << (char) (i + 32) << " |";
    
    cout << " * |\n";
    
    for (int i = 0; i <= unique; ++i) cout << "+---";
    cout << "+\n|";
    
    for (int i = 0; i < ascii; ++i)
        if (table[i] < (int) pattern.size() && table[i] >= 0)
            printf("%3d|", table[i]);
    
    printf("%3d|\n", -1);
    
    for (int i = 0; i <= unique; ++i) cout << "+---";
    cout << "+\n";
}
