/**********|**********|**********|
Program: GameView.h
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/
#ifndef GAMEVIEW_H
#define GAMEVIEW_H
/// View header used for inheritance.
#include "View.h"
///forward Board declaration.
class Board;
//!  A sub-class HelpView of View class.
/*!
  An interface class for sub-classes to inherits.
*/
class GameView: public View
{
    public:
    //! A constructor of GameView. GameView will print the Board.
    /*!
      \param bd the first argument.
    */
        GameView(Board* bd);
      /**
       * A virtual void member taking no arguments this function prints out the View.
       * This function overrides the interface class from abstract to concrete function.
       */
        void printView();
    private:
    //! A private variable.
    /*!
      Board pointer.
    */
        Board* board_ = nullptr;
    //! A function variable.
    /*!
      Prints single row of board.
    */
        void printSingleRow();
    //! A function variable.
    /*!
      Prints the number of the board.
      \param n the first argument.
    */
        void printNumber(int n);
    //! A function variable.
    /*!
      Prints the Board.
    */
        void printBoard();
    //! A function variable.
    /*!
      Prints the Score.
    */
        void printScore();
    //! A function variable.
    /*!
      Prints Player's Turn.
    */
        void printPlayerTurn();
    //! A function variable.
    /*!
      Prints User options available.
    */
        void printUserOptions();
    //! A function variable.
    /*!
      Prints starting game banner.
    */
        void printGameBanner();
};

#endif // GAMEVIEW_H
