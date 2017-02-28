/**********|**********|**********|
Program: Command.h
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/
#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED
//!  A Command class.
/*!
  An interface class for sub-classes to inherits.
*/
class Command
{
public:
    /**
    * A virtual void member taking no arguments this function prints out the View.
    */
    virtual void execute() = 0;
};

#endif // COMMAND_H_INCLUDED
