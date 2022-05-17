#include <iostream>
#include <fstream>
#include<string>
#include "List.h"
using namespace std;

class Destanation
{
public:
    string name;
    int to;
    int from;
    Destanation(string _name, int _to, int _from)
    {
        name = _name;
        to = _to;
        from = _from;
    }
    Destanation()
    {
        name = "";
        to = -1;
        from = -1;
    }
    Destanation operator=(Destanation mc)
    {
        name = mc.name;
        to = mc.to;
        from = mc.from;
        return *this;
    }
};

class Node {
private:

public:
    string town; //data in the node
    int index;
    List<Destanation> list;
    Node* next; //pointer to the next node
    Node(string intdata, int _index)
    {
        town = intdata;
        index = _index;
        next = NULL; //the text node is set as 'NULL', as there no next node
    }
};

class TownList
{
private:
    Node* head; //begining of the List
    void insert_first(string newData, string name_to, int to, int from) //inserts first element in the List
    {
        Node* newNode = new Node(newData, 0);
        newNode->list.push_back(Destanation(name_to, to, from));
        head = newNode;
    }
    void delete_one()
    {
        Node* tmp = head;
        head = NULL;
        delete tmp;
    }
public:
    TownList() //start of the new List
    {
        head = NULL;
    }
    Node* get_head()
    {
        return head;
    }
    void push_back(string newData, string name_to, int to, int from) //adds newData to the end of the List
    {
        if (isEmpty())
        {
            insert_first(newData, name_to, to, from);
        }
        else
        {
            Node* tmp = new Node(newData, 1);
            int i = 1;
            Node* cur = head; //current = head
            while (cur->next != NULL) { cur = cur->next; i++; }
            tmp->index = i;
            tmp->list.push_back(Destanation(name_to, to, from));
            cur->next=tmp;
        }
    }
    void push_name_only(string newData)
    {
        Node* tmp = new Node(newData, 1);
        int i = 1;
        Node* cur = head; //current = head
        while (cur->next != NULL) { cur = cur->next; i++; }
        tmp->index = i;
        cur->next = tmp;
    }

    void pop_back() //deletes the node in the end
    {
        if (isEmpty())
        {
            throw invalid_argument("nothing to pop");
        }
        else
        {
            if (head->next == NULL)
            {
                delete_one();
            }
            else
            {
                Node* cur = head; //current = head
                Node* tmp = cur->next;
                while (tmp->next != NULL)
                {
                    cur = cur->next;
                    tmp = tmp->next;
                }
                cur->next=NULL;
                delete tmp;
            }
        }
    }

    size_t get_size() //gets the size of the List
    {
        Node* cur = head; //current = head
        size_t counter = 0;
        while (cur != NULL)
        {
            counter++;
            cur = cur->next;
        }
        return counter;
    }
    bool contains(string _data) //searches for the node corresponding to the index
    {
        Node* cur = head; //current = head
        while (cur != NULL)
        {
            if (cur->town == _data)
            {
                return true;
            }
            else
            {
                cur = cur->next;
            }
        }
        return false;
    }
    int get_index(string _data)
    {
        Node* cur = head;
        int i = 0;
        while (cur->town != _data)
        {
            cur = cur->next;
            i++;
        }
        return i;
    }
    void update_destanation(string name_from, string name_to, int to, int from)
    {
        Node* cur = head; //current = head
        while (cur->town !=name_from)
        {
                cur = cur->next;
        }
        cur->list.push_back(Destanation(name_to, to, from));
    }
    void clear() //clears the entire List
    {
        Node* cur; //current
        while (head != NULL)
        {
            cur = head->next;
            delete head;
            head = cur;
        }
    }
    bool isEmpty() //checks if the List is empty
    {
        return head == NULL;
    }
};
