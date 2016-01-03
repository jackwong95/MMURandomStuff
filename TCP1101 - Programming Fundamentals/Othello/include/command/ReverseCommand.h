/**********|**********|**********|
Program: ReverseCommand.h
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/
#ifndef REVERSECOMMAND_H_INCLUDED
#define REVERSECOMMAND_H_INCLUDED
/// using Board header for referencing.
#include "Board.h"
/// using Command header for referencing.
#include "Command.h"
//!  A sub-class ReverseCommand of Command class.
/*!
  An interface class for sub-classes to inherits.
*/
class ReverseCommand : public Command
{
       /**
       * reverse the everything of the board.
       * \param board first argument.
       */
    public:
        ReverseCommand(Board* board)
        {
            board_ = board;
        }
      /**
       * reverse everything player board and score.
       */
        void execute()
        {
            if((board_->whiteTurn && !board_->super2OUsed_)||(!board_->whiteTurn && !board_->super2XUsed_))
                board_->reverseBoard();
        }

    private:
        Board* board_;
};

#endif // REVERSECOMMAND_H_INCLUDED
