/**********|**********|**********|
Program: NextPlayerCommand.h
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/
#ifndef NEXTPLAYERCOMMAND_H_INCLUDED
#define NEXTPLAYERCOMMAND_H_INCLUDED
/// using Board header for referencing.
#include "Board.h"
//!  A sub-class NextPlayerCommand of Command class.
/*!
  An interface class for sub-classes to inherits.
*/
class NextPlayerCommand: public Command
{
    public:
      /**
       * skip player turn.
       * \param board first argument.
       */
        NextPlayerCommand(Board* board)
        {
            board_ = board;
        }
      /**
       * skip turn.
       */
        void execute()
        {
            board_->switchTurn();
        }
    private:
        Board* board_;
};


#endif // NEXTPLAYERCOMMAND_H_INCLUDED
