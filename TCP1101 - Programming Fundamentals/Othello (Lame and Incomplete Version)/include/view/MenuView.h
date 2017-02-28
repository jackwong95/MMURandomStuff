/**********|**********|**********|
Program: MenuView.h
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/
#ifndef MENUVIEW_H
#define MENUVIEW_H
/// View header used for inheritance.
#include "View.h"
//!  A sub-class MenuView of View class.
/*!
  An interface class for sub-classes to inherits.
*/
class MenuView: public View
{
    public:
      /**
       * An empty constructor.
       */
        MenuView();
      /**
       * A virtual void member taking no arguments this function prints out the View.
       * This function overrides the interface class from abstract to concrete function.
       */
        void printView();
};

#endif // MENUVIEW_H
