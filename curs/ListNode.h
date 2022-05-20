#include <iostream>
#include <fstream>
#include<string>
#include "Map.h"
using namespace std;

class Node {
private:

public:
    string name; //data in the node
    //int index;
    Map<string, int> capacity;
    Map<string, int> flow;
    Node* parent;
    Node* next; //pointer to the next node
    Node(string intdata)
    {
        name = intdata;
        //index = _index;
        next = NULL; //the text node is set as 'NULL', as there no next node
        parent = NULL;
    }
    void update_capacity(string key, int newValue)
    {
        capacity.update_val(key, newValue);
    }
    void update_flow(string key, int newValue)
    {
        flow.update_val(key, newValue);
    }
    int get_flow(string key)
    {
        return flow.find(key);
    }
    int get_capacity(string key)
    {
        return capacity.find(key);
    }
};

class NodeList
{
private:
    Node* head; //begining of the List
    void insert_first(string newData, string name_to, int to) //inserts first element in the List
    {
        Node* newNode = new Node(newData);
        newNode->capacity.insert(name_to, to);
        newNode->flow.insert(name_to, 0);
        head = newNode;
    }
    void delete_one()
    {
        Node* tmp = head;
        head = NULL;
        delete tmp;
    }
public:
    NodeList() //start of the new List
    {
        head = NULL;
    }
    Node* get_head()
    {
        return head;
    }
    void push_back(string newData, string name_to, int to) //adds newData to the end of the List
    {
        if (isEmpty())
        {
            insert_first(newData, name_to, to);
        }
        else
        {
            Node* tmp = new Node(newData);
            Node* cur = head; //current = head
            while (cur->next != NULL) { cur = cur->next;}
            tmp->capacity.insert(name_to, to);
            tmp->flow.insert(name_to, 0);
            cur->next = tmp;
        }
    }
    void push_name_only(string newData)
    {
        Node* tmp = new Node(newData);
        Node* cur = head; //current = head
        while (cur->next != NULL) { cur = cur->next;}
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
                cur->next = NULL;
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

    Node* at(size_t index) //gets data element in the node corresponding to the index
    {
        if ((isEmpty()) || (get_size() <= index))
        {
            throw invalid_argument("wrong index");
        }
        else
        {
            Node* cur = head; //current = head
            size_t counter = 0;
            while (counter < index)
            {
                cur = cur->next;
                counter++;
            }
            return cur;
        }
    }

    bool contains(string _data) //searches for the node corresponding to the index
    {
        Node* cur = head; //current = head
        while (cur != NULL)
        {
            if (cur->name == _data)
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
    void update_destanation(string name_from, string name_to, int to)
    {
        Node* cur = head; //current = head
        while (cur->name != name_from)
        {
            cur = cur->next;
        }
        cur->capacity.insert(name_to, to);
        cur->flow.insert(name_to, 0);
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
    Node* find(string _name)
    {
        Node* cur = head; //current = head
        while (cur->name != _name)
        {
            cur = cur->next;
        }
        return cur;
    }
};

NodeList form_List_from_file(string file_name)
{
    NodeList listT;
    string str;
    string town_from;
    string town_to;
    int to;
    string sub_str;
    //int from;
    int pos;
    fstream file;
    file.open(file_name, ios::in);
    while (!file.eof())
    {
        getline(file, str);
        pos = str.find(" ");
        town_from = str.substr(0, pos);
        str.erase(0, (pos + 1));
        pos = str.find(" ");
        town_to = str.substr(0, pos);
        str.erase(0, (pos + 1));
        to = stoi(str);
        if (!listT.contains(town_from))
        {
            listT.push_back(town_from, town_to, to);
        }
        else
        {
            listT.update_destanation(town_from, town_to, to);
        }
        if (!listT.contains(town_to))
        {
            listT.push_name_only(town_to);
        }
    }
    file.close();
    return listT;
}
NodeList form_List_from_string(string string_name)
{
    NodeList listT;
    string str_og = string_name;
    string str;
    string town_from;
    string town_to;
    int to;
    string sub_str;
    //int from;
    int pos;
    while (str_og!="")
    {
        pos = str_og.find("/");
        if (pos == -1)
        {
            str = str_og;
            str_og = "";
        }
        else
        {
            str = str_og.substr(0, pos);
            str_og.erase(0, (pos + 1));
        }

        pos = str.find(" ");
        town_from = str.substr(0, pos);
        str.erase(0, (pos + 1));
        pos = str.find(" ");
        town_to = str.substr(0, pos);
        str.erase(0, (pos + 1));
        to = stoi(str);
        if (!listT.contains(town_from))
        {
            listT.push_back(town_from, town_to, to);
        }
        else
        {
            listT.update_destanation(town_from, town_to, to);
        }
        if (!listT.contains(town_to))
        {
            listT.push_name_only(town_to);
        }
    }
    return listT;
}
void reset_prev(NodeList list)
{
    for (int i = 0; i < list.get_size(); i++)
    {
        list.at(i)->parent = NULL;
    }
}