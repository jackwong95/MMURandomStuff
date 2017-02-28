/**********|**********|**********|
Program: main.cpp
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/

#include "MenuManager.h"
#include <iostream>
#include <windows.h>

using namespace std;

int main(){

    char str[] = {"Welcome to my game!"};
    for(int i=0;i<sizeof(str)/sizeof(str[0]);i++) {
        cout << str[i];
        Sleep(250);
    }
    cout << endl << endl;
    PrintManager::getInstance()->printPage("hypnotoad.txt");
    system("pause");
    MenuManager::clearConsole();
    MenuManager::getInstance()->start();
    return 0;
}
