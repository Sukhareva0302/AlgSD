#include <iostream>
using namespace std;

template <class T>
class Queue
{
private:
    class elem
    {
    public:
        T data;
        elem* next;
        elem(T new_data)
        {
            data = new_data;
            next = NULL;
        }
    };
    elem* head;
    elem* last;
public:
    Queue()
    {
        head = NULL;
        last = NULL;
    }
    Queue(T _data)
    {
        elem* newNode = new elem(_data);
        head = newNode;
        last = NULL;
    }
    void push(T data)
    {
        elem* tmp = new elem(data);
        if (head == NULL)
        {
            head = tmp;
            last = tmp;
        }
        else
        {
            last->next = tmp;
            last = tmp;
        }
    }
    void pop()
    {
        if (head == NULL)
        {
            throw out_of_range("No more elements");
        }
        else
        {
            elem* tmp = head;
            head = head->next;
            delete tmp;
        }
    }
    T top()
    {
        if (head == NULL)
        {
            throw out_of_range("Empty");
        }
        else
        {
            return head->data;
        }
    }
    bool Empty()
    {
        return(head == NULL);
    }
    void clear()
    {
        while (!Empty())
        {
            pop();
        }
    }
};