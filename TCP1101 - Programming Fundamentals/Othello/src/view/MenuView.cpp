/**********|**********|**********|
Program: MenuView.cpp
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/
#include "MenuView.h"
#include "Ultis.h"

#include <iostream>

MenuView::MenuView()
{
}
void MenuView::printView()
{
    try
    {
        ultis::readAndPrint("assets/UserOptionStartingScreen.txt");
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << "\n";
    }
}
