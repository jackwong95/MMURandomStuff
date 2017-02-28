/**********|**********|**********|
Program: BoardType.h
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/
#ifndef BOARDTYPE_H
#define BOARDTYPE_H
/*!
 *  \addtogroup BoardType
 *  @{
 */
//! BoardType of Enum.
namespace BoardType{
    /**
     * An enum.
     * Type that represents a certain character in ASCII.
     */
    enum Type
    {
          WHITE = (int)'O' /**< enum value WHITE with decimal value of 'O' from ASCII. */
        , BLACK = (int)'X' /**< enum value WHITE with decimal value of 'X' from ASCII. */
        , NONE = (int)' ' /**< enum value WHITE with decimal value of ' ' from ASCII. */
    };
}
#endif // BOARDTYPE_H
