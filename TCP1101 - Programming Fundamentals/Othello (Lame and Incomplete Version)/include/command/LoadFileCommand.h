/**********|**********|**********|
Program: LoadFileCommand.h
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/
#ifndef LOADFILECOMMAND_H_INCLUDED
#define LOADFILECOMMAND_H_INCLUDED
/// using FileReader header for referencing.
#include "FileReader.h"
/// using Board header for referencing.
#include "Board.h"
//!  A sub-class LoadFileCommand of Command class.
/*!
  An interface class for sub-classes to inherits.
*/
class LoadFileCommand: public Command
{
    public:
      /**
       * load a file given controller and file path.
       * \param menuController first argument.
       * \param path first argument.
       */
        LoadFileCommand(MenuController* menuController, std::string path)
        {
            if(fr_==nullptr)fr_ = new FileReader();
            menuController_ = menuController;
            board_ = fr_->stringToBoard(path);
        }
      /**
       * call main game loop after loading the board.
       */
        void execute()
        {
            GameController* gameController_ = new GameController(board_);
            menuController_->setGameController(gameController_);
            gameController_->update();
        }
    private:
    //! A private variable.
    /*!
      pointer of Board.
    */
        Board* board_ = nullptr;
    //! A private variable.
    /*!
      pointer of MenuController.
    */
        MenuController* menuController_ = nullptr;
    //! A private variable.
    /*!
      pointer of FileReader.
    */
        FileReader* fr_ = nullptr;
};

#endif // LOADFILECOMMAND_H_INCLUDED
