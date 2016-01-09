#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include "City.h"
#include "Attraction.h"
#include "Sport.h"
#include "Culture.h"
#include "Shopping.h"

using namespace std;

vector<City> cities;

City* citySelection(bool& hasSelectedCity, bool& toLoop)
{
    ///do bubble sort
    for (int i = 0 ; i < cities.size() - 1 ; i++)
    {
        for (int j = 0 ; j < cities.size() - 1 ; j++)
        {
            string val1 = cities.at(j).getName();
            string val2 = cities.at(j+1).getName();
            if ( val1 > val2 )
            {
                string temp = val1;
                cities.at(j).setName(val2);
                cities.at(j+1).setName(temp);
            }
        }
    }


    City* targetCity = nullptr;
    for(int i = 0; i < (int)cities.size(); i ++)
    {
        cities.at(i).display();
    }
    cout << "Please select the city by entering the name" << endl;
    cout << "To stop the program enter \"break\"" << endl;
    string input;
    getline(cin, input);
    if(input == "break") toLoop = false;
    for(int i = 0; i < (int)cities.size(); i ++)
    {
        City tempCity = cities.at(i);
        if(tempCity.getName() == input)
        {
            targetCity = &cities.at(i);
            break;
        }
    }
    if(targetCity!=nullptr)
    {
        hasSelectedCity = true;
    }
    return targetCity;
}

void attractionSelection(City* city)
{
    while(true)
    {
        if(city==nullptr)break;
        int shoppingCount = 0, cultureCount = 0, sportCount = 0;
        vector<Attraction*> attractions = city->getAttraction();
        for(int i = 0; i < (int)attractions.size(); i ++)
        {
            if(attractions.at(i)->getTypeID() == 1)
            {
                sportCount ++;
            }else if(attractions.at(i)->getTypeID() == 2)
            {
                cultureCount ++;
            }else if(attractions.at(i)->getTypeID() == 3)
            {
                shoppingCount ++;
            }
        }
        cout << "The number of sport attractions available in this city : " << sportCount << endl;
        cout << "The number of culture attractions available in this city : " << cultureCount << endl;
        cout << "The number of shopping attractions available in this city : " << shoppingCount << endl;
        cout << "Please select the attraction by entering the \"attraction type\" to display everything enter *" << endl;
        cout << "To return enter \"break\"" << endl;
        string input;
        getline(cin, input);
        if(input == "break") break;
        for(int i = 0; i < (int)attractions.size(); i ++)
        {
            ///TYPEID 1 = Sport
            ///TYPEID 2 = Culture
            ///TYPEID 3 = Shopping
            if((input=="*" || input=="culture") && attractions.at(i)->getTypeID()==2)
            {
                Culture* k = (Culture*)(attractions.at(i));
                k->display();
            }else if((input=="*" || input=="sport") && attractions.at(i)->getTypeID()==1)
            {
                Sport* k = (Sport*)(attractions.at(i));
                k->display();
            }else if((input=="*" || input=="shopping") && attractions.at(i)->getTypeID()==3)
            {
                Shopping* k = (Shopping*)(attractions.at(i));
                k->display();
            }
        }

    }
}

City* getCityByID(vector<City> cities, int id)
{
    for(int i = 0; i < cities.size(); i ++)
    {
        if(cities[i].getID()==id)
        {
            return &cities[i];
        }
    }
    return nullptr;
}

bool isCityWithinTheVector(vector<City*>* cities, int id)
{
    for(int i = 0; i < cities->size(); i ++)
    {
        if(cities->at(i)->getID()==id)
        {
            return true;
        }
    }
    return false;
}

void connect(City* c1, City* c2)
{
    c1->connections->push_back(c2->getID());
    c2->connections->push_back(c1->getID());
}

bool isConnected(vector<City> cities, vector<City*>* visitedCities, stack<City*>* trace, City* toFind)
{

    City* root;
    if(!trace->empty())
    {
        root = trace->top();
        trace->pop();
        visitedCities->push_back(root);
        //cout << "Current root name : " << root->getName() << endl;
        if(root->getID()==toFind->getID())
        {
            //cout << "Returned true " << root->getName() << " " << root->getID() << endl;
            //cout << "Returned true " << toFind->getName() << " " << toFind->getID() << endl;
            return true;
        }
    }else if(trace->empty())
    {
        //cout << "Stack is empty " << endl;
        return false;
    }

    for(int i = 0; i < root->connections->size(); i ++)
    {
        //cout << "Connections of ID : " << root->connections->at(i) << endl;
        if(!isCityWithinTheVector(visitedCities, root->connections->at(i)))
        {
            trace->push(getCityByID(cities, root->connections->at(i)));
        }
        if(isConnected(cities, visitedCities, trace, toFind)) return true;
    }
    return false;
}

bool isConnected(vector<City> cities, City* root, City* toFind)
{
    if(root == nullptr || toFind == nullptr )
    {
        cout << "Null pointer paramter given at isConnected function."<<endl;
        return false;
    }
    vector<City*>* visitedCities = new vector<City*>;
    stack<City*>* trace = new stack<City*>;
    trace->push(root);
    return isConnected(cities, visitedCities, trace, toFind);
}

