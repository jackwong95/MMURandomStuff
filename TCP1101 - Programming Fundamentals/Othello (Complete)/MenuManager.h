/**********|**********|**********|
Program: MenuManager.h
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/

#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include <locale>
#include <algorithm>
#include <vector>
#include "GameManager.h"

//!  MenuManager that manages the menu screen.
class MenuManager
{
    public:
        /*! static method for getting the instance of this object */
        static MenuManager* getInstance();
        /*! static method for clearing the console output */
        static void clearConsole();
        /*! destructor of this object */
        ~MenuManager(){instanceFlag = false;}
        //! static function that takes no arguments and returning a string by getting input from user.
        /*!
          \return string.
        */
        static string getSelectedString();
        //! static function that takes no arguments and returning a integer by getting input from user.
        /*!
          \return int.
        */
        static int getSelectedIndex();
        //! static function that takes an arguments and returning an integer by parsing the string.
        /*!
          \return int.
        */
        static int parseInt(string k);
        //! static function that takes no arguments start the menu and return void.
        /*!
          \param a string
          \return void.
        */
        void start();

    private:
        /*! Vector of legit operations in string that is available. */
        vector<string> operationVectors;
        /*! Private constructor for singleton design pattern so that it can only be created from other method. */
        MenuManager(){
            operationVectors.push_back("new game");
            operationVectors.push_back("help");
            operationVectors.push_back("quit");
            operationVectors.push_back("resume game");
            operationVectors.push_back("clear console");
        }
        /*! Static boolean to check whether if this instance has already been initialized. */
        static bool instanceFlag;
        /*! Static instance of the game object */
        static MenuManager *single;
        //! member function that takes no arguments return value given by user and parse to integer.
        /*!
          \return int.
        */
        int getSelectedBoard();

};


#endif // MENUMANAGER_H

//refer to www.silviuardelean.ro/2012/06/05/few-singleton-approaches/ V2 for more detail on how I implemented this design pattern on c++.
