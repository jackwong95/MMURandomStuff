/**********|**********|**********|
Program: FileWriter.h
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/
#ifndef FILEWRITER_H
#define FILEWRITER_H
/// using built in library for string type.
#include <string>
///forward Board declaration.
class Board;
//!  A class FileWriter.
/*!
  A concrete class that writes from Board to a txt file with format as given in the assignment.
*/
class FileWriter
{
    public:
      /**
       * An empty constructor.
       */
        FileWriter();
    //! A function variable.
    /*!
      Writes from Board to a text file.
      \param board the first argument.
      \param fileName the second argument.
    */
        void boardToFile(Board* board, std::string fileName);
};

#endif // FILEWRITER_H
