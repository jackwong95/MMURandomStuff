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
//if empty constructor is called, then call the one with size.
Board::Board(){
    init(8);
}
//given the size of the board, call initialize method.
Board::Board(int size){
    init(size);
}
//initialize board, depending on the size select the middle point of the board and set default value of the layout.
void Board::init(int size_){
    if(size_%2!=0){
        throw runtime_error("Board.cpp: Unable to create board due to uneven size.");
    }else if(size_ < 3){
        throw runtime_error("Board.cpp: Unable to create board due to board being too small size.");
    }

    for(int i = 0; i < size_; i ++){
        for(int j = 0; j < size_; j ++){
            boardLayout[i][j] = NONE;
        }
    }


    int axis = (size_/2-1);

    boardLayout[axis][axis] = WHITE;
    boardLayout[axis+1][axis] = BLACK;
    boardLayout[axis][axis+1] = BLACK;
    boardLayout[axis+1][axis+1] = WHITE;

    size = size_;
    updateMarker();
}
//checks if the game is over, by updating the marker by scanning through the entire board. Inefficient but direct.
void Board::updateMarker(){
    whiteHasMove = false;
    blackHasMove = false;
    for(int i = 0; i < size; i ++){
        for(int j = 0; j < size; j ++){
            whiteMarker[i][j] = false;
            blackMarker[i][j] = false;
        }
    }
    for(int i = 0; i < size; i ++){
        for(int j = 0; j < size; j ++){
            Vector2D pos = convertCoordToVec2D(j, i);
            if(getBoardType(pos)==BLACK){
                hasChanged = false;
                addMarker(whiteMarker, WHITE, pos);
                if(hasChanged)whiteHasMove = true;
            }else if(getBoardType(pos)==WHITE){
                hasChanged = false;
                addMarker(blackMarker, BLACK, pos);
                if(hasChanged)blackHasMove = true;
            }
        }
    }
    if(!whiteHasMove&&!blackHasMove){
        isOver = true;
    }
}
//mark the array given a position of board type.
void Board::addMarker(bool (&arr) [16][16], BoardType bt, Vector2D pos){
    for(int i = 0; i < sizeof(directions)/sizeof(directions[0]); i ++){
        Vector2D dir = convertCoordToVec2D((pos.x + directions[i][0]), (pos.y + directions[i][1]));
        if(!isInBound(dir))continue;
        if(getBoardType(dir)!=NONE)continue;
            for(int j = 0; j < sizeof(directions)/sizeof(directions[0]); j ++){
                if(isNotAdjFromCoord(bt, dir, directions[j]) && isFlippable(bt, dir, directions[j])){
                    arr[dir.y][dir.x] = true;
                    hasChanged = true;
                    break;
            }
        }
    }
}
//set board type to a value given a position, calls update function, change player turn and create marker on boolean array.
void Board::setBoardType(Vector2D pos){
    updateBoard(bt, pos);
    switchTurn();
    updateMarker();
}
//look for all possible direction given a position check whether if they're flippable from that position. If a direction is flippable and its not next to the position, then flip it.
void Board::updateBoard(BoardType bt, Vector2D pos){
    for(int i = 0; i < sizeof(directions)/sizeof(directions[0]); i ++){
        if(isNotAdjFromCoord(bt, pos, directions[i]) && isFlippable(bt, pos, directions[i])){
            flip(bt, pos, directions[i]);
        }
    }
}
//flip the board recursively until it gets out of bound or reach empty vector and also call update method.
void Board::flip(BoardType bt, Vector2D pos, int direction[]){
    Vector2D dir = convertCoordToVec2D(pos.x+direction[0], pos.y+direction[1]);
    if(!isInBound(dir))return;
    if(getBoardType(dir)==NONE)return;
    if(getBoardType(pos) == bt)return;
    flip(bt, dir, direction);
    if(getBoardType(pos)!=bt){
        updateScore(bt, pos);
        boardLayout[pos.y][pos.x] = bt;
    }
}
//update the score given board type and position of occurance.
void Board::updateScore(BoardType bt, Vector2D pos){
        if(bt == BLACK){
            blackScore ++;
            if(getBoardType(pos)==WHITE)
                whiteScore --;
        }else if(bt == WHITE){
            whiteScore ++;
            if(getBoardType(pos)==BLACK)
                blackScore --;
        }
}
//change player's turn
void Board::switchTurn(){
    if(whiteTurn){
        whiteTurn = false;
        bt = BLACK;
    }else{
        whiteTurn = true;
        bt = WHITE;
    }
}
//set boardlayout's value to board type given the position
void Board::setBoard(BoardType bt, Vector2D pos){
    boardLayout[pos.y][pos.x] = bt;
}
//convert coordinate x and y to Vector2D struct.
Vector2D Board::convertCoordToVec2D(int x, int y){
    Vector2D temp;
    temp.x = x;
    temp.y = y;
    return temp;
}
//get type of board enum given the position.
Board::BoardType Board::getBoardType(Vector2D pos){
    if(isInBound(pos)){
        return boardLayout[pos.y][pos.x];
    }else{
    throw runtime_error("Board.cpp: Array out of bounds at boardType " +convertIntToStr(pos.x) + "," + convertIntToStr(pos.y));
    }
    throw runtime_error("Board.cpp: Unable to retrieve BoardType");
}
//get type of board name given the position.
string Board::getBoardName(Vector2D pos){
    return convertEnumToStr(getBoardType(pos));
    throw runtime_error("Board.cpp: Unable to convert BoardType to string");
}
//convert integer to string
string Board::convertIntToStr(int val){
    stringstream ss;
    ss << val;
    return ss.str();
}
//convert enum type to string
string Board::convertEnumToStr(BoardType bt){
    switch(bt){
        case WHITE:
            return "O";
        case BLACK:
            return "X";
        case NONE:
            return " ";
        default:
           throw runtime_error("Board.cpp: Unable to convert boardtype enum to string");
    }
}
//checks if the given coordinate is legit.
bool Board::isLegal(Vector2D pos){
    if(!isInBound(pos))return false;
    if((whiteTurn && whiteMarker[pos.y][pos.x])||(!whiteTurn && blackMarker[pos.y][pos.x])){
        return true;
    }
    return false;
}
//checks if the given coordinate has same type given the direction recursively.
bool Board::isFlippable(BoardType bt, Vector2D pos, int direction []){
    Vector2D dir = convertCoordToVec2D(pos.x+direction[0], pos.y+direction[1]);
    if(!isInBound(dir))return false;
    if(getBoardType(dir)==NONE)return false;
    if(getBoardType(dir) == bt || isFlippable(bt, dir, direction)) return true;
    return false;
}
//checks if given coordinate is within the range.
bool Board::isInBound(Vector2D pos){
    return (pos.x>=0) && (pos.x<size) && (pos.y>=0) && (pos.y<size);
}
//checks if the type of current position is the same as the ones adjacent to the current position, given the type.
bool Board::isNotAdjFromCoord(BoardType bt, Vector2D pos, int direction []){
    Vector2D dir = convertCoordToVec2D(pos.x+direction[0], pos.y+direction[1]);
    if(!isInBound(dir)) return false;
    if(getBoardType(dir)==NONE)return false;
    if(getBoardType(dir)!=bt)return true;
    return false;
}
