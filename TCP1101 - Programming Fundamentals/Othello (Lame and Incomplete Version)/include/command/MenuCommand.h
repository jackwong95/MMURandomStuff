/**********|**********|**********|
Program: MenuCommand.h
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/
#ifndef MENUCOMMAND_H_INCLUDED
#define MENUCOMMAND_H_INCLUDED
/// using Command header for referencing.
#include "Command.h"
/// using GameController header for referencing.
#include "GameController.h"
//!  A sub-class MenuCommand of Command class.
/*!
  An interface class for sub-classes to inherits.
*/
class MenuCommand: public Command
{
    public:
      /**
       * go back to menu from game menu.
       * \param gc first argument.
       */
        MenuCommand(GameController* gc)//
        {
           gameController_ = gc;
        }
      /**
       * pause the current game instance.
       */
        void execute()
        {
           gameController_->onGamePause();
        }
    private:
    //! A private variable.
    /*!
      pointer of GameController.
    */
        GameController* gameController_ = nullptr;

};


#endif // MENUCOMMAND_H_INCLUDED
