/**********|**********|**********|
Program: GameManager.cpp
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/

#include "GameManager.h"

bool GameManager::instanceFlag = false;
GameManager* GameManager::single = NULL;
GameManager* GameManager::getInstance(){
    if(!instanceFlag){
        single = new GameManager();
        instanceFlag = true;
        return single;
    }else{
        return single;
    }
}

void GameManager::update(){
    while(!quitGame){
        int y, x, m;
        printGameMenu(board[selector]);
        pmInstance->print("\n");
        pmInstance->printPage("game.txt");
        string n = getSelectedString();
        while(!(std::find(operationVectors.begin(), operationVectors.end(), n) != operationVectors.end())){
            y = -1, x = - 1, m = 0;
            istringstream iss(n);
            string temp;
            while(getline(iss, temp, ' ')){
                if(m==0 && temp.length()==1){
                    x = (temp.c_str())[0]-'a';
                }else if (m==1 && ((temp.length()==1 && isdigit(temp.at(0))) || (temp.length()==2  && isdigit(temp.at(1))) ) ) {
                    y = board[selector].size-atoi(temp.c_str());
                }
                m ++;
            }
            if(m==2 && (x>=0&&x<=board[selector].size&&y>=0&&y<=board[selector].size) && board[selector].isLegal(Board::convertCoordToVec2D(x, y))) break;
            if(!board[selector].isOver)
                PrintManager::print("Invalid selection, please enter the name of your selection.");
            if(board[selector].isOver)
                PrintManager::print("You can now restart current board, or start a new game by typing 'restart current tab'");
            n = getSelectedString();
        }
        if(n=="next player"){
            if(!board[selector].isOver){
                board[selector].switchTurn();
            }
        }else if(n=="menu"){
            MenuManager::getInstance()->start();
            break;
        }else if(n=="restart current tab"){
            board[selector] = Board();
        }else if(n=="select tab"){
            PrintManager::print("Please select the tab number from 0-15\n");
            int m = getSelectedBoard();
            while(!(m>=0&&m<16)){
                PrintManager::print("Invalid Operation \nPlease select the tab number from 0-15\n");
                m = getSelectedBoard();
            }
            selector = m;
        }else if(n=="resize current tab"){
            PrintManager::print("Only 4, 6, 8, 10, 12, 14, 16 are valid for the size of board.\nPlease enter one of the size stated above to change.\n");
            int m = getSelectedBoard();
           while(!(m>=0&&m<=16) || !(m%2==0||m==2||m==0)){
                PrintManager::print("Invalid Operation \nPlease select the tab number from 0-16\n");
                m = getSelectedBoard();
            }
            board[selector] = Board(m);
        }else if(n=="restart everything"){
            restartBoard();
        }else if(n=="clear console"){
            MenuManager::clearConsole();
        }else{
            if(!board[selector].isOver && ((board[selector].whiteTurn && board[selector].whiteHasMove) || (!board[selector].whiteTurn && board[selector].blackHasMove)) ){
                board[selector].setBoardType(Board::convertCoordToVec2D(x, y));        }
        }
    }
}
//function to restart EVERYTHING, from tab 0 to 15. and set selector back to 0.
void GameManager::restartBoard(){
    for(int i = 0; i < 16; i ++){
        board[i] = Board(8);
    }
    selector = 0;
}
//function called when game is over.
void GameManager::gameIsOver(){
    quitGame = true;
}
//print out the board.
void GameManager::printGameMenu(Board board){
    pmInstance->printBoard(board);
    PrintManager::print("\n\n");
    pmInstance->printScore(board.whiteTurn, board.whiteScore, board.blackScore);

}
//this part of code is copied from the website given below, as solution will be SIMILAR even without the reference.
//http://codereview.stackexchange.com/questions/40124/trim-white-space-from-string
string GameManager::trim(string const& str)
{
    if(str.empty())
        return str;

    size_t firstScan = str.find_first_not_of(' ');
    size_t first = firstScan == string::npos ? str.length() : firstScan;
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, last-first+1);
}
//calls the main loop
void GameManager::start(){
    update();
}
//get selected board value within the game, that can have length of more than 2. for example, 345, 2356, 43432, 543534
int GameManager::getSelectedBoard(){
    string temp;
    getline(cin, temp);
    temp = GameManager::trim(temp);
    return atoi(temp.c_str());
}
//get selected board value within the game, that can only have length of one. for example 1, 4, 3, 9
string GameManager::getSelectedString(){

    if(!board[selector].isOver && ((board[selector].whiteTurn && !board[selector].whiteHasMove) || (!board[selector].whiteTurn && !board[selector].blackHasMove))){
        pmInstance->print("You do not have any moves left. \nPlease skip turn for opponent to move.");
    }
    if(board[selector].isOver){
        pmInstance->print("GAME IS OVER!! GOOD GAME, WELL PLAYED.\n");
        pmInstance->print(((board[selector].blackScore>board[selector].whiteScore)?"X won":(board[selector].blackScore<board[selector].whiteScore)?"O won":"draw!") );
    }
    return MenuManager::getSelectedString();
}

