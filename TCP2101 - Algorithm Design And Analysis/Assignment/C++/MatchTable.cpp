#include "MatchTable.hpp"

/** Constructor.
 *
 * Input: pattern, the string to be matched.
 *
 */
MatchTable::MatchTable(const string &pattern) {
    
    this->pattern = pattern;
    fill_n(this->table, ascii, (int) pattern.size());
    this->init();
}


/** Function to get the skip value.
 *
 * Input: character, the character for finding its skip value.
 * Output: an integer which is the skip value for the character.
 *
 */
int MatchTable::skip(char character) const {
    
    int key = (int) character - non;
    if (key < 0 || key >= ascii) throw new out_of_range("Not a printable ASCII character");
    
    return this->table[key];
}


/** Function for initializing the table.
 *
 * Input: pattern, the string to be matched.
 *
 */
void MatchTable::init() {
    
    for (int i = 0; i < (int) pattern.size() - 1; ++i) {
        
        int key = (int) pattern[i] - non;
        if (key < 0 || key >= ascii) throw new out_of_range("Not a printable ASCII character");
        
        this->table[key] = (int) pattern.size() - i - 1;
    }
}


/** Function to print the keys and its corresponding skip value in a table.
 *
 */
void MatchTable::print() const {
    
    cout << "\nTable:\n";
    
    int unique = 0;
    for (int i = 0; i < ascii; ++i)
        if (table[i] < (int) pattern.size())
            ++unique;
    
    for (int i = 0; i <= unique; ++i) cout << "+---";
    cout << "+\n|";
    
    for (int i = 0; i < ascii; ++i)
        if (table[i] < (int) pattern.size())
            cout << " " << (char) (i + 32) << " |";
    
    cout << " * |\n";
    
    for (int i = 0; i <= unique; ++i) cout << "+---";
    cout << "+\n|";
    
    for (int i = 0; i < ascii; ++i)
        if (table[i] < (int) pattern.size())
            printf("%3d|", table[i]);
    
    printf("%3d|\n", (int) pattern.size());
    
    for (int i = 0; i <= unique; ++i) cout << "+---";
    cout << "+\n";
}
