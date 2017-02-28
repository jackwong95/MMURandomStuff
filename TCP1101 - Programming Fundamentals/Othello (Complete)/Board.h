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

#include "cstddef"
#include <stdexcept>
#include <iostream>
#include <sstream>

using namespace std;
/*! \struct Vector2D
 * A pair of coordinate that contains x and y integer.
 */
struct Vector2D
{
/*! The x coordinate */
    int x;
/*! The y coordinate */
    int y;
};
//!  Generate board and handle everything thats related to the board when theres an update.
class Board
{
    public:
    /** An enum of BoardType.
     *  There are three types of unit in this board, WHITE, BLACK and NONE.
     */
        enum BoardType
        {
          WHITE = (int)'O' /**< enum type WHITE that represents 'O' in game play or in ASCII integer 79 to round it back to char later. */
        , BLACK = (int)'X' /**< enum type BLACK that represents 'X' in game play or in ASCII integer 58 to round it back to char later.. */
        , NONE = (int)' '  /**< enum type NONE that represents ' ' in game play or in ASCII integer 32 to round it back to char later.. */
        };
        /*! Legal position for X moves.. */
        bool blackMarker [16][16];
        /*! Legal position for Y moves. */
        bool whiteMarker [16][16];
        //! Default constructor of Board.
        /*!
        Default size for a board is 8, unless other value is specified.
        */
        Board();
        //! Constructor of Board that takes in a size.
        /*!
          Dynamic constructor of Board that takes in different size.
        */
        Board(int size);
        //! static function that takes an argument of BoardType and return string.
        /*!
          \param a board type.
          \return the name of boardtype in string within game space.
        */
        //TODO: REMOVE THESE 2 FUNCTIONS
        static string convertEnumToStr(BoardType bt);
        static string convertIntToStr(int val);
        //! static function that takes two arguments and returning a Vector2D.
        /*!
          \param an integer argument of x axis.
          \param an integer argument of y axis.
          \return Vector2D which holds values of direction in game space.
        */
        static Vector2D convertCoordToVec2D(int x, int y);
       //! member of class that takes an arguments and returning a void.
        /*!
          \param Vector2D of position.
          \return void
        */
        void setBoardType(Vector2D pos);
       //! member of class that takes no arguments and returning a void.
        /*!
          \return void
        */
        void switchTurn();
       //! member of class that takes an arguments and returning a BoardType of given Vector2D.
        /*!
          \param Vector2D of position.
          \return void
        */
        BoardType getBoardType(Vector2D pos);
       //! member of class that takes an arguments and returning a string of given Vector2D.
        /*!
          \param Vector2D of position.
          \return string
        */
        string getBoardName(Vector2D pos);
        /*! The size of board. */
        int size;
        /*! Score of white player. */
        int whiteScore = 2;
        /*! Score of black player. */
        int blackScore = 2;
       //! member of class that takes an arguments and returning a boolean depending on whether if a vector is legit move.
        /*!
          \param Vector2D of position.
          \return boolean
        */
        bool isLegal(Vector2D pos);
        /*! To decide which player's turn. */
        bool whiteTurn = false;
        /*! To decide if white has move. */
        bool whiteHasMove = false;
        /*! To decide if black has move. */
        bool blackHasMove = false;
        /*! For white and black to decide whether if the marker array has been marked. */
        bool hasChanged = false;
        /*! To check whether if game is over. */
        bool isOver = false;

    private:
        /*! Array of boardLayout */
        BoardType boardLayout [16][16];
        /*! All possible direction a unit can go. */
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
        /*! Target for current player to achieve. */
        BoardType bt = BLACK;
       //! member of class that no arguments and returning void this method updates all possible moves for both players.
        void updateMarker();
       //! member of class that three arguments and returning void this method add all possible moves for both players.
        /*!
          \param pass by reference of double dimensional boolean.
          \param boardtype.
          \param Vector2D of position.
          \return void
        */
        void addMarker(bool (&arr) [16][16] ,BoardType bt, Vector2D pos);
       //! member of class that two arguments and returning void this method add all possible moves for both players.
        /*!
          \param boardtype.
          \param Vector2D of position.
          \return void
        */
        void updateScore(BoardType bt, Vector2D pos);
       //! member of class that two arguments and returning void this method set all possible moves for both players.
        /*!
          \param boardtype.
          \param Vector2D of position.
          \return void
        */
        void setBoard(BoardType bt, Vector2D pos);
       //! member of class that three arguments and returning void this method flip all possible moves for both players.
        /*!
          \param boardtype.
          \param Vector2D of position.
          \param An array of integer.
          \return void
        */
        void flip(BoardType bt, Vector2D pos, int direction []);
       //! member of class that two arguments and returning void this method updateBoard all possible moves for both players.
        /*!
          \param boardtype.
          \param Vector2D of position.
          \return void
        */
        void updateBoard(BoardType type, Vector2D pos);
       //! member of class that an arguments and returning void this method is initializer called by constructor..
        /*!
          \param size of the board.
          \return void
        */
        void init(int size);
       //! member of class that an arguments this method returns boolean, at given vector2d.
        /*!
          \param vector2d of position.
          \return bool
        */
        bool isInBound(Vector2D pos);
       //! member of class that an arguments this method returns boolean, at given that the direction is flippable.
        /*!
          \param Boardtype of bt.
          \param Vector2D of position.
          \param Integer of x and y for direction.
          \return bool
        */
        bool isFlippable(BoardType bt, Vector2D pos, int direction []);
       //! member of class that an arguments this method returns boolean, at given that the direction is not the same as board type.
        /*!
          \param Boardtype of bt.
          \param Vector2D of position.
          \param Integer of x and y for direction.
          \return bool
        */
        bool isNotAdjFromCoord(BoardType bt, Vector2D pos, int direction []);


};

#endif // BOARD_H
