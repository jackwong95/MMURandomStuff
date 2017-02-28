/**********|**********|**********|
Program: MenuController.cpp
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/
#include "Ultis.h"
#include "MenuController.h"
#include "GameController.h"
#include "Command.h"
#include "MenuView.h"
#include "BannerView.h"
#include "MenuInputHandler.h"

#include <iostream>

MenuController::MenuController()
{
    if(menuView_==nullptr)
    {
        menuView_ = new MenuView();
    }
    if(bannerView_==nullptr)
    {
        bannerView_ = new BannerView();
    }
    if(inputHandler_==nullptr)
    {
        inputHandler_ = new MenuInputHandler(this);
    }
}

void MenuController::startMenu()
{
    bannerView_->printView();
    while(!quitGame_)
    {
        try
        {
            menuView_->printView();
            std::string input = ultis::getUserInput();
            Command* command = inputHandler_->handleInput(input);
            if(command==nullptr) std::cout << "Bummer! You've entered '" << input << "' an undefined operation.\nPlease re-enter the right one. :3" << std::endl;
            if(command!=nullptr) command->execute();
        }
        catch(const std::exception& e)
        {
            std::cout << e.what() << "\n";
        }
    }
}

void MenuController::setGameController(GameController* gc)
{
    gameController_ = gc;
}

GameController* MenuController::getGameController()
{
    if(gameController_!=nullptr) return gameController_;
    return nullptr;
}

void MenuController::quitGame()
{
    quitGame_ = true;
}
