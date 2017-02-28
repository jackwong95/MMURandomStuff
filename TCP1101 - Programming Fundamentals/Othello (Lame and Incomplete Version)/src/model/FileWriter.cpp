/**********|**********|**********|
Program: FileWriter.cpp
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/
#include "FileWriter.h"

#include "Ultis.h"
#include "Board.h"

#include <fstream>

FileWriter::FileWriter()
{
}
void FileWriter::boardToFile(Board* board, std::string fileName)
{
    std::vector<std::string> coord = ultis::split(fileName);
    std::string path = "assets/games/" + coord.at(1);
    std::ofstream outputFile;
    outputFile.open(path);
    outputFile << "current player, " << ((board->whiteTurn)?"O":"X") << std::endl;
    outputFile << "super1O, " << ((board->super1OUsed_)?"true":"false") << std::endl;
    outputFile << "super2O, " << ((board->super2OUsed_)?"true":"false") << std::endl;
    outputFile << "super1X, " << ((board->super1XUsed_)?"true":"false") << std::endl;
    outputFile << "super2X, " << ((board->super2XUsed_)?"true":"false") << std::endl;
    outputFile << "board";
    int sz = board->sz_;
    for(int i = 0; i < sz; i ++)
    {
        outputFile << std::endl;
        for(int j = 0; j < sz; j ++)
        {
            if(board->getBoardName(j, i)=='O')
            {
                outputFile << "O";
            }
            else if(board->getBoardName(j, i)=='X')
            {
                outputFile << "X";
            }
            else
            {
                outputFile << "S";
            }
            if(j!=sz-1)
                outputFile << ", ";
        }
    }
    outputFile.close();

}
