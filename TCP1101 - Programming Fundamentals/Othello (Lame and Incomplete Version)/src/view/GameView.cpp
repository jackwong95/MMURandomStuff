/**********|**********|**********|
Program: GameView.cpp
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/
#include "GameView.h"
#include "board.h"
#include "Ultis.h"

#include <iostream>

GameView::GameView(Board* bd)
{
    board_ = bd;
}


void GameView::printGameBanner()
{
    try
    {
        ultis::readAndPrint("assets/GameBanner.txt");
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << "\n";
    }
}
void GameView::printUserOptions()
{
    try
    {
        bool playerHasMove = (((board_->whiteTurn && board_->whiteHasMove) || (!board_->whiteTurn && board_->blackHasMove)));

        std::cout << "\n\n";
        if(board_->isOver){
            if(board_->whiteScore>board_->blackScore)
                std::cout << "Player O has won the game!\n";
            if(board_->whiteScore<board_->blackScore)
                std::cout << "Player X has won the game!\n";
            if(board_->whiteScore==board_->blackScore)
                std::cout << "Game is even please try again!";
        }
        std::cout << "\n=*******************~GAME MENU~*******************=\n\n";
        if(!board_->isOver && playerHasMove)
            std::cout << "==> f 4\n";
        std::cout << "==> save filename.txt\n";
        std::cout << "==> menu\n";
        if(!board_->isOver)
            std::cout << "==> next player\n";
        if(((board_->whiteTurn && !board_->super1OUsed_)||(!board_->whiteTurn && !board_->super1XUsed_)) && !board_->isOver && playerHasMove)
            std::cout << "==> super1 capture f 4    ( Flip everything at a given point except empty spaces )\n";
        if(((board_->whiteTurn && !board_->super2OUsed_)||(!board_->whiteTurn && !board_->super2XUsed_)) && !board_->isOver)
            std::cout << "==> super2 flip       ( Swap players' markers )\n";
        std::cout << "==> clear console\n\n";
        if(((board_->whiteTurn && !board_->whiteHasMove) || (!board_->whiteTurn && !board_->blackHasMove))&&!board_->isOver)
            std::cout << "\n\nyou have no move left, please enter 'next player' for next player to move.\n";
        std::cout << "type the operation name.\nExample 'clear console'\n";
        //ultis::readAndPrint("assets/UserOptions.txt");
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << "\n";
    }
}
void GameView::printView()
{
    if(board_==nullptr)throw std::logic_error("GameView. Null pointer exception of type board_ view. Please ensure that board_view is pointing to a board_View instance.");
    printGameBanner();
    printBoard();
    printScore();
    printPlayerTurn();
    printUserOptions();

}


void GameView::printScore()
{
    std::cout << "Score : O = " << board_->whiteScore << " , X = " << board_->blackScore << std::endl;
}
void GameView::printPlayerTurn()
{
    std::cout << "Current player = " << ((board_->whiteTurn)?"O":"X") << std::endl;
}

void GameView::printSingleRow()
{
    std::cout << "    |";
    for(int i = 0; i < board_->sz_-1; i ++)
        std::cout << "---+";
    std::cout<<"---|\n";
}
void GameView::printNumber(int n)
{
    std::cout << n << " ";
}
void GameView::printBoard()
{
    for(int i = 0; i < board_->sz_; i ++)
    {
        printSingleRow();
        printNumber(board_->sz_-i);
        std::cout<< ((board_->sz_-i<10)?"  ":" ") ;
        for(int j = 0; j < board_->sz_; j ++)
        {
            std::cout << "| ";

            if(board_->getBoardName(j, i)==' ')
            {
                if((board_->whiteTurn && board_->whiteMarker[i][j]) || (!board_->whiteTurn && board_->blackMarker[i][j]))
                {
                    std::cout << "?";
                }
                else
                {
                    std::cout << " ";
                }
            }
            else
            {
                std::cout << board_->getBoardName(j, i);

            }
            std::cout << " ";
        }
        std::cout << "|\n";
    }
    printSingleRow();
    std::cout << "      ";
    for(int j = 0; j < board_->sz_; j ++)
    {
        char c = 'a';
        int i = c + j;
        std::cout << (char)i << "   ";
    }
    std::cout << "\n\n\n";
}
