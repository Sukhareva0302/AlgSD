#include <iostream>
using namespace std;

template <class T>
class List
{
private:
    class Node {
    private:

    public:
        T data; //data in the node
        Node* next; //pointer to the next node
        Node(T intdata)
        {
            data = intdata; //the initialized data is set as the head
            next = NULL; //the text node is set as 'NULL', as there no next node
        }
        T getData() //function that return data of a given node
        {
            return data;
        }
        Node* getNext() //function that return pointer to the next element of given node
        {
            return next;
        }
        void setData(T newData) //function that set data as the new value
        {
            data = newData;
        }
        void setNext(Node* newNext) //function that set pointer as the new value
        {
            next = newNext;
        }
    };
    Node* head; //begining of the List
    //unsigned int error; //to find errors when using methods
    Node* search(size_t index) //searches for the node corresponding to the index
    {
        Node* cur = head; //current = head
        size_t counter = 0;
        while (counter < index)
        {
            cur = cur->getNext();
            counter++;
        }
        return cur;
    }
    void insert_first(T newData) //inserts first element in the List
    {
        Node* newNode = new Node(newData);
        head = newNode;
    }
    void delete_one()
    {
        Node* tmp = head;
        head = NULL;
        delete tmp;
    }
public:
    List() //start of the new List
    {
        head = NULL;
    }
    void push_back(T newData) //adds newData to the end of the List
    {
        if (isEmpty())
        {
            insert_first(newData);
        }
        else
        {
            Node* tmp = new Node(newData);
            Node* cur = head; //current = head
            while (cur->getNext() != NULL) { cur = cur->getNext(); }
            cur->setNext(tmp);
        }
    }
    void push_front(T newData) //adds newData to the beginning of the List
    {
        if (isEmpty())
        {
            insert_first(newData);
        }
        else
        {
            Node* tmp = new Node(newData);
            tmp->setNext(head);
            head = tmp;
        }
    }
    void pop_back() //deletes the node in the end
    {
        if (isEmpty())
        {
            throw invalid_argument("nothing to pop");
        }
        else
        {
            if (head->getNext() == NULL)
            {
                delete_one();
            }
            else
            {
                Node* cur = head; //current = head
                Node* tmp = cur->getNext();
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
    void pop_front() //deletes the node in the beginning
    {
        if (isEmpty())
        {
            throw invalid_argument("nothing to pop");
        }
        else
        {
            Node* tmp = head;
            head = head->getNext();
            delete tmp;
        }
    }
    void insert_Node(T newData, size_t index)//inserts an element by index (before the element that has been available by this index earlier)
    {
        if ((isEmpty()) || (get_size() <= index))
        {
            if (get_size() == index)
            {
                push_back(newData);
            }
            else
            {
                throw invalid_argument("wrong index");
            }
        }
        else
        {
            if (index == 0)
            {
                push_front(newData);
            }
            else
            {
                Node* prev = search(index - 1); // prev (previous) is set to node previous to the one that should be replaced
                Node* newNode = new Node(newData); // the newNode is the new node that will be available by this index
                newNode->setNext(prev->getNext());
                prev->setNext(newNode);
            }
        }
    }
    T at(size_t index) //gets data element in the node corresponding to the index
    {
        if ((isEmpty()) || (get_size() <= index))
        {
            throw invalid_argument("wrong index");
        }
        else
        {
            return search(index)->getData();
        }
    }
    bool contains (T _data) //searches for the node corresponding to the index
    {
        Node* cur = head; //current = head
        while (cur!=NULL)
        {
            if (cur->getData() == _data)
            {
                return true;
            }
            else
            {
                cur = cur->getNext();
            }
        }
        return false;
    }
    void remove(size_t index) //deletes the node corresponding to the index
    {
        if ((isEmpty()) || (get_size() <= index))
        {
            throw invalid_argument("wrong index");
        }
        else
        {
            if (index != 0)
            {
                Node* forDelete = search(index); // forDelete is set to the node that should be deleted 
                Node* prev = search(index - 1); // prev (previous) is set to node previous to the one that should be deleted 
                prev->setNext(forDelete->getNext());
                delete forDelete;
            }
            else
            {
                pop_front();
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
            cur = cur->getNext();
        }
        return counter;
    }
    void clear() //clears the entire List
    {
        Node* cur; //current
        while (head != NULL)
        {
            cur = head->getNext();
            delete head;
            head = cur;
        }
    }
    void set(size_t index, T newData) //replacing an element by index with a new value
    {
        if ((isEmpty()) || (get_size() <= index))
        {
            throw invalid_argument("wrong index");
        }
        else
        {
            search(index)->setData(newData);
        }
    }
    bool isEmpty() //checks if the List is empty
    {
        return head == NULL;
    }
    void insert_List(List* newList, size_t index) //inserts tne new List starting from the index
    {
        if (newList->head != NULL)
        {
            if ((isEmpty()) || (get_size() < index))
            {
                if (index == 0)
                {
                    head = newList->head;
                }
                else
                {
                    throw invalid_argument("wrong index");
                }
            }
            else
            {
                if (index == 0)
                {
                    Node* tmp = newList->head;
                    while (tmp->getNext() != NULL)
                    {
                        tmp = tmp->getNext();
                    }
                    tmp->setNext(head->getNext());
                    head->setNext(tmp);
                }
                else
                {
                    Node* prev = search(index - 1); //prev (previous) is set to node previous to the one starting from which a new list will be inserted
                    Node* newList_cur = newList->head; //newList_cur=current of the new List
                    while (newList_cur->getNext() != NULL)
                    {
                        newList_cur = newList_cur->getNext();
                    }
                    newList_cur->setNext(prev->getNext());
                    prev->setNext(newList->head);
                }
            }
        }
    }
    void printList()
    {
        Node* cur = head;
        while (cur != NULL)
        {
            cout << cur->data << "->";
            cur = cur->next;
        }
        cout<<"XXX\n";
    }
};



/*cout << "1) Add new Data to the end of the List.\n"
<< "2) Add new Data to the beginning of the List\n"
<< "3) Delete the node in the end of the List\n"
<< "4) Delete the node in the beginning of the List\n"
<< "5) Insert an element by Index (before the element that has been available by this index earlier)\n"
<< "6) Get Data element in the node corresponding to the Index\n"
<< "7) Delete the node corresponding to the Index\n"
<< "8) Get the size of the List\n"
<< "9) Clear the entire List\n"
<< "10) Replace an element by Index with a new Data\n"
<< "11) Check if the List is empty\n"
<< "12) Insert different List (1->2->3->XX) starting from the Index\n"
*/