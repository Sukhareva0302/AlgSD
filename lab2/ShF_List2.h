#include <iostream>
using namespace std;

class Node2 {
private:

public:
    int data; //data in the Node2
    char key; //data #2 (it will be char)
    Node2* next; //pointer to the next Node2
    Node2(char initkey, int intdata)
    {
        key = initkey;
        data = intdata; //the initialized data is set as the head
        next = NULL; //the text Node2 is set as 'NULL', as there no next Node2
    }
    Node2* getNext() //function that return pointer to the next element of given Node2
    {
        return next;
    }
    void setData(char newKey, int newData) //function that set data as the new value
    {
        data = newData;
        key = newKey;
    }
    void setNext(Node2* newNext) //function that set pointer as the new value
    {
        next = newNext;
    }
};

class List2
{
private:
    Node2* head; //begining of the List2
    unsigned int error; //to find errors when using methods
    Node2* search(size_t index) //searches for the Node2 corresponding to the index
    {
        Node2* cur = head; //current = head
        size_t counter = 0;
        while (counter < index)
        {
            cur = cur->getNext();
            counter++;
        }
        return cur;
    }
    void insert_first(char newKey, int newData) //inserts first element in the List2
    {
        Node2* newNode2 = new Node2(newKey, newData);
        head = newNode2;
    }
    void delete_one()
    {
        Node2* tmp = head;
        head = NULL;
        delete tmp;
    }
public:
    List2() //start of the new List2
    {
        head = NULL;
        error = 0;
    }
    Node2* get_head()
    {
        return head;
    }
    void reset_error()
    {
        error = 0;
    }
    unsigned int get_error()
    {
        return error;
    }

