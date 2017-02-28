/**********|**********|**********|
Program: PrintManager.h
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/

#ifndef PRINTMANAGER_H
#define PRINTMANAGER_H

#include <fstream>
#include "Board.h"

//!  Print Manager, manages all of the outputs.
class PrintManager
{
    public:
        /*! static method for getting the instance of this object */
        static PrintManager* getInstance();
        /*! destructor of this object */
        ~PrintManager(){instanceFlag = false;}
        //! member function that takes no arguments prints given board and return void.
        /*!
          \param Board instance.
          \return void.
        */
        void printBoard(Board board);
        //! member function that takes an arguments prints given message and return void.
        /*!
          \param string message.
          \return void.
        */
        static void print(string msg);
        //! member function that takes two arguments prints given message with integer and return void.
        /*!
          \param string message.
          \param integer message.
          \return void.
        */
        static void print(string msg, int n);
        //! member function that takes an arguments prints the name of text file and return void.
        /*!
          \param string filename.format.
          \return void.
        */
        void printPage(string fileName);
        //! member function that takes three arguments prints the score, players turn and return void.
        /*!
          \param boolean iswhite's turn.
          \param integer of white's score.
          \param integer of black's score.
          \return void.
        */
        void printScore(bool whitesTurn, int whiteScore, int blackScore);
    private:
        /*! get input stream of file. */
        ifstream inputFile;
        /*! Private constructor for singleton design pattern so that it can only be created from other method. */
        PrintManager(){}
        /*! Static boolean to check whether if this instance has already been initialized. */
        static bool instanceFlag;
        /*! Static instance of the game object */
        static PrintManager *single;
        //! function of member that takes no arguments and returning void by printing closing brackets.
        /*!
          \return void.
        */
        void printClosingBracket();
        //! function of member that takes an arguments and returning void by printing number of board.
        /*!
          \param integer of the number to be printed;
          \return void.
        */
        void printNumber(int n);
        //! function of member that takes an arguments and returning void by printing marker of board.
        /*!
          \param string of the marker to be printed;
          \return void.
        */
        void printBoardMarker(string marker);
        //! function of member that takes three arguments and returning void by printing board unit.
        /*!
          \param Board;
          \param integer x;
          \param integer y;
          \return void.
        */
        void printBoardUnit(Board board, int x, int y);
        //! function of member that takes four arguments and returning void by printing board unit.
        /*!
          \param Board;
          \param string of the name to be printed;
          \param integer x;
          \param integer y;
          \return void.
        */
        void printBoardUnit(Board board, string name, int x, int y);
        //! member function that takes an arguments prints empty row.
        /*!
          \param Board instance.
          \return void.
        */
        void printEmptyRow(Board board);
        //! member function that takes an arguments prints alphabetical row.
        /*!
          \param Board instance.
          \return void.
        */
        void printAlphabeticalRow(Board board);

};

#endif // PRINTMANAGER_H
