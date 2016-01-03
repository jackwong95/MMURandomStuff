/**********|**********|**********|
Program: BannerView.cpp
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/
#include "BannerView.h"
//mini library I made
#include "Ultis.h"
//for system
#include <cstdlib>
//for exception handling
#include <stdexcept>
//for printing out
#include <iostream>
//for timer please dont kill me for the .h, this is built in library.. but i don't know why you need .h :3
#include <unistd.h>
//constructor of BannerView
BannerView::BannerView()
{
}
//print out starting banner
void BannerView::printView()
{
    try
    {
        char str[] = {"Welcome to my game!"};
        for(unsigned int i=0;i<sizeof(str)/sizeof(str[0]);i++) {
            std::cout << str[i];
            usleep(100000);
        }
        std::cout << "\n\n";
        ultis::readAndPrint("assets/hypnotoad.txt");
        system("PAUSE");
        ultis::clearConsole();
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << "\n";
    }
}
