/**********|**********|**********|
Program: GameController.cpp
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/
#ifndef HELPCOMMAND_H
#define HELPCOMMAND_H
/// using Command header for referencing.
#include "Command.h"
/// using View header for referencing.
#include "View.h"
//!  A sub-class HelpCommand of Command class.
/*!
  An interface class for sub-classes to inherits.
*/
class HelpCommand: public Command
{
    public:
      /**
       * print out the help command from a view.
       * \param view first argument.
       */
        HelpCommand(View* view)
        {
            view_ = view;
        }
      /**
       * print the view.
       */
        void execute()
        {
            view_->printView();
        }
    private:
    //! A private variable.
    /*!
      pointer of view.
    */
        View* view_;
};

#endif // HELPCOMMAND_H
