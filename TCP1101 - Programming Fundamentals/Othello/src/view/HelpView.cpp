/**********|**********|**********|
Program: HelpView.cpp
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/
#include "HelpView.h"
#include "Ultis.h"

#include <iostream>

HelpView::HelpView()
{
    //ctor
}
void HelpView::printView()
{
    try
    {
        ultis::readAndPrint("assets/Instructions.txt");
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << "\n";
    }
}
