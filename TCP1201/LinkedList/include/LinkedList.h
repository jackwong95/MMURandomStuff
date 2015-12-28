#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
using namespace std;

template <typename T>
struct Node
{
    T item;
    Node *next = nullptr;
};

template <class T>
class LinkedList
{
    public:
        LinkedList(int _N = 0)
        :N(_N)
        {
        }

        ~LinkedList()
        {
        }

        void push_back(T item)
        {
            Node<T>* newNode = new Node<T>;
            newNode->item = item;
            if(tailNode == nullptr)
            {
                tailNode = newNode;
                headNode = newNode;
            }
            else
            {
                tailNode->next = newNode;
                tailNode = newNode;
            }
            N++;
        }

        void display()
        {
            Node<T>* currNode = headNode;
            while(currNode != nullptr)
            {
                cout << currNode->item << endl;
                currNode = currNode->next;
            }
        }

        void remove(int _idx)
        {
            if(_idx >= 0 && _idx <= (N-1))
            {
                int idx = 0;
                Node<T>* currNode = headNode;
                while(currNode != nullptr)
                {
                    if(_idx==0)
                    {
                        headNode = headNode->next;
                        N--;
                        break;
                    }
                    else if(idx == _idx && (idx-1)>=0)
                    {
                        Node<T>* previousNode = getNode(idx-1);
                        previousNode->next = currNode->next;
                        N--;
                        break;
                    }
                    idx ++;
                    currNode = currNode->next;
                }
            }
        }

        Node<T>* getNode(int i)
        {
            if(i >= 0 && i <= (N-1))
            {
                int idx = 0;
                Node<T>* currNode = headNode;
                while(currNode != nullptr)
                {
                    if(idx == i) return currNode;
                    idx ++;
                    currNode = currNode->next;
                }
            }
            return nullptr;
        }

        T* at(int i)
        {
            if(i >= 0 && i <= (N-1))
            {
                int idx = 0;
                Node<T>* currNode = headNode;
                while(currNode != nullptr)
                {
                    if(idx == i) return &(currNode->item);
                    idx ++;
                    currNode = currNode->next;
                }
            }
            return nullptr;
        }

        int findIdx(T item)
        {
            int idx = 0;
            Node<T>* currNode = headNode;
            while(currNode != nullptr)
            {
                if(currNode->item == item) return idx;
                idx ++;
                currNode = currNode->next;
            }
            return -1;
        }

        int size()
        {
            return N;
        }
        Node<T> *headNode = nullptr;
        Node<T> *tailNode = nullptr;
    private:
        int N;
};

#endif // LINKEDLIST_H
