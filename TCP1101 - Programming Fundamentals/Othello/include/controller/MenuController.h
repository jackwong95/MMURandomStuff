/**********|**********|**********|
Program: GameManager.cpp
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/
#ifndef MENUCONTROLLER_H
#define MENUCONTROLLER_H
///forward class declaration.
class View;
class MenuInputHandler;
class GameController;
//!  A class MenuController.
/*!
  A concrete class that handles view and model.
*/
class MenuController
{
    public:
      /**
       * An empty constructor.
       */
        MenuController();
    //! A function variable.
    /*!
      //getter for the game controller variable.
    */
        GameController* getGameController();
    //! A function variable.
    /*!
      //setter for the game controller variable.
    */
        void setGameController(GameController* gc);
    //! A function variable.
    /*!
      //start the menu screen.
    */
        void startMenu();
    //! A function variable.
    /*!
      //quit the main loop in menu screen.
    */
        void quitGame();
    private:
    //! A private variable.
    /*!
      pointer of menu input handler.
    */
        MenuInputHandler* inputHandler_ = nullptr;
    //! A private variable.
    /*!
      pointer of game controller.
    */
        GameController* gameController_ = nullptr;
    //! A private variable.
    /*!
      pointer of view.
    */
        View* menuView_ = nullptr;
    //! A private variable.
    /*!
      pointer of view.
    */
        View* bannerView_ = nullptr;
    //! A private variable.
    /*!
      pointer of for whether if the game is finish.
    */
        bool quitGame_ = false;
};

#endif // MENUCONTROLLER_H
