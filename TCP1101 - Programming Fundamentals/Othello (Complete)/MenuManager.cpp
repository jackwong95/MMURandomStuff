/**********|**********|**********|
Program: MenuManager.cpp
Course: Degree In Computer Science - Game Development
Year: 2015/16 Trimester 1
Name: Wong Tiong Kiat
ID: 1132702943
Email: jackwongtiongkiat@gmail.com
Phone: 012-2321133
**********|**********|**********/

#include "MenuManager.h"

bool MenuManager::instanceFlag = false;
MenuManager* MenuManager::single = NULL;
MenuManager* MenuManager::getInstance(){
    if(!instanceFlag){
        single = new MenuManager();
        instanceFlag = true;
        return single;
    }else{
        return single;
    }
}

void MenuManager::start(){
    GameManager *gmInstance = GameManager::getInstance();
    PrintManager::getInstance()->printPage("banner.txt");
    string n = getSelectedString();
    while(!(std::find(operationVectors.begin(), operationVectors.end(), n) != operationVectors.end())){
        PrintManager::print("Invalid selection, please enter the name of your selection.");
        n = getSelectedString();
    }
    if(n=="new game"){
        gmInstance->restartBoard();
        gmInstance->start();
    }else if(n=="help"){
        clearConsole();
        PrintManager::getInstance()->printPage("help.txt");
        do{
            if(getSelectedString()=="back")break;
            PrintManager::print("Invalid selection, please type 'back' than press enter.");
        }while(true);
        start();
    }else if(n=="quit"){
        gmInstance->gameIsOver();
    }else if(n=="resume game"){
        gmInstance->start();
    }else if(n=="clear console"){
        clearConsole();
        start();
    }else{
        throw runtime_error("MenuManager.cpp: Illegal input");
    }
}
void MenuManager::clearConsole(){
    if(system("CLS")) system("CLEAR");
}
string MenuManager::getSelectedString(){
    string temp;
    cout << "==>";
    getline(cin, temp);
    temp = GameManager::trim(temp);
    transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
    return temp;
}
int MenuManager::getSelectedIndex(){
    //temporary string holder
    string temp;
    cout << "==>";
    //get whole line and assign it to temp
    getline(cin, temp);
    //trim it by calling gamemanager's static function
    temp = GameManager::trim(temp);
    //return the value by parsing it into integer
    return parseInt(temp);
}
//menu manager's parse from string to int function, it can only take in length of 1 string as I dont think i'll be adding more than 10 features in this game
int MenuManager::parseInt(string k){
    //check if k is 1
    if(k.length()==1){
        //if length of string is 1 then get the first character and if its digit
        if(isdigit(k.at(0))){
            //return it by converting it to integer.
            return atoi(k.c_str());
        }
    }
    //else return - 1.
    return -1;
}


