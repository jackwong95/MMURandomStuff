///g++ -std=c++11 main.cpp -o myfile && myfile
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

///print("mytext.txt");
///mytext.txt file same level directory as the your main exe
bool print(const string fileName){
    ifstream inputFile;
    inputFile.open(fileName.c_str());
    if(!inputFile.good())
    {
        throw runtime_error(("Unable to print out file " + fileName));
    }
    string temp;
    while(getline(inputFile, temp)){
        cout << endl << temp;
    }
    inputFile.close();
    return true;
}

void saveTexts(const string fileName)
{
    string textToWrite = "This Text Allows \n and tis is the next line.\n";
    ofstream fwriter (fileName);
    fwriter << textToWrite;
    fwriter.close();
}

void clearConsole()
{
    system("CLS");
}

int toInteger(const string val)
{
    return atoi(val.c_str());
}

string toString(const int toConv)
{
    ostringstream stream;
    stream << toConv;
    return stream.str();
}

string toString(const float toConv)
{
    ostringstream stream;
    stream << toConv;
    return stream.str();
}

string toString(const double toConv)
{
    ostringstream stream;
    stream << toConv;
    return stream.str();
}

vector<string> split(const string s, const char delimeter)
{
    vector<string> tempVec;
    stringstream ss(s);
    string temp;
    while(getline(ss, temp, delimeter))
    {
        tempVec.push_back(temp);
    }
    return tempVec;
}

double toDouble(const string val)
{
    return atof(val.c_str());;
}

string trim(const string val)
{
    string aux = val;
    string temp = aux.erase(0, aux.find_first_not_of(' '));
    temp = aux.erase(aux.find_last_not_of(' ')+1);
    return temp;
}

string toLower(const string input)
{
    string tolower = input;
    for(unsigned int i = 0; i < tolower.length(); ++i)
    {
        if(tolower[i]>='A' && tolower[i]<='Z')
            tolower[i] = tolower[i]-('Z'-'z');
        else
            tolower[i] = tolower[i];
    }
    return tolower;
}

string replaceAll(const string input, const char replaceFrom, const char replaceTo)
{
    string toReplace = input;
    for(unsigned int i = 0; i < toReplace.length(); ++ i)
    {
        if(toReplace[i]==replaceFrom)
            toReplace[i] = replaceTo;
    }
    return toReplace;
}

void doubleDArray(int size)
{
    int** adjMatrix = nullptr;

    adjMatrix = new int*[size];
    for (int i = 0; i < size; i++)
        adjMatrix[i] = new int[size];

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            adjMatrix[i][j] = 0;
        }
    }
}

void deleteDoubleDArray()
{
    /*
    if(adjMatrix==nullptr) return;
    for (int i = 0; i < size; i++)
    {
        if(adjMatrix[i]!=nullptr)
            delete[] adjMatrix[i];
    }
    delete[] adjMatrix;
    adjMatrix = nullptr;
*/
}

void singleDArray(int N)
{
    int* id = nullptr;
    id = new int[N];
    ///initialize all arrays values
    for(int i = 0; i < N; i ++)
    {
        *(id + i) = i;
    }
}

void deleteSingleDArray()
{
    /*
    if(id!=nullptr)
        delete[] id;
    id = nullptr;
    */
}

class A
{
    public:
        int dataz;
        friend A operator* (A& a, A& e);
        friend istream& operator>> (istream& is, A& k);
        friend ostream& operator << (ostream& os, A const& k);
        int getSeconz () {return seconz;}
    private:
        int seconz;
};

A operator* (A& lfs, A& rhs)
{
    A newA;
    newA.seconz = lfs.seconz * rhs.seconz;
    return newA;
}

istream& operator >> (istream& is, A& k)
{
    is >> k.seconz;
    return is;
}

ostream& operator << (ostream& os, A const& k)
{
    os << k.seconz;
    return os;
}

bool comparable(const A& lhs, const A& rhs)
{
  return lhs.dataz < rhs.dataz;
}

void insertAlphabetically(A arrayz[10], int randomz)
{
    for(int i = 0; i < 10; i ++)
    {
        if(arrayz[i].dataz >= randomz)
        {
            arrayz[i].dataz = randomz;
            break;
        }
    }
}

///for sort using bubble go and check out City.cpp look for sort class.

int main()
{
    A sortedA[10];
    sortedA[0].dataz = 4;
    sortedA[1].dataz = 10;
    sortedA[2].dataz = 9;
    sortedA[3].dataz = 2;
    sortedA[4].dataz = 3;
    sortedA[5].dataz = 6;
    sortedA[6].dataz = 6;
    sortedA[7].dataz = 7;
    sortedA[8].dataz = 1;
    sortedA[9].dataz = 3;
    sort(begin(sortedA), end(sortedA), comparable);
    insertAlphabetically(sortedA, 8);
    for(int i = 0; i < 10; i ++) cout << sortedA[i].dataz << endl;
    A myA;
    A myB;
    cin >> myA;
    cin >> myB;
    A mynewVal = (myA*myB);
    std::cout << mynewVal;
    return 0;
}
