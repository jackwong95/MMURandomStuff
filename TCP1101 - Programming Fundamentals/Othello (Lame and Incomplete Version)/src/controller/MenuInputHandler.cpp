/**********|**********|**********|
Program: MenuInputHandler.cpp
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/
#include "MenuInputHandler.h"
#include "QuitCommand.h"
#include "GameCommand.h"
#include "ResumeGameCommand.h"
#include "ClearConsoleCommand.h"
#include "HelpCommand.h"
#include "HelpView.h"
#include "LoadFileCommand.h"
//for ifstream
#include <fstream>


MenuInputHandler::MenuInputHandler(MenuController* menuController)
{
    menuController_ = menuController;
    if(helpView_==nullptr)
    {
        helpView_ = new HelpView();
    }
}

bool MenuInputHandler::isLoadGame(std::string str)
{
    std::vector<std::string> coord = ultis::split(str);
    if(coord.size()==0)return false;
    if(coord.at(0)=="load")
    {
        std::ifstream inputFile;
        std::string path_ = "assets/games/" + coord.at(1);
        inputFile.open(path_.c_str());
        if(inputFile.good())return true;
    }
    return false;
}

Command* MenuInputHandler::handleInput(const std::string str)
{
    std::string aux = str;
    aux = ultis::trim(aux, " ");
    aux = ultis::toLowerCase(aux);
    if(aux=="new game")return new GameCommand(menuController_);
    if(aux=="help")return new HelpCommand(helpView_);
    if(aux=="quit")return new QuitCommand(menuController_);
    if(aux=="resume game")return new ResumeGameCommand(menuController_);
    if(aux=="clear console")return new ClearConsoleCommand();
    if(isLoadGame(aux))return new LoadFileCommand(menuController_, aux);
    return nullptr;
}


