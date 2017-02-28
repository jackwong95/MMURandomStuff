/**********|**********|**********|
Program: FileReader.cpp
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/
#include "FileReader.h"
#include "BoardType.h"
//for ifstream input file
#include <fstream>
//for erasing the ',' and the ' ' inside the text file.
#include <algorithm>

FileReader::FileReader()
{

}
Board* FileReader::stringToBoard(std::string path)
{

    std::vector<std::string> coord = ultis::split(path);
    bool isWhite = false, hasSuper1O = false, hasSuper2O = false, hasSuper1X = false, hasSuper2X = false, startLooping = false;
    int i = 0;
    Type boardLayout [16][16];

    path_ = "assets/games/" + coord.at(1);
    std::ifstream inputFile;
    inputFile.open(path_.c_str());
    std::string temp;
    while(getline(inputFile, temp)){
        if(temp=="current player, O" || temp =="current player, X")
        {
            if(temp[16]=='O')isWhite = true;
            else isWhite = false;
        }
        if(temp=="super1O, false" || temp=="super1O, true")
        {
            if(temp[9]=='t')
            {
                hasSuper1O = true;
            }else if(temp[9]=='f')
            {
                hasSuper1O = false;
            }
        }
        if(temp=="super1X, false" || temp=="super1X, true")
        {
            if(temp[9]=='t')
            {
                hasSuper1X = true;
            }else if(temp[9]=='f')
            {
                hasSuper1X = false;
            }
        }
        if(temp=="super2X, false" || temp=="super2X, true")
        {
            if(temp[9]=='t')
            {
                hasSuper2X = true;
            }else if(temp[9]=='f')
            {
                hasSuper2X = false;
            }
        }
        if(temp=="super2O, false" || temp=="super2O, true")
        {
            if(temp[9]=='t')
            {
                hasSuper2O = true;
            }else if(temp[9]=='f')
            {
                hasSuper2O = false;
            }
        }
        if(temp=="board")startLooping = true;
        else if(startLooping && i<=7)
        {
            for(int j = 0; j < 8; j ++)
            {
                //std::cout << " i : " << i << " j : " << j << std::endl;
                temp.erase(std::remove(temp.begin(), temp.end(), ','), temp.end());
                temp.erase(std::remove(temp.begin(), temp.end(), ' '), temp.end());
                if(temp[j] == 'O')
                {
                    boardLayout[i][j] = WHITE;
                    //std::cout << 1;
                }else if(temp[j]=='X'){
                    boardLayout[i][j] = BLACK;
                    //std::cout << 0;
                }else{
                    boardLayout[i][j] = NONE;
                    //std::cout << '-';
                }
                //std::cout << temp << std::endl;
            }
            //std::cout << std::endl;
            i++;
        }
    }
    //std::cout << hasSuper1O << " " << hasSuper1X << " " << hasSuper2O << " " << hasSuper2X << " " << std::endl;
    //std::cout << isWhite << " " << hasSuper1O << " " << hasSuper1X << " " << hasSuper2O << " " << hasSuper2X << " " << startLooping << std::endl;
    inputFile.close();
    //bool isWhiteTurn, bool super1OUsed, bool super2OUsed, bool super1XUsed, bool super2XUsed);
    Board* tempB = new Board(boardLayout, 8, isWhite, hasSuper1O, hasSuper2O, hasSuper1X, hasSuper2X);

    return tempB;
}
