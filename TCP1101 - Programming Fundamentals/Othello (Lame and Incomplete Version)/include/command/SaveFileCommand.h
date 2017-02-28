/**********|**********|**********|
Program: SaveFileCommand.h
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/
#ifndef SAVEFILECOMMAND_H_INCLUDED
#define SAVEFILECOMMAND_H_INCLUDED
/// using Board header for referencing.
#include "Board.h"
/// using FileWriter header for referencing.
#include "FileWriter.h"
//!  A sub-class SaveFileCommand of Command class.
/*!
  An interface class for sub-classes to inherits.
*/
class SaveFileCommand : public Command
{
       /**
       * save the board to a file name
       * \param board first argument.
       * \param fileName second argument.
       */
    public:
        SaveFileCommand(Board* board, std::string fileName)
        {
            board_ = board;
            fileName_ = fileName;
        }
      /**
       * save the game.
       */
        void execute()
        {
            FileWriter fw;
            fw.boardToFile(board_, fileName_);
        }

    private:
        Board* board_;
        std::string fileName_;
};

#endif // SAVEFILECOMMAND_H_INCLUDED
