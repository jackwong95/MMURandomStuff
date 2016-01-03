/**********|**********|**********|
Program: Board.h
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/
#ifndef BOARD_H
#define BOARD_H
/// using ultilities header for referencing.
#include "Ultis.h"
/// using BoardType header for referencing.
#include "BoardType.h"
/// using my own namespace
using namespace BoardType;
//!  A class Board.
/*!
  A concrete class that contains all the logic of the game.
*/
class Board
{
    public:
    //! A public variable.
    /*!
      store the legit moves or maker for X player.
    */
        bool blackMarker [16][16];
    //! A public variable.
    /*!
      store the legit moves or maker for O player.
    */
        bool whiteMarker [16][16];
      /**
       * An empty constructor.
       */
        Board();
      /**
       * An constructor that loads an existing board.
       * \param Type of layout of size 16 by 16 an 2D array the first argument.
       * \param sz the second argument.
       * \param isWhiteTurn the third argument.
       * \param super1OUsed the fourth argument.
       * \param super2OUsed the fifth argument.
       * \param super1XUsed the sixth argument.
       * \param super2XUsed the seventh argument.
       */
        Board(Type layout[16][16], int sz, bool isWhiteTurn, bool super1OUsed, bool super2OUsed, bool super1XUsed, bool super2XUsed);
      /**
       * An that expandable board constructor.
       * \param size the first argument.
       */
        Board(int size);
    //! A function variable.
    /*!
      //set the board type at position x and y.
      \param x the first argument.
      \param y the second argument.
      \param toNuke the third argument.
    */
        void setBoardType(int x, int y, bool toNuke);
    //! A function variable.
    /*!
      //switch player's turn
    */
        void switchTurn();
    //! A function variable.
    /*!
      //reverse the whole board.
    */
        void reverseBoard();
    //! A function variable.
    /*!
      //get the board name at position x and y.
      \param x the first argument.
      \param y the second argument.
    */
        char getBoardName(int x, int y);
    //! A public variable.
    /*!
      size of the board.
    */
        int sz_;
    //! A public variable.
    /*!
      O score of the board.
    */
        int whiteScore = 2;
    //! A public variable.
    /*!
      X score of the board.
    */
        int blackScore = 2;
    //! A function variable.
    /*!
      //check if position at x and y is legal move.
      \param x the first argument.
      \param y the second argument.
    */
        bool isLegal(int x, int y);
    //! A public variable.
    /*!
      if is white turn in this board.
    */
        bool whiteTurn = false;
    //! A public variable.
    /*!
      if this board is game over.
    */
        bool isOver = false;
    //! A public variable.
    /*!
      if this board's O still has move.
    */
        bool whiteHasMove = false;
    //! A public variable.
    /*!
      if this board's X still has move.
    */
        bool blackHasMove = false;
    //! A public variable.
    /*!
      if this board's O super power one has been used.
    */
        bool super1OUsed_;
    //! A public variable.
    /*!
      if this board's O super power second has been used.
    */
        bool super2OUsed_;
    //! A public variable.
    /*!
      if this board's X super power one has been used.
    */
        bool super1XUsed_;
    //! A public variable.
    /*!
      if this board's X super power second has been used.
    */
        bool super2XUsed_;

    private:
    //! A private variable.
    /*!
      board layout of Type.
    */
        Type boardLayout [16][16];
    //! A private variable.
    /*!
      a double dimensional array of all possible directions a tile can move from.
    */
        int directions [8][2] = {
            {+1, +0},
            {+0, +1},
            {+1, +1},
            {-1, -1},
            {-0, -1},
            {-1, -0},
            {-1, +1},
            {+1, -1}
        };
    //! A private variable.
    /*!
      boolean to check if there is a change after player placed the unit.
    */
        bool hasChanged = false;
    //! A private variable.
    /*!
      the targeted type that the player wanted to change.
    */
        Type bt = BLACK;
    //! A function variable.
    /*!
      //set board type at given position
      \param toChange the first argument.
      \param x the second argument.
      \param y the third argument.
    */
        void setBoardAt(Type toChange, int x, int y);
    //! A function variable.
    /*!
      //update the markers or legal moves for both players.
    */
        void updateMarker();
    //! A function variable.
    /*!
      //add markers at given position and given board type at x position and y position
      \param arr the first argument.
      \param bt the second argument.
      \param xPos the third argument.
      \param yPos the fourth argument.
    */
        void addMarker(bool (&arr) [16][16] ,Type bt, int xPos, int yPos);
    //! A function variable.
    /*!
      //update the score at x and y position.
      \param toUpdate the first argument.
      \param x the second argument.
      \param y the third argument.
    */
        void updateScore(Type toUpdate, int x, int y);
    //! A function variable.
    /*!
      //initialize the variables and all the house keeping stuff needed somewhat a constructor but not a constructor.
      \param sz_ the first argument.
    */
        void init(int sz_);
    //! A function variable.
    /*!
      //checks if the given coordinate is within the bound
      \param x the first argument.
      \param y the second argument.
    */
        bool isInBound(int , int y);
        void updateBoard(Type type, bool toNuke, int x, int y);
    //! A function variable.
    /*!
      //checks if the given coordinate is flippable at a given direction to the board type.
      \param changeTo the first argument.
      \param xPos the second argument.
      \param yPos the third argument.
      \param xDir the fourth argument.
      \param yDir the fifth argument.
      \param isAdjFromOrigin the sixth argument.
      \param toFlip the seventh argument.
      \param nuke the eigth argument.
    */
        bool flip(Type changeTo, int xPos, int yPos, int xDir, int yDir, bool isAdjFromOrigin, bool toFlip, bool nuke);


};

#endif // BOARD_H
