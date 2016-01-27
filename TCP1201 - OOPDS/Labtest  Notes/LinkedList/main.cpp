#include <iostream>
#include <stdexcept>

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
    /*
    */
    public:
        LinkedList()
        {
            N = 0;
        }
        ~LinkedList()
        {
            while(!empty())
            {
                pop_head();
            }
        }
        void insert_at(int idx, T item)
        {
            if (empty())
            {
                push_head(item);
                return;
            }
            if(idx == N)
            {
                push_tail(item);
                return;
            }
            Node<T>* currNode = headNode;
            Node<T>* prevNode = headNode;
            int idxCount = 0;
            if(!(idx >= 0 && idx <= N))
                throw runtime_error ("Out of range unable to insert at insert_at");
            while(true)
            {
                if(currNode->next == nullptr || idxCount == idx) break;
                prevNode = currNode;
                currNode = currNode->next;
                idxCount ++;
            }
            Node<T>* middleNode = new Node<T>;
            middleNode->item = item;
            middleNode->next = currNode;
            prevNode->next = middleNode;
            N++;
        }
        void remove(int _idx)
        {
            if(validate(_idx))
            {
                int idx = 0;
                Node<T>* currNode = headNode;
                Node<T>* previousNode = headNode;
                while(currNode != nullptr)
                {
                    if(_idx==0)
                    {
                        pop_head();
                        return;
                    }
                    else if(_idx==(N-1))
                    {
                        pop_tail();
                        return;
                    }
                    else if(idx == _idx && (idx-1)>=0)
                    {

                        previousNode->next = currNode->next;
                        currNode->next = nullptr;
                        delete currNode;
                        currNode = nullptr;
                        N--;
                        return;
                    }
                    idx ++;
                    previousNode = currNode;
                    currNode = currNode->next;
                }
            }
            throw runtime_error("remove function out of range");
        }
        void clear()
        {
            while(!empty())
            {
                pop_head();
            }
        }
        bool contains(T _item)
        {
            Node<T>* currNode = headNode;
            while(true)
            {
                if(currNode->next == nullptr) break;
                if(currNode->item == _item) return true;
                currNode = currNode->next;
            }
            return false;
        }
        T pop_head()
        {
            if(empty()) throw runtime_error("unable to pop tail because stack is empty");
            Node<T>* toDel = headNode;
            T toreturn = toDel->item;

            if(headNode->next != nullptr)
                headNode = headNode->next;
            else
                headNode = nullptr;

            toDel->next = nullptr;
            delete toDel;
            toDel = nullptr;
            N--;
            return toreturn;
        }
        T pop_tail()
        {
            if(empty()) throw runtime_error("unable to pop head because stack is empty");
            if(size()==1) return pop_head();

            Node<T>* currNode = headNode;
            Node<T>* prevNode = headNode;
            while(true)
            {
                if(currNode->next == nullptr) break;
                prevNode = currNode;
                currNode = currNode->next;
            }

            Node<T>* toDel = currNode;
            T toreturn = toDel->item;

            if(prevNode->next != nullptr)
                prevNode->next = nullptr;

            toDel->next = nullptr;
            delete toDel;
            toDel = nullptr;
            N--;
            return toreturn;
        }
        void push_head(T item)
        {
            Node<T>* newNode = new Node<T>;
            newNode->item = item;
            newNode->next = headNode;
            headNode = newNode;
            N ++;
        }
        void push_tail(T item)
        {
            if(empty())
            {
                push_head(item);
                return;
            }
            Node<T>* currNode = headNode;
            while(true)
            {
                if(currNode->next == nullptr) break;
                currNode = currNode->next;
            }
            Node<T>* newNode = new Node<T>;
            newNode->item = item;
            currNode->next = newNode;
            N ++;
        }
        T& at(int target)
        {
            if(validate(target))
            {
                Node<T>* currNode = headNode;
                int i = 0;
                while(true)
                {
                    if (i == target) return currNode->item;
                    currNode = currNode->next;
                    i ++;
                }
            }
            throw runtime_error("index out of range for at function");
        }
        int size() {return N;}
        bool empty() {return N == 0;}
        bool validate(int i) {return (i>=0 && i < N); }
    private:
        Node<T> *headNode = nullptr;
        int N;
};

int main()
{
    LinkedList<int> list;
    list.push_tail(23);
    list.push_head(43);
    list.push_tail(3);
    list.push_head(2);
    list.pop_head();
    list.push_head(4);
    list.push_head(5);
    list.pop_head();
    list.pop_head();
    list.pop_head();
    list.pop_head();
    list.pop_head();
    list.push_tail(9);
    list.push_head(2);
    list.push_head(1);
    list.push_tail(8);
    list.pop_tail();
    list.pop_head();
    list.push_tail(9);
    list.push_head(2);
    list.push_head(1);
    list.push_tail(8);
    list.pop_tail();
    list.pop_tail();
    list.pop_tail();
    list.pop_tail();
    list.pop_tail();
    list.pop_tail();
    list.push_tail(23);
    list.push_head(43);
    list.push_tail(3);
    list.push_head(2);
    list.clear();
    list.push_head(4);
    list.push_head(3);
    list.push_head(2);
    list.push_head(1);
    list.push_tail(5);
    list.push_tail(6);
    list.push_tail(7);
    list.push_tail(8);
    list.push_tail(9);
    list.remove(0);
    list.push_tail(10);
    list.push_head(1);
    list.remove(3);
    list.remove(8);
    list.remove(0);
    list.remove(0);
    list.remove(0);
    list.push_head(4);
    list.push_head(3);
    list.push_head(2);
    list.push_head(1);
    list.remove(list.size()-1);
    list.remove(list.size()-1);
    list.push_tail(8);
    list.push_tail(9);
    list.remove(5);
    list.insert_at(5, 6);
    list.insert_at(list.size(), list.size()+1);
    list.insert_at(list.size(), list.size()+1);
    list.insert_at(list.size(), list.size()+1);
    list.insert_at(list.size(), list.size()+1);
    list.insert_at(list.size(), list.size()+1);
    list.insert_at(list.size(), list.size()+1);
    list.clear();
    list.insert_at(0, 1);
    list.insert_at(1, 2);
    list.insert_at(2, 3);
    list.insert_at(3, 4);
    list.insert_at(4, 5);
    list.insert_at(5, 6);
    list.insert_at(list.size(), list.size()+1);
    list.insert_at(list.size(), list.size()+1);
    list.insert_at(list.size(), list.size()+1);

    for(int i = 0; i < list.size(); i ++)
    {
        cout << list.at(i) << endl;
    }

}
