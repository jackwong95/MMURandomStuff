/**********|**********|**********|
Program: Ultis.h
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/
#ifndef ULTIS_H
#define ULTIS_H
///for splitting the string and add them into the vector
#include <vector>
///for string
#include <string>
///for throwing exceptions
#include <stdexcept>
class Board;
/*!
 *  \addtogroup ultis
 *  @{
 */
//! Helper functions in namespace.
namespace ultis
{
/**
 * This type is used when there are 2 coordinates x and y.
 */
    struct Vector2D
    {
        int x; /**< member x-axis*/
        int y; /**< member y-axis*/
    };
    //! A function variable.
    /*!
      //split the string.
      \param str the first argument.
    */
    std::vector<std::string> split(const std::string& str);
    //! A function variable.
    /*!
      //convert integer to string.
      \param input the first argument.
    */
    std::string intToString(const int input);
    //! A function variable.
    /*!
      //get the first string after split.
      \param input the first argument.
    */
    std::string getFirstString(const std::string& input);
    //! A function variable.
    /*!
      //trim the string.
      \param input the first argument.
      \param trimS the second argument.
    */
    std::string trim(const std::string& str, const std::string& trimS);
    std::string trim(const std::string& str);
    //! A function variable.
    /*!
      //get user input.
    */
    std::string getUserInput();
    //! A function variable.
    /*!
      //change to Vector2D struct from raw x-axis and y-axis.
      \param x the first argument.
      \param y the second argument.
    */
    Vector2D coordinateToVector2D(int x, int y);
    //! A function variable.
    /*!
      //change read and print from path.
      \param fileName the first argument.
    */
    void readAndPrint(std::string fileName);
    //! A function variable.
    /*!
      //clear console.
    */
    void clearConsole();
    //! A function variable.
    /*!
      //to lower case
      \param str the first argument.
    */
    std::string toLowerCase(const std::string& str);
    //! A function variable.
    /*!
      //convert string to single character.
      \param x the first argument.
    */
    char intToChar(int x);
    //! A function variable.
    /*!
      //convert input to vector by splitting.
      \param str the first argument.
      \param board the first argument.
    */
    Vector2D inputToVector(const std::string str, Board* board);
    //! A function variable.
    /*!
      //checks if given string is a coordinate.
      \param str the first argument.
      \param board the first argument.
    */
    bool isACoordinate(const std::string str, Board* board);
    //! A function variable.
    /*!
      //checks if given character is an upper case.
      \param x the first argument.
    */
    bool isUpperCaseChar(const char x);
    //! A function variable.
    /*!
      //checks if given character is an lower case.
      \param x the first argument.
    */
    bool isLowerCaseChar(const char x);
    //! A function variable.
    /*!
      //checks if given character is an white space.
      \param x the first argument.
    */
    bool isWhiteSpaceChar(const char x);
    //! A function variable.
    /*!
      //checks if given character is an alphabetical character.
      \param x the first argument.
    */
    bool isAlphabeticalCharacter(const char x);
    //! A function variable.
    /*!
      //checks if given character is an number.
      \param x the first argument.
    */
    bool isNumericChar(const char x);
    //! A function variable.
    /*!
      //conert string to integer.
      \param str the first argument.
    */
    int stringToInt(const char *str);
    ///i have no idea how to doxygen the stuff below... template functions..
    template <typename T, int N>
    int getArraySize(T (&a) [N]) {
        if(a==nullptr)throw std::logic_error("Null pointer exception, Unable to determine size of the array.");
        return sizeof(a)/sizeof(a[0]);
    }
    template <typename T, int N>
    bool arrayIsInBound(T (&a) [N], int x, int y) {
        if(a==nullptr)throw std::logic_error("Null pointer exception, Unable to determine size of the array.");
        return (x>=0 && y>=0 && getArraySize(a)<x && getArraySize(a)<y);
    }
}
#endif // ULTIS_H
