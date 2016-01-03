/**********|**********|**********|
Program: MoveUnitRandomly.h
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/
#ifndef MOVEENEMYUNITRANDOMLY_H_INCLUDED
#define MOVEENEMYUNITRANDOMLY_H_INCLUDED
/// using Board header for referencing.
#include "Board.h"
/// using Command header for referencing.
#include "Command.h"
//!  A sub-class MakeEnemyUnitRandomly of Command class.
/*!
  An interface class for sub-classes to inherits.
*/
class MakeEnemyUnitRandomly : public Command
{
    public:
      /**
       * er... this is suppose to be flip everything in all direction... the class's name is misleading...
       * but i'm too lazy to change the name.. so just gona leave it like that..
       * \param board first argument.
       * \param temp first argument.
       */
        MakeEnemyUnitRandomly(Board* board, std::string temp)
        {
            board_ = board;
            std::vector<std::string> coord = ultis::split(temp);
            x_ = coord.at(2)[0] - 'a';
            y_ = board->sz_ - ultis::stringToInt(coord.at(3).c_str());
        }
      /**
       * if the super power hasn't been used then use it.
       */
        void execute()
        {
            if((board_->whiteTurn && !board_->super1OUsed_)||(!board_->whiteTurn && !board_->super1XUsed_))
                board_->setBoardType(x_, y_, true);
        }

    private:
    //! A private variable.
    /*!
      Board of GameController.
    */
        Board* board_;
    //! A private variable.
    /*!
      integer of coordinate x and y.
    */
        int x_ = -1, y_ = -1;
};

#endif // MOVEENEMYUNITRANDOMLY_H_INCLUDED
