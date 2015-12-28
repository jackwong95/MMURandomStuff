#include <iostream>
#include "LinkedList.h"

using namespace std;

int main()
{
    LinkedList<int> linkedListed;

    linkedListed.push_back(12);
    linkedListed.push_back(3);
    linkedListed.push_back(37);
    linkedListed.push_back(7);
    linkedListed.remove(0);
    linkedListed.remove(2);
    cout << linkedListed.size() << endl;
    linkedListed.display();
    return 0;
}
