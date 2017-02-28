/**********|**********|**********|
Program: View.h
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/
#ifndef VIEW_H_INCLUDED
#define VIEW_H_INCLUDED
//!  A View class.
/*!
  An interface class for sub-classes to inherits.
*/
class View
{
      /**
       * A virtual void member taking no arguments this function prints out the View.
       */
    public:
        virtual void printView() = 0;
};

#endif // VIEW_H_INCLUDED
