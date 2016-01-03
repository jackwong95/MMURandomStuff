/**********|**********|**********|
Program: QuitCommand.h
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/
#ifndef QUITCOMMAND_H_INCLUDED
#define QUITCOMMAND_H_INCLUDED
/// using Command header for referencing.
#include "Command.h"
/// using MenuController header for referencing.
#include "MenuController.h"
//!  A sub-class NextPlayerCommand of Command class.
/*!
  An interface class for sub-classes to inherits.
*/
class QuitCommand: public Command
{
    public:
      /**
       * quit the game
       * \param menuController first argument.
       */
        QuitCommand(MenuController* menuController)
        {
           menuController_ = menuController;
        }
      /**
       * quit the game.
       */
        void execute()
        {
            menuController_->quitGame();
        }
    private:
        MenuController* menuController_ = nullptr;
};

#endif // QUITCOMMAND_H_INCLUDED
