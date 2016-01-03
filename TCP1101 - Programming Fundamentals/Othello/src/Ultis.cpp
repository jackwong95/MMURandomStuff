/**********|**********|**********|
Program: GameController.cpp
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/
#include "Ultis.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "Board.h"

using namespace std;

const std::string toTrim = " \n\t";

//this class kinda explains why i dislike c++, fast but lack of built in functions..
//and i'm not even sure if i'm allowed to use external libraries for this assignment.

namespace ultis
{
/**
  *function name
  *parameters
  *why it is called
  *what the function does
  *what it returns
  */
    std::vector<std::string> split(const std::string& str)
    {
        std::vector<std::string> tokens;
        stringstream ss(str);
        std::string buf;
        while (ss >> buf)
            tokens.push_back(buf);
        return tokens;
    }
    std::string intToString(int input)
    {
        std::stringstream ss;
        ss << input ;
        return ss.str();
    }
    Vector2D coordinateToVector2D(int x, int y)
    {
        Vector2D temp;
        temp.x = x;
        temp.y = y;
        return temp;
    }
    std::string getUserInput()
    {
        std::cout << "\n\n==>  ";
        std::string input;
        std::getline(std::cin, input);
        return input;
    }
    std::string getFirstString(const std::string& input)
    {
        std::vector<std::string> coord = split(input);
        return coord.at(0);
    }
    bool isACoordinate(const std::string str, Board* board)
    {
        std::vector<std::string> coord = ultis::split(str);
        int x = -1, y = -1;
        if(coord.size() == 2)
        {
            x = coord.at(0)[0] - 'a';
            y = (board->sz_ - ultis::stringToInt(coord.at(1).c_str()));
        }
        if(x>=0&&y>=0&&y<=board->sz_&&x<=board->sz_)
        {
            ultis::Vector2D coord = ultis::coordinateToVector2D(x, y);
            if(board->isLegal(coord.x, coord.y))
            {
                return true;
            }
        }
        return false;
    }
    Vector2D inputToVector(const std::string str, Board* board)
    {
        std::vector<std::string> coord = split(str);
        return coordinateToVector2D(coord.at(0)[0] - 'a', (board->sz_ - stringToInt(coord.at(1).c_str())));
    }
    void readAndPrint(std::string path)
    {
        ifstream inputFile;
        inputFile.open(path.c_str());
        if(!inputFile.good())throw std::logic_error("Ultis, File not found, or something is wrong with the stream");
        string temp;
        while(getline(inputFile, temp)){
            std::cout << temp << std::endl;
        }
        inputFile.close();
    }
    std::string toLowerCase(const std::string& str)
    {
        std::string aux = str;
        for(unsigned int i = 0; i < aux.length(); i ++)
        {
            if(isUpperCaseChar(aux[i]))
            {
                aux[i] = aux[i] - ('Z' - 'z');
            }
        }
        return aux;
    }
    char intToChar(int x)
    {
        return (char)x;
    }
    bool isUpperCaseChar(char x)
    {
        return x>='A' && x<='Z';
    }
    bool isLowerCaseChar(char x)
    {
        return x>='a' && x<='z';
    }
    bool isWhiteSpaceChar(char x)
    {
        return x==' ';
    }
    bool isAlphabeticalCharacter(char x)
    {
        return isUpperCaseChar(x) || isLowerCaseChar(x);
    }
    bool isNumericChar(char x)
    {
        return (x >= '0' && x <= '9');
    }
    void clearConsole(){
        if(system("CLS")) system("CLEAR");
    }
    int stringToInt(const char *str)
    {
        int res = 0;
        int sign = 1;
        int i = 0;
        if (str[0] == '-')
        {
            sign = -1;
            i++;
        }
        for (; str[i] != '\0'; ++i)
        {
            if (isNumericChar(str[i]) == false)
                throw std::logic_error("ULTIS. Invalid Argument, illegal argument unable to convert string to integer. Reason: input is not an integer");
            res = res*10 + str[i] - '0';
        }
        return sign*res;
    }
    std::string trim(const std::string& str)
    {
        return trim(str, toTrim);
    }
    std::string trim(const std::string& str, const std::string& trimS)
    {
        size_t leftPos = str.find_first_not_of(trimS);
        size_t rightPos = str.find_last_not_of(trimS);
        if(leftPos == std::string::npos || rightPos == std::string::npos) return "";
        return str.substr(leftPos, rightPos+1);
    }
}
