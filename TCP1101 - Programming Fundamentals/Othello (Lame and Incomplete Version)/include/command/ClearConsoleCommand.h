/**********|**********|**********|
Program: ClearConsoleCommand.h
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/
#ifndef CLEARCONSOLECOMMAND_H_INCLUDED
#define CLEARCONSOLECOMMAND_H_INCLUDED
/// using ultilities header for referencing.
#include "Ultis.h"
//!  A sub-class ClearConsoleCommand of Command class.
/*!
  An interface class for sub-classes to inherits.
*/
class ClearConsoleCommand: public Command
{
    public:
      /**
       * An empty constructor.
       */
        ClearConsoleCommand()
        {
        }
      /**
       * A virtual void member taking no arguments this function executes a certain command for different execution.
       * This function overrides the interface class from abstract to concrete function.
       */
        void execute()
        {
            ultis::clearConsole();
        }
};

#endif // CLEARCONSOLECOMMAND_H_INCLUDED
