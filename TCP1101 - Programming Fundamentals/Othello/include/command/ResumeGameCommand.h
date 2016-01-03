/**********|**********|**********|
Program: ResumeGameCommand.h
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/
#ifndef RESUMEGAMECOMMAND_H_INCLUDED
#define RESUMEGAMECOMMAND_H_INCLUDED
/// using Command header for referencing.
#include "Command.h"
/// using MenuController header for referencing.
#include "MenuController.h"
/// using GameController header for referencing.
#include "GameController.h"
//!  A sub-class ResumeGameCommand of Command class.
/*!
  An interface class for sub-classes to inherits.
*/
class ResumeGameCommand: public Command
{
      /**
       * resume the game for constructor.
       * \param menuController first argument.
       */
    public:
        ResumeGameCommand(MenuController* menuController)
        {
            menuController_ = menuController;
        }
      /**
       * resume game.
       */
        void execute()
        {
            if((menuController_->getGameController())==nullptr)
            {
                GameController* gameController_ = new GameController();
                menuController_->setGameController(gameController_);
                gameController_->update();
            }
            else
            {
                (menuController_->getGameController())->onGameResume();
                (menuController_->getGameController())->update();
            }
        }
    private:
        MenuController* menuController_ = nullptr;
};
#endif // RESUMEGAMECOMMAND_H_INCLUDED
