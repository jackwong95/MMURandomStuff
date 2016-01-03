/**********|**********|**********|
Program: GameCommand.h
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/
#ifndef GAMECOMMAND_H_INCLUDED
#define GAMECOMMAND_H_INCLUDED
/// using Command header for referencing.
#include "Command.h"
/// using GameController header for referencing.
#include "GameController.h"
/// using MenuController header for referencing.
#include "MenuController.h"
//!  A sub-class GameCommand of Command class.
/*!
  An interface class for sub-classes to inherits.
*/
class GameCommand: public Command
{
    public:
      /**
       * if going to game mode from menu mode, set the controller of the menu to game controller.
       * \param menuController first argument.
       */
        GameCommand(MenuController* menuController)
        {
            menuController_ = menuController;
        }
      /**
       * store the pointer of game controller to menu controller, then call main loop from game controller.
       */
        void execute()
        {
            GameController* gameController_ = new GameController();
            menuController_->setGameController(gameController_);
            gameController_->update();
        }
    private:
    //! A private variable.
    /*!
      pointer of menuController_.
    */
        MenuController* menuController_ = NULL;
};

#endif // GAMECOMMAND_H_INCLUDED
