/**********|**********|**********|
Program: FileReader.h
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/
#ifndef FILEREADER_H
#define FILEREADER_H
/// using Board header for referencing.
#include "Board.h"
//!  A class FileReader.
/*!
  A concrete class that reads from text file with given format in the assignment and load the board from board's constructor.
*/
class FileReader
{
    public:
      /**
       * An empty constructor.
       */
        FileReader();
    //! A function variable.
    /*!
      Writes from string to Board.
      \param path the first argument.
    */
        Board* stringToBoard(std::string path);
    private:
    //! A private variable.
    /*!
      string path of where the file is located.
    */
        std::string path_;
};

#endif // FILEREADER_H
