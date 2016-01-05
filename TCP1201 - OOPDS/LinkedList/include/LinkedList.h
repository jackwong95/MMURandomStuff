#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <stdexcept>
#include <exception>

template <typename T>
struct Node
{
    T item;
    Node *next = nullptr;
};

///functions available:
/*
void clr();
void reserve(int size);
void insert_at(int idx, T item)
void push_head(T item)
void push_tail(T item)
void pop_head(T item)
void pop_tail(T item)
void display()
void removeAt(int _idx)
T& getAt(int i)
int findIdx(T item)
int sz()
*/
template <class T>
class LinkedList
{
    public:
        LinkedList()
        :N(0)
        {
        }

        ~LinkedList()
        {
        }

        void clr()
        {
            while(headNode!=nullptr&&tailNode!=nullptr)
            {
                pop_head();
            }
        }

        void reserve_from_tail(int sz)
        {
            for(int i = 0; i < sz; i ++)
            {
                Node<T> newNode;
                push_tail(newNode.item);
            }
        }

        void reserve_from_head(int sz)
        {
            for(int i = 0; i < sz; i ++)
            {
                Node<T> newNode;
                push_head(newNode.item);
            }
        }

        void insert_at(int idx, T item)
        {
            getNode(idx) = item;
        }

        void push_tail(T item)
        {
            Node<T>* newNode = new Node<T>;
            newNode->item = item;
            if(N==0)
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

        void push_head(T item)
        {
            Node<T>* newNode = new Node<T>;
            newNode->item = item;
            if(N==0)
            {
                tailNode = newNode;
                headNode = newNode;
            }
            else
            {
                newNode->next = headNode;
                headNode = newNode;
            }
            N++;
        }
        T pop_head()
        {
            if(headNode==nullptr)
                throw std::out_of_range("Attempt to get nullptr node, LinkedList pop_head function.");
            T item = headNode->item;
            Node<T>* toDel = headNode;
            headNode = headNode->next;
            N--;
            delete toDel;
            toDel = nullptr;
            return item;
        }

        T pop_tail()
        {
            Node<T>* tempNode = getNode(N-2);
            if(tempNode==nullptr)
                throw std::out_of_range("Attempt to get nullptr node, LinkedList pop_tail function.");
            tempNode->next = nullptr;
            T item = tailNode->item;
            N--;
            delete tailNode;
            tailNode = nullptr;
            tailNode = tempNode;
            return item;
        }
        void display()
        {
            std::cout<<"Displaying all items in the list"<<std::endl;
            int idx = 0;
            Node<T>* currNode = headNode;
            while(currNode != nullptr)
            {
                std::cout << "Item " << idx << " : "  << currNode->item << std::endl;
                currNode = currNode->next;
                idx ++;
            }
        }

        void removeAt(int _idx)
        {
            if(_idx >= 0 && _idx <= (N-1))
            {
                int idx = 0;
                Node<T>* currNode = headNode;
                while(currNode != nullptr)
                {
                    if(_idx==0)
                    {
                        /*
                        headNode = headNode->next;
                        N--;
                        */
                        pop_head();
                        return;
                    }
                    else if(_idx==(N-1))
                    {
                        /*
                        delete tailNode;
                        tailNode = getNode(N-2);
                        tailNode->next = nullptr;
                        N--;
                        */
                        pop_tail();
                        return;
                    }
                    else if(idx == _idx && (idx-1)>=0)
                    {
                        Node<T>* previousNode = getNode(idx-1);
                        previousNode->next = currNode->next;
                        N--;
                        return;
                    }
                    idx ++;
                    currNode = currNode->next;
                }
            }
        }

        T& getAt(int i)
        {
            if(i >= 0 && i <= (N-1))
            {
                int idx = 0;
                Node<T>* currNode = headNode;
                while(currNode != nullptr)
                {
                    if(idx == i) return currNode->item;
                    idx ++;
                    currNode = currNode->next;
                }
            }
            throw std::out_of_range("Argument out of bounds, LinkedList getAt function.");
        }
        ///THIS WILL ONLY RETURN THE VERY FIRST VALUE FROM HEAD THAT IS EQUIVILENT OF ITEM
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

        int sz()
        {
            return N;
        }
    private:
        Node<T> *headNode = nullptr;
        Node<T> *tailNode = nullptr;
        int N;
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
            throw std::out_of_range("Argument out of bounds, LinkedList getNode function.");
        }
};

#endif // LINKEDLIST_H
