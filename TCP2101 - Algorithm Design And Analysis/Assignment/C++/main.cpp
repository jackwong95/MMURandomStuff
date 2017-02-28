#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include "Analysis.hpp"
#include "BoyerMoore.hpp"
#include "BoyerMooreHorspool.hpp"

using namespace std;

void plainTestBoyerMoore();
void plainTestHorspool();
void fileTestBoyerMoore();
void fileTestHorspool();
void runAnalysis();


int main() {
    
    string choice;
    cout << "Q5. Boyer Moore's Algorithm\n\nEnter:\n" <<
            "1. to test simple input and match.\n" <<
            "2. to read a file and match a pattern.\n" <<
            "3. to generate report of running time.\n" <<
            "\n==> ";
    
    getline(cin, choice);
    cout << "\n";
    
    if (choice == "1") {
        
        cout << "i. Boyer-Moore's.\n" <<
                "ii. Boyer-Moore-Horspool's.\n" <<
                "\n==> ";
        
        getline(cin, choice);
        cout << "\n";
        
        if (choice == "i") plainTestBoyerMoore();
        else if (choice == "ii") plainTestHorspool();
    }
    else if (choice == "2") {
        
        cout << "i. Boyer-Moore's.\n" <<
        "ii. Boyer-Moore-Horspool's.\n" <<
        "\n==> ";
        
        getline(cin, choice);
        cout << "\n";
        
        if (choice == "i") fileTestBoyerMoore();
        else if (choice == "ii") fileTestHorspool();
    }
    else if (choice == "3") runAnalysis();
    
    return 0;
}


/** Function to generate a csv file for running time.
 *
 */
void runAnalysis() {
    
    int trials;
    cout << "Enter number of trials ==> ";
    cin >> trials;
    
    srand((int) time(NULL));
    ofstream file("Report.txt");
    
    static const string alphanum = "0123456789!@#$%^&*ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int length = (int) alphanum.length();
    
    if (file.is_open()) {
    
        file << "length-of-text, length-of-pattern, Naive, Boyer-Moore, Horspool\n";
        
        for (int i = 0; i < trials; ++i) {
            
            int n = (rand() % 2000) + 1, m = (rand() % 200) + 1;
            string text, pattern;
            
            for (int j = 0; j < n; ++j) text += alphanum[rand() % length];
            for (int j = 0; j < m; ++j) pattern += alphanum[rand() % length];
        
            Analysis a(text, pattern);
            file << n << "," << m
            << "," << a.naiveTime().count()
            << "," << a.boyerMooreTime().count()
            << "," << a.horspoolTime().count()
            << endl;
        }
    }
    else {
        
        cout << "Unable to open file\n";
        return;
    }
    
    file.close();
}


/** Function to accept small inputs.
 *
 */
void plainTestBoyerMoore() {
    
    string input, pattern;
    cout << "Enter text ==> ";
    getline(cin, input);
    
    cout << "Enter pattern ==> ";
    getline(cin, pattern);
    
    BoyerMoore test(input, pattern);
    test.printLocations();
    if (input.size() <= 60) test.simulate();
}


/** Function to accept small inputs.
 *
 */
void plainTestHorspool() {
    
    string input, pattern;
    cout << "Enter text ==> ";
    getline(cin, input);
    
    cout << "Enter pattern ==> ";
    getline(cin, pattern);
    
    BoyerMooreHorspool test(input, pattern);
    test.printLocations();
    if (input.size() <= 60) test.simulate();
}


/** Function to read a text file.
 *
 */
void fileTestBoyerMoore() {
    
    string input;
    ifstream file;
    
    cout << "Enter input file.\n";
    cout << "File Path ==> ";
    getline(cin, input);
    
    file.open(input);
    if (file.is_open()) {
        
        string text;
        while (getline(file, input)) text = text + input;
        
        for (int i = 0; i < text.size(); ++i)
            if ((int) text[i] < 32 || (int) text[i] >= 127)
                text[i] = ' ';
        
        cout << "Enter pattern ==> ";
        getline(cin, input);
        
        BoyerMoore test(text, input);
        test.printLocations();
        if (text.size() <= 60) test.simulate();
    }
    else {
        
        cout << "   Error: unable to open file.\n\n";
        return;
    }
    
    file.close();
}


/** Function to read a text file.
 *
 */
void fileTestHorspool() {
    
    string input;
    ifstream file;
    
    cout << "Enter input file.\n";
    cout << "File Path ==> ";
    getline(cin, input);
    
    file.open(input);
    if (file.is_open()) {
        
        string text;
        while (getline(file, input)) text = text + input;
        
        for (int i = 0; i < text.size(); ++i)
            if ((int) text[i] < 32 || (int) text[i] >= 127)
                text[i] = ' ';
        
        cout << "Enter pattern ==> ";
        getline(cin, input);
        
        BoyerMooreHorspool test(text, input);
        test.printLocations();
        if (text.size() <= 60) test.simulate();
    }
    else {
        
        cout << "   Error: unable to open file.\n\n";
        return;
    }
    
    file.close();
}
