/**********|**********|**********|
Program: GameController.cpp
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/
#include "GameInputHandler.h"
#include "MoveUnitCommand.h"
#include "NextPlayerCommand.h"
#include "Ultis.h"
#include "MenuCommand.h"
#include "ReverseCommand.h"
#include "MoveEnemyUnitRandomly.h"
#include "GameCommand.h"
#include "ClearConsoleCommand.h"
#include "SaveFileCommand.h"

GameInputHandler::GameInputHandler(GameController* gc, Board* board)
{
    gameController_ = gc;
    board_ = board;
}

bool GameInputHandler::isSuperPowa2(std::string str)
{
    std::vector<std::string> coord = ultis::split(str);
    if(coord.size()==0)return false;
    if(coord.size()<=4 && coord.at(0)=="super1" && coord.at(1)=="capture")
    {
        std::string temp = (coord.at(2) + " " + coord.at(3));
        if(ultis::isACoordinate(temp, board_))
        {
            return true;
        }
    }
    return false;
}

bool GameInputHandler::isSaveGame(std::string str)
{
    std::vector<std::string> coord = ultis::split(str);
    if(coord.size()==0)return false;
    if(coord.at(0)=="save")
    {
        return true;
    }
    return false;
}

Command* GameInputHandler::handleInput(const std::string str)
{
    std::string aux = str;
    aux = ultis::trim(aux, " ");
    aux = ultis::toLowerCase(aux);
    if(aux=="menu")return new MenuCommand(gameController_);
    if(aux=="clear console")return new ClearConsoleCommand();
    if(isSaveGame(aux))return new SaveFileCommand(board_, aux);
    if(!board_->isOver)
    {
        if(aux=="next player")return new NextPlayerCommand(board_);
        if(aux=="super2 flip")return new ReverseCommand(board_);
        if(ultis::isACoordinate(aux, board_))return new MoveUnitCommand(board_, ultis::inputToVector(aux, board_));
        if(isSuperPowa2(aux))return new MakeEnemyUnitRandomly(board_, aux);
    }
    return nullptr;
}