    void push_back(char newKey, int newData) //adds newData to the end of the List2
    {
        if (isEmpty())
        {
            insert_first(newKey, newData);
        }
        else
        {
            Node2* tmp = new Node2(newKey, newData);
            Node2* cur = head; //current = head
            while (cur->getNext() != NULL) { cur = cur->getNext(); }
            cur->setNext(tmp);
        }
    }
    void push_front(char newKey, int newData) //adds newData to the beginning of the List2
    {
        if (isEmpty())
        {
            insert_first(newKey, newData);
        }
        else
        {
            Node2* tmp = new Node2(newKey, newData);
            tmp->setNext(head);
            head = tmp;
        }
    }
    void pop_back() //deletes the Node2 in the end
    {
        if (isEmpty())
        {
            error = 1;
        }
        else
        {
            if (head->getNext() == NULL)
            {
                delete_one();
            }
            else
            {
                Node2* cur = head; //current = head
                Node2* tmp = cur->getNext();
                while (tmp->getNext() != NULL)
                {
                    cur = cur->getNext();
                    tmp = tmp->getNext();
                }
                cur->setNext(NULL);
                delete tmp;
            }
        }
    }
    void pop_front() //deletes the Node2 in the beginning
    {
        if (isEmpty())
        {
            error = 1;
        }
        else
        {
            Node2* tmp = head;
            head = head->getNext();
            delete tmp;
        }
    }
    void insert_Node2(char newKey, int newData, size_t index)//inserts an element by index (before the element that has been available by this index earlier)
    {
        if ((isEmpty()) || (get_size() <= index))
        {
            if (get_size() == index)
            {
                push_back(newKey, newData);
            }
            else
            {
                error = 1;
            }
        }
        else
        {
            if (index == 0)
            {
                push_front(newKey, newData);
            }
            else
            {
                Node2* prev = search(index - 1); // prev (previous) is set to Node2 previous to the one that should be replaced
                Node2* newNode2 = new Node2(newKey, newData); // the newNode2 is the new Node2 that will be available by this index
                newNode2->setNext(prev->getNext());
                prev->setNext(newNode2);
            }
        }
    }
    void remove(size_t index) //deletes the Node2 corresponding to the index
    {
        if ((isEmpty()) || (get_size() <= index))
        {
            error = 1;
        }
        else
        {
            if (index != 0)
            {
                Node2* forDelete = search(index); // forDelete is set to the Node2 that should be deleted 
                Node2* prev = search(index - 1); // prev (previous) is set to Node2 previous to the one that should be deleted 
                prev->setNext(forDelete->getNext());
                delete forDelete;
            }
            else
            {
                pop_front();
            }
        }
    }
    size_t get_size() //gets the size of the List2
    {
        Node2* cur = head; //current = head
        size_t counter = 0;
        while (cur != NULL)
        {
            counter++;
            cur = cur->getNext();
        }
        return counter;
    }
    void clear() //clears the entire List2
    {
        Node2* cur; //current
        while (head != NULL)
        {
            cur = head->getNext();
            delete head;
            head = cur;
        }
    }
    void set(size_t index, char newKey, int newData) //replacing an element by index with a new value
    {
        if ((isEmpty()) || (get_size() <= index))
        {
            error = 1;
        }
        else
        {
            search(index)->setData(newKey, newData);
        }
    }
    bool isEmpty() //checks if the List2 is empty
    {
        return head == NULL;
    }
    void insert_List2(List2* newList2, size_t index) //inserts tne new List2 starting from the index
    {
        if (newList2->head != NULL)
        {
            if ((isEmpty()) || (get_size() < index))
            {
                if (index == 0)
                {
                    head = newList2->head;
                }
                else
                {
                    error = 1;
                }
            }
            else
            {
                if (index == 0)
                {
                    Node2* tmp = newList2->head;
                    while (tmp->getNext() != NULL)
                    {
                        tmp = tmp->getNext();
                    }
                    tmp->setNext(head->getNext());
                    head->setNext(tmp);
                }
                else
                {
                    Node2* prev = search(index - 1); //prev (previous) is set to Node2 previous to the one starting from which a new List2 will be inserted
                    Node2* newList2_cur = newList2->head; //newList2_cur=current of the new List2
                    while (newList2_cur->getNext() != NULL)
                    {
                        newList2_cur = newList2_cur->getNext();
                    }
                    newList2_cur->setNext(prev->getNext());
                    prev->setNext(newList2->head);
                }
            }
        }
    }
    void printList2()
    {
        Node2* cur = head;
        while (cur != NULL)
        {
            cout << cur->key << ", "<< cur->data<< "->";
            cur = cur->next;
        }
        cout << "XXX\n";
    }
    List2 reverse()
    {
        Node2* cur = head;
        List2 reverce_list;
        while (cur != NULL)
        {
            reverce_list.push_front(cur->key, cur->data);
            cur = cur->next;
        }
        return reverce_list;
    }
    bool contains(char x)
    {
        Node2* cur = head;
        while (cur != NULL)
        {
            if (cur->key == x)
            {
                return true;
            }
            cur = cur->next;
        }
        return false;
    }
    void increase_periodicity(char x)
    {
        Node2* cur = head;
        while (cur->key!=x)
        {
            cur = cur->next;
        }
        cur->data++;
    }
    int return_data(char x)
    {
        {
            Node2* cur = head;
            while (cur->key != x)
            {
                cur = cur->next;
            }
            return cur->data;
        }
    }
    char return_char_one()
    {
        return head->key;
    }
    void copy(List2 listNew)
    {
        Node2* curNew = listNew.get_head();
        //Node<T> cur = head;
        while (curNew != NULL)
        {
            push_back(curNew->key, curNew->data);
            curNew = curNew->next;
        }
    }
};



/*cout << "1) Add new Data to the end of the List2.\n"
<< "2) Add new Data to the beginning of the List2\n"
<< "3) Delete the Node2 in the end of the List2\n"
<< "4) Delete the Node2 in the beginning of the List2\n"
<< "5) Insert an element by Index (before the element that has been available by this index earlier)\n"
<< "6) Get Data element in the Node2 corresponding to the Index\n"
<< "7) Delete the Node2 corresponding to the Index\n"
<< "8) Get the size of the List2\n"
<< "9) Clear the entire List2\n"
<< "10) Replace an element by Index with a new Data\n"
<< "11) Check if the List2 is empty\n"
<< "12) Insert different List2 (1->2->3->XX) starting from the Index\n"
*/#pragma once
