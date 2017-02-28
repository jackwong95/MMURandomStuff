/**********|**********|**********|
Program: PrintManager.cpp
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/

#include "PrintManager.h"
//part of singleton, which means there can be only an instance of this object
bool PrintManager::instanceFlag = false;
PrintManager* PrintManager::single = NULL;
PrintManager* PrintManager::getInstance(){
    if(!instanceFlag){
        single = new PrintManager();
        instanceFlag = true;
        return single;
    }else{
        return single;
    }
}
//Code on top is adapted but NOT plagiarise from http://www.codeproject.com/Articles/1921/Singleton-Pattern-its-implementation-with-C
//http://gameprogrammingpatterns.com/

//print out the board
void PrintManager::printBoard(Board board){
    cout << "=*******************~BOARD~*******************=\n\nM means the possible/legal moves for the current player\n\n";
    for(int i = 0; i < board.size; i ++){
        printEmptyRow(board);
        printNumber(board.size-i);
        cout<< ((board.size-i<10)?"  ":" ") ;
        for(int j = 0; j < board.size; j ++){
            printBoardUnit(board, board.getBoardName(Board::convertCoordToVec2D(j, i)), j, i);
            //printBoardUnit(board, j, i);
        }
        printClosingBracket();
    }
        printEmptyRow(board);
        printAlphabeticalRow(board);
        //printTabRow(16);
}
//print out the score and turn
void PrintManager::printScore(bool whiteTurn, int whiteScore, int blackScore){
    cout << "\nScore: O = "<<Board::convertIntToStr(whiteScore)<<" X = "<<Board::convertIntToStr(blackScore)<<"\nCurrent Player: "<< ((whiteTurn)?"O":"X")<<"\n";
}
//close bracket
void PrintManager::printClosingBracket(){
    cout << "|\n";
}
//print out the number of left
void PrintManager::printNumber(int n){
    cout << Board::convertIntToStr(n)<<" ";
}
//print out board unit
void PrintManager::printBoardUnit(Board board, string name, int x, int y){
    cout << "| ";
    if(name==" "){
        if(board.whiteTurn && board.whiteMarker[y][x]){
            cout << "M";
        }else if(!board.whiteTurn && board.blackMarker[y][x]){
            cout << "M";
        }else{
            cout << " ";
        }
    }else{
        cout << name;
    }
    cout <<" ";
}
void PrintManager::printEmptyRow(Board board){
    cout << "    |";
    for(int j = 0; j < board.size-1; j ++)
        cout << "---+";
    cout<<"---|\n";
}
//print message
void PrintManager::print(string msg){
    cout << msg << "\n";
}
//print message of integer
void PrintManager::print(string msg, int n){
    cout << msg << n <<"\n";
}
//print lower row
void PrintManager::printAlphabeticalRow(Board board){
    cout << "      ";
    for(int j = 0; j < board.size; j ++){
        char c = 'a';
        int i = c + j;
        cout << (char)i << "   ";
    }
}

void PrintManager::printPage(string fileName){
    //open file
    inputFile.open(fileName.c_str());
    if(!inputFile.good())throw runtime_error("PrintManager, File not found, or something is wrong with the stream");
    //create temporary holder for string as temp.
    string temp;
    //create a loop for the input file and assign temporary variable to temp.
    while(getline(inputFile, temp)){
        //print it out
        print(temp);
    }
    inputFile.close();
}
