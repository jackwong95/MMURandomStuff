/**********|**********|**********|
Program: GameController.cpp
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/
#ifndef GAMEINPUTHANDLER_H
#define GAMEINPUTHANDLER_H
/// using ultilities header for referencing.
#include "Ultis.h"
///forward class declaration.
class Board;
class Command;
class GameController;
//!  A class MenuInputHandler.
/*!
  A concrete class that process given inputs.
*/
class GameInputHandler
{
    public:
      /**
       * An constructor that deals with the input from game controller.
       * \param gc first argument.
       * \param board second argument.
       */
        GameInputHandler(GameController* gc, Board* board);
    //! A function variable.
    /*!
      //get Command type and execute the command.
      * \param str first argument.
    */
        Command* handleInput(const std::string str);
    private:
    //! A private variable.
    /*!
      pointer of game controller.
    */
        GameController* gameController_ = nullptr;
    //! A private variable.
    /*!
      pointer of board controller.
    */
        Board* board_ = nullptr;
    //! A function variable.
    /*!
      //check if the string is using super power two.
      * \param str first argument.
    */
        bool isSuperPowa2(std::string str);
    //! A function variable.
    /*!
      //check if the string is to save the game.
      * \param str first argument.
    */
        bool isSaveGame(std::string str);
};

#endif // GAMEINPUTHANDLER_H
