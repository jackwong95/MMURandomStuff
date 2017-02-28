/**********|**********|**********|
Program: GameManager.h
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Board.h"
#include "PrintManager.h"
#include "MenuManager.h"
#include <stdlib.h>
#include <stdio.h>

//!  GameManager that manages all the instances of boards and current game.
class GameManager
{
    public:
        /*! static method for getting the instance of this object */
        static GameManager* getInstance();
        /*! destructor of this object */
        ~GameManager(){instanceFlag = false;}
        /*! boolean to quit the main loop. */
        bool quitGame = false;
        //! static function that takes an arguments and returning a string by trimming trail and ending white spaces.
        /*!
          \param a string pass by reference
          \return string.
        */
        static string trim(std::string const& str);
        //! function of member that takes no arguments and returning void by restarting the current game.
        /*!
          \return void.
        */
        void restartBoard();
        //! function of member that takes no arguments and returning void by breaking the main loop.
        /*!
          \return void.
        */
        void gameIsOver();
        //! function of member that takes no arguments and returning void by starting the main loop.
        /*!
          \return void.
        */
        void start();
    private:
        /*! Vector of legit operations in string that is available. */
        vector<string> operationVectors;
        /*! Array of board that holds max size of 16 instances. */
        Board board[16];
        /*! Integer to hold the selected board. */
        int selector = 0;
        /*! Private constructor for singleton design pattern so that it can only be created from other method. */
        GameManager(){
            operationVectors.push_back("next player");
            operationVectors.push_back("menu");
            operationVectors.push_back("restart current tab");
            operationVectors.push_back("select tab");
            operationVectors.push_back("resize current tab");
            operationVectors.push_back("restart everything");
            operationVectors.push_back("clear console");
        }
        /*! Static boolean to check whether if this instance has already been initialized. */
        static bool instanceFlag;
        /*! Static instance of the game object */
        static GameManager *single;
        //! function of member that takes an arguments and returning void by printing out the board given.
        /*!
          \param a board object.
          \return void.
        */
        void printGameMenu(Board board);
        //! function of member that takes no arguments and returning void by looping the main loop.
        /*!
          \return void.
        */
        void update();
        //! function of member that takes no arguments and returning integer by selecting the current board.
        /*!
          \return void.
        */
        int getSelectedBoard();
        //! function of member that takes no arguments and returning string by selecting user input.
        /*!
          \return void.
        */
        string getSelectedString();
        /*! get instance of print manager */
        PrintManager *pmInstance = PrintManager::getInstance();
};

#endif // GAMEMANAGER_H
