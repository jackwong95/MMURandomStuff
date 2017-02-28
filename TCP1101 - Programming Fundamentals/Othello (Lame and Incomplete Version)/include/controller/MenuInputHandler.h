/**********|**********|**********|
Program: MenuInputHandler.h
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/
#ifndef MENUINPUTHANDLER_H
#define MENUINPUTHANDLER_H
/// using built in library for string type.
#include <string>
///forward Command, View, MenuController classes declaration
class Command;
class View;
class MenuController;
//!  A class MenuInputHandler.
/*!
  A concrete class that process given inputs.
*/
class MenuInputHandler
{
    public:
      /**
       * An constructor that deals with the input from menu controller.
       * \param menuController first argument.
       */
        MenuInputHandler(MenuController* menuController);
    //! A function variable.
    /*!
      //get Command type and execute the command.
      * \param str first argument.
    */
        Command* handleInput(const std::string str);
    private:
    //! A function variable.
    /*!
      //check if the string is load game
      * \param str first argument.
    */
        bool isLoadGame(std::string str);
    //! A private variable.
    /*!
      pointer of menu controller.
    */
        MenuController* menuController_;
    //! A private variable.
    /*!
      pointer of view.
    */
        View* helpView_ = nullptr;
};

#endif // MENUINPUTHANDLER_H
