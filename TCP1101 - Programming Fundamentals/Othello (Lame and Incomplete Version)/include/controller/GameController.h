/**********|**********|**********|
Program: GameController.h
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/
#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
///forward class declaration.
class Board;
class GameView;
class GameInputHandler;
//!  A class MenuController.
/*!
  A concrete class that handles view and model.
*/
class GameController
{
    public:
      /**
       * An empty constructor.
       */
        GameController();
      /**
       * if there is given board, use this board. otherwise make your own.
       * \param board first argument.
       */
        GameController(Board* board);
    //! A function variable.
    /*!
      //main game loop.
    */
        void update();
    //! A function variable.
    /*!
      //when game has been paused.
    */
        void onGamePause();
    //! A function variable.
    /*!
      //when game has been resume.
    */
        void onGameResume();
    protected:
    private:
    //! A private variable.
    /*!
      to check whether if the game will resume.
    */
        bool gameResume_ = true;
    //! A private variable.
    /*!
      pointer of Board.
    */
        Board* board_ = nullptr;
    //! A private variable.
    /*!
      pointer of GameView.
    */
        GameView* gameView_ = nullptr;
    //! A private variable.
    /*!
      pointer of game input handler.
    */
        GameInputHandler* inputHandler_ = nullptr;

};

#endif // GAMECONTROLLER_H