int main()
{
    ///TYPEID 1 = Sport
    ///TYPEID 2 = Culture
    ///TYPEID 3 = Shopping
    ///CITY ONE DETAILS
    City cityOne(100, "City one");

    Sport c1Sport1 = Sport (101, 1, 20, "Sport one");
    Sport c1Sport2 = Sport(102, 1, 25, "Sport two");
    Sport c1Sport3 = Sport(103, 1, 30, "Sport three");

    Culture c1Cul1 = Culture(104, 2, 30.0d, "Culture one");
    Culture c1Cul2 = Culture(105, 2, 23.4d, "Culture two");

    Shopping c1Shop1 = Shopping(106, 3, "Shopping one");
    c1Shop1.addMall("Mall one");
    c1Shop1.addMall("Mall two");
    c1Shop1.addMall("Mall three");
/*
    Attraction* att = (Attraction*)(&c1Cul1);
    Culture* cul = (Culture*)(att);
    cul->display();*/

    ///UPCAST ALL SHOPPINGS, because SHOPPING is not An Attraction so you upcast it.
    Attraction* c1Shop1Temp = (Attraction*)(&c1Shop1);
    Attraction* c1Sport1Temp = (Attraction*)(&c1Sport1);
    Attraction* c1Sport2Temp = (Attraction*)(&c1Sport2);
    Attraction* c1Sport3Temp = (Attraction*)(&c1Sport3);
    Attraction* c1Cul1Temp = (Attraction*)(&c1Cul1);
    Attraction* c1Cul2Temp = (Attraction*)(&c1Cul2);
    ///ADD ALL ATTRACTIONS.
    cityOne.addAttraction(c1Sport1Temp);
    cityOne.addAttraction(c1Sport2Temp);
    cityOne.addAttraction(c1Sport3Temp);
    cityOne.addAttraction(c1Cul1Temp);
    cityOne.addAttraction(c1Cul2Temp);
    cityOne.addAttraction(c1Shop1Temp);

    City cityTwo(200, "City two");

    Culture c2Cul1 = Culture(201, 2, 30.0d, "Culture one");
    Culture c2Cul2 = Culture(202, 2, 23.4d, "Culture two");

    Shopping c2Shop1 = Shopping(203, 3, "Shopping one");
    c2Shop1.addMall("Mall one");
    c2Shop1.addMall("Mall two");
    c2Shop1.addMall("Mall three");
    Shopping c2Shop2 = Shopping(204, 3, "Shopping two");
    c2Shop2.addMall("Mall one");

    ///UPCAST ALL SHOPPINGS, because SHOPPING is not An Attraction so you upcast it.
    Attraction* c2Cul1Temp = (Attraction*)(&c2Cul1);
    Attraction* c2Cul2Temp = (Attraction*)(&c2Cul2);
    Attraction* c2Shop1Temp = (Attraction*)(&c2Shop1);
    Attraction* c2Shop2Temp = (Attraction*)(&c2Shop2);
    ///ADD ALL ATTRACTIONS.
    cityTwo.addAttraction(c2Cul1Temp);
    cityTwo.addAttraction(c2Cul2Temp);
    cityTwo.addAttraction(c2Shop1Temp);
    cityTwo.addAttraction(c2Shop2Temp);

    ///ADD city one and two into vector of cities
    cities.push_back(cityOne);
    cities.push_back(cityTwo);

    ///lazy to add more, add it yourself.
    /*
    City c3(300, "City three");
    City c4(400, "City four");
    */

    while(true)
    {
        bool hasSelectedCity = false, toLoop = true;
        City* city = nullptr;
        city = citySelection(hasSelectedCity, toLoop);
        if(hasSelectedCity)
        {
            attractionSelection(city);
        }
        if(!toLoop)break;
    }

    ///all IDs have to be unique for this to work, because i'm too lazy of think of any other way.
    City A(1, "A");
    City B(2, "B");
    City C(3, "C");
    City D(4, "D");
    City E(5, "E");
    City F(6, "F");
    City G(7, "G");
    City H(8, "H");

    ///store all of these cities into a vector
    vector<City> cities;
    cities.push_back(A);
    cities.push_back(B);
    cities.push_back(C);
    cities.push_back(D);
    cities.push_back(E);
    cities.push_back(F);
    cities.push_back(G);
    cities.push_back(H);

    ///set up all of connections
    ///if A is connected to B, B is also said to be connected to A
    connect(&A, &B);
    connect(&A, &D);
    connect(&A, &E);
    connect(&D, &B);
    connect(&D, &E);
    connect(&B, &C);
    connect(&E, &C);
    connect(&C, &H);

    ///cities is the cities you want to check, and input are 2 cities
    bool isAConnectedToF = isConnected(cities, &A, &F);
    if(isAConnectedToF)
    {
        cout << "City A is Connected To City F" << endl;
    }
    else
    {
        cout << "City A is Not Connected To City F" << endl;
    }

    bool isAConnectedToB = isConnected(cities, &A, &B);
    if(isAConnectedToB)
    {
        cout << "City A is Connected To City B" << endl;
    }
    else
    {
        cout << "City A is Not Connected To City B" << endl;
    }

    bool isAConnectedToH = isConnected(cities, &A, &H);
    if(isAConnectedToH)
    {
        cout << "City A is Connected To City H" << endl;
    }
    else
    {
        cout << "City A is Not Connected To City H" << endl;
    }

    bool isAConnectedToA = isConnected(cities, &A, &A);
    if(isAConnectedToH)
    {
        cout << "City A is Connected To City A" << endl;
    }
    else
    {
        cout << "City A is Not Connected To City A" << endl;
    }

    return 0;
}
