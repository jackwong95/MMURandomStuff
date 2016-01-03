/**********|**********|**********|
Program: Board.cpp
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/

#include "Board.h"

Board::Board()
: Board(8)
{
}
Board::Board(int sz)
{
    if(sz%2!=0)throw std::logic_error("Board.cpp: Unable to create board due to uneven size.");
    if(sz < 3)throw std::logic_error("Board.cpp: Unable to create board due to board being too small size.");
    init(sz);
}
Board::Board(Type layout[16][16], int sz, bool isWhiteTurn, bool super1OUsed, bool super2OUsed, bool super1XUsed, bool super2XUsed)
{
    for(int i = 0; i < sz; i ++)
    {
        for(int j = 0; j < sz; j ++)
        {
            boardLayout[i][j] = layout[i][j];
            if(boardLayout[i][j]==WHITE)whiteScore ++;
            if(boardLayout[i][j]==BLACK)blackScore ++;
        }
    }

    whiteTurn = isWhiteTurn;
    super1OUsed_ = super1OUsed;
    super2OUsed_ = super2OUsed;
    super1XUsed_ = super1XUsed;
    super2XUsed_ = super2XUsed;
    sz_ = sz;
    updateMarker();
}
void Board::init(int sz)
{
    for(int i = 0; i < sz; i ++)
    {
        for(int j = 0; j < sz; j ++)
        {
            boardLayout[i][j] = NONE;
        }
    }


    int axis = (sz/2-1);
    setBoardAt(WHITE, axis, axis);
    setBoardAt(WHITE, axis+1, axis+1);
    setBoardAt(BLACK, axis, axis+1);
    setBoardAt(BLACK, axis+1, axis);
    sz_ = sz;
    updateMarker();
}
void Board::updateMarker(){
    whiteHasMove = false;
    blackHasMove = false;
    for(int i = 0; i < sz_; i ++){
        for(int j = 0; j < sz_; j ++){
            whiteMarker[i][j] = false;
            blackMarker[i][j] = false;
        }
    }
    for(int i = 0; i < sz_; i ++){
        for(int j = 0; j < sz_; j ++){
            if(boardLayout[i][j]==BLACK){
                hasChanged = false;
                addMarker(whiteMarker, WHITE, j, i);
                if(hasChanged)whiteHasMove = true;
            }else if(boardLayout[i][j]==WHITE){
                hasChanged = false;
                addMarker(blackMarker, BLACK, j, i);
                if(hasChanged)blackHasMove = true;
            }
        }
    }
    if(!whiteHasMove&&!blackHasMove){
        isOver = true;
    }
}
void Board::addMarker(bool (&arr) [16][16], Type bt, int xPos, int yPos)
{
    for(unsigned int i = 0; i < sizeof(directions)/sizeof(directions[0]); i ++)
    {
        int dirX = xPos + directions[i][0];
        int dirY = yPos + directions[i][1];
        if(!isInBound(dirX, dirY))continue;
        if(boardLayout[dirY][dirX]!=NONE)continue;
        for(unsigned int j = 0; j < sizeof(directions)/sizeof(directions[0]); j ++)
        {
            if(flip(bt, dirX, dirY, directions[j][0], directions[j][1], true, false, false))
            {
                arr[dirY][dirX] = true;
                hasChanged = true;
                break;
            }
        }
    }
}

void Board::reverseBoard()
{
    if(whiteTurn) super2OUsed_ = true;
    else if(!whiteTurn) super2XUsed_ = true;
    int tempWhite = 0, tempBlack = 0;
    for(int i = 0; i < sz_; i ++)
    {
        for(int j = 0; j < sz_; j ++)
        {
            if(boardLayout[i][j] == WHITE)
            {
                tempBlack ++;
                boardLayout[i][j] = BLACK;
            }else if(boardLayout[i][j] == BLACK)
            {
                tempWhite ++;
                boardLayout[i][j] = WHITE;
            }
        }
    }
    whiteScore = tempWhite;
    blackScore = tempBlack;
    switchTurn();
    updateMarker();
}

void Board::setBoardType(int x, int y, bool toNuke)
{
    if(whiteTurn && toNuke) super1OUsed_ = true;
    else if(!whiteTurn && toNuke) super1XUsed_ = true;
    updateBoard(bt, toNuke, x, y);
    switchTurn();
    updateMarker();
}
void Board::updateBoard(Type bt, bool toNuke, int x, int y){
    for(unsigned int i = 0; i < sizeof(directions)/sizeof(directions[0]); i ++){
        flip(bt, x, y, directions[i][0], directions[i][1], true, true, toNuke);
    }
}

char Board::getBoardName(int x, int y){
    return (char)boardLayout[y][x];
}

bool Board::isLegal(int x, int y){
    if(!isInBound(x, y))return false;
    if((whiteTurn && whiteMarker[y][x])||(!whiteTurn && blackMarker[y][x])){
        return true;
    }
    return false;
}

void Board::switchTurn()
{
    if(whiteTurn)
    {
        whiteTurn = false;
        bt = BLACK;
    }
    else
    {
        whiteTurn = true;
        bt = WHITE;
    }
}

void Board::setBoardAt(Type toChange, int x, int y)
{
    boardLayout[y][x] = toChange;
}

void Board::updateScore(Type toUpdate, int x, int y)
{
        if(toUpdate == BLACK) blackScore ++;
        if(toUpdate == WHITE) whiteScore ++;
        if(boardLayout[y][x]== WHITE) whiteScore --;
        if(boardLayout[y][x]== BLACK) blackScore --;
}

bool Board::isInBound(int x, int y)
{
    return (x>=0) && (x<sz_) && (y>=0) && (y<sz_);
}

bool Board::flip(Type changeTo, int xPos, int yPos, int xDir, int yDir, bool isAdjFromOrigin, bool toFlip, bool nuke)
{
    int newDirX = xPos + xDir;
    int newDirY = yPos + yDir;
    if(!isInBound(newDirX, newDirY)) return false;
    if(nuke)
    {
        updateScore(changeTo, xPos, yPos);
        setBoardAt(changeTo, xPos, yPos);
    }
    if(boardLayout[newDirY][newDirX]==NONE || (isAdjFromOrigin && boardLayout[newDirY][newDirX]==changeTo))return false;
    if((!nuke && boardLayout[newDirY][newDirX]==changeTo && !isAdjFromOrigin) || flip(changeTo, newDirX, newDirY, xDir, yDir, false, toFlip, nuke))
    {
        if(toFlip)
        {
            updateScore(changeTo, xPos, yPos);
            setBoardAt(changeTo, xPos, yPos);
        }
        return true;
    }
    return false;
}
