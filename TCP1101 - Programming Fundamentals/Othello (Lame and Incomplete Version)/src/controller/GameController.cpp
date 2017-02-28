/**********|**********|**********|
Program: GameController.cpp
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/
#include "GameController.h"
#include "Ultis.h"
#include "GameInputHandler.h"
#include "Command.h"
#include "Board.h"
#include "GameView.h"

#include <iostream>

GameController::GameController()
{
    if(board_==nullptr)
    {
        board_ = new Board();
    }
    if(gameView_==nullptr)
    {
        gameView_ = new GameView(board_);
    }
    if(inputHandler_==nullptr)
    {
        inputHandler_ = new GameInputHandler(this, board_);
    }
}
GameController::GameController(Board* board)
{
    board_ = board;
    if(gameView_==nullptr)
    {
        gameView_ = new GameView(board_);
    }
    if(inputHandler_==nullptr)
    {
        inputHandler_ = new GameInputHandler(this, board_);
    }
}
void GameController::onGamePause()
{
    gameResume_ = false;
}
void GameController::onGameResume()
{
    gameResume_ = true;
}

void GameController::update()
{
    while(gameResume_)
    {
        try
        {
            gameView_->printView();
            std::string input = ultis::getUserInput();
            Command* command = inputHandler_->handleInput(input);
            if(command==nullptr) throw std::logic_error ("Bummer! You've entered '" + input + "' an undefined operation.\nPlease re-enter the right one. :3");
            if(command!=nullptr) command->execute();
        }
        catch(const std::exception& e)
        {
            std::cout << e.what() << "\n";
        }
    }
}
