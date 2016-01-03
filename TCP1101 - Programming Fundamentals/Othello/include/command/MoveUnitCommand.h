/**********|**********|**********|
Program: MoveUnitCommand.h
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/
#ifndef MOVEUNITCOMMAND_H_INCLUDED
#define MOVEUNITCOMMAND_H_INCLUDED
/// using Board header for referencing.
#include "Board.h"
/// using Command header for referencing.
#include "Command.h"
//!  A sub-class MoveUnitCommand of Command class.
/*!
  An interface class for sub-classes to inherits.
*/
class MoveUnitCommand : public Command
{
    public:
      /**
       * set the unit at given coordinate.
       * \param board first argument.
       * \param pos first argument.
       */
        MoveUnitCommand(Board* board, ultis::Vector2D pos)
        {
            board_ = board;
            pos_ = pos;
        }
      /**
       * flip that board at that position.
       */
        void execute()
        {
            board_->setBoardType(pos_.x, pos_.y, false);
        }

    private:
    //! A private variable.
    /*!
      Board of pointer.
    */
        Board* board_ = nullptr;
    //! A private variable.
    /*!
      position struct of ultis namespace.
    */
        ultis::Vector2D pos_;
};

#endif // MOVEUNITCOMMAND_H_INCLUDED
