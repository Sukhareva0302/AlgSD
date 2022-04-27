#include <iostream>
#include "List.h"
using namespace std;

template <class T>
class Iterator
{
public:
    virtual T next() = 0;
    virtual bool has_next() = 0;
};

template <class T1, class T2>
class RBTree
{
private:
    class Node {
    private:
        T1* key; //key for node
        T2 data; //data in the node
        bool color; //0 - Red, 1 - Black

        Node* parent; //pointer to the parent node
        Node* left; //pointer to the left node
        Node* right;//pointer to the right node
    public:
        friend class RBTree;
        Node(T1 newKey, T2 newData)
        {
            key = new T1;
            *key = newKey;
            data = newData;
            color = 0;

            parent = NULL;
            left = NULL;
            right = NULL;
        }
        Node()
        {
            key = NULL;
            data = 0;
            color = 0;

            parent = NULL;
            left = NULL;
            right = NULL;
        }
    };
    Node* root;
    Node* nil;
    Node* findParentNode(T1 newKey)
    {
        Node* cur = root; //current Node
        while (1)
        {
            if (*cur->key == newKey)
            {
                throw invalid_argument("this key already exists");
            }
            else
            {
                if (newKey < *cur->key)
                {
                    if (cur->left == nil)
                    {
                        return cur;
                    }
                    else
                    {
                        cur = cur->left;
                    }
                }
                else
                {
                    if (cur->right == nil)
                    {
                        return cur;
                    }
                    else
                    {
                        cur = cur->right;
                    }
                }
            }
        }
    }
    void leftTurn(Node* newNode)
    {
        Node* x = newNode;
        Node* y = newNode->right;
        x->right = y->left;
        if (y->left != nil)
        {
            y->left->parent = x;
        }
        if (x->parent == NULL)
        {
            root = y;
            root->parent = NULL;
        }
        else
        {
            if (x->parent->left == x)
            {
                y->parent = x->parent;
                x->parent->left = y;
            }
            else
            {
                y->parent = x->parent;
                x->parent->right = y;
            }
        }
        x->parent = y;
        y->left = x;
    }
    void rightTurn(Node* newNode)
    {
        Node* y = newNode;
        Node* x = newNode->left;
        y->left = x->right;
        if (x->right != nil)
        {
            x->right->parent = y;
        }
        if (y->parent == NULL)
        {
            root = x;
            root->parent = NULL;
        }
        else
        {
            if (y->parent->right == y)
            {
                x->parent = y->parent;
                y->parent->right = x;
            }
            else
            {
                x->parent = y->parent;
                y->parent->left = x;
            }
        }
        y->parent = x;
        x->right = y;
    }
    void fixRBTreeFromInsert(Node* newNode)
    {
        while (newNode->parent->color == 0)
        {
            Node* p = newNode->parent;
            Node* Gp = newNode->parent->parent;
            if (Gp->left == p)
            {
                if (Gp->right->color == 0)
                {
                    Gp->right->color = 1;
                    Gp->left->color = 1;
                    Gp->color = 0;
                    newNode = Gp;
                }
                else
                {
                    if (p->right == newNode)
                    {
                        newNode = p;
                        leftTurn(newNode);
                    }
                    else
                    {
                        p->color = 1;
                        Gp->color = 0;
                        rightTurn(Gp);
                    }
                }
            }
            else
            {
                if (Gp->left->color == 0)
                {
                    Gp->right->color = 1;
                    Gp->left->color = 1;
                    Gp->color = 0;
                    newNode = Gp;
                }
                else
                {
                    if (p->left == newNode)
                    {
                        newNode = p;
                        rightTurn(newNode);
                    }
                    else
                    {
                        p->color = 1;
                        Gp->color = 0;
                        leftTurn(Gp);
                    }
                }
            }
            if (newNode == root) break;
        }
        root->color = 1;
    }
    Node* minNode(Node* cur)
    {
        while (cur->left != nil)
        {
            cur = cur->left;
        }
        return cur;
    }
    void swap(Node* x, Node* y)
    {
        if (y->parent == NULL)
        {
            root = x;
        }
        else
        {
            if (y->parent->right == y)
            {
                y->parent->right = x;
            }
            else
            {
                y->parent->left = x;
            }
            x->parent = y->parent;
        }
    }
    void fixRBTreeFromRemove(Node* x)
    {
        while ((x != root) && (x->color == 1))
        {
            if (x->parent->left == x)
            {
                Node* w = x->parent->right;
                if (w->color == 0)
                {
                    w->color = 1;
                    x->parent->color = 0;
                    leftTurn(x->parent);
                    w = x->parent->right;
                }
                if ((w->left->color == 1) && (w->right->color == 1))
                {
                    w->color = 0;
                    x = x->parent;
                }
                else
                {
                    if (w->right->color == 1)
                    {
                        w->left->color = 1;
                        w->color = 0;
                        rightTurn(w);
                        w = x->parent->right;
                    }
                    else
                    {
                        w->color = x->parent->color;
                        x->parent->color = 1;
                        w->right->color = 1;
                        leftTurn(x->parent);
                        x = root;

                    }
                }
            }
            else
            {
                Node* w = x->parent->left;
                if (w->color == 0)
                {
                    w->color = 1;
                    x->parent->color = 0;
                    rightTurn(x->parent);
                    w = x->parent->left;
                }
                if ((w->left->color == 1) && (w->right->color == 1))
                {
                    w->color = 0;
                    x = x->parent;
                }
                else
                {
                    if (w->left->color == 1)
                    {
                        w->right->color = 1;
                        w->color = 0;
                        leftTurn(w);
                        w = x->parent->left;
                    }
                    else
                    {
                        w->color = x->parent->color;
                        x->parent->color = 1;
                        w->left->color = 1;
                        rightTurn(x->parent);
                        x = root;

                    }
                }
            }
        }
        root->parent = NULL;
        nil->parent = NULL;
    }
    class TreeIterator :public Iterator<Node*>
    {
    private:
        class Stack
        {
        private:
            class elem
            {
            public:
                Node* data;
                elem* next;
                elem(Node* new_data)
                {
                    data = new_data;
                    next = NULL;
                }
            };
            elem* head;
        public:
            Stack()
            {
                head = NULL;
            }
            void push(Node* data)
            {
                elem* tmp = new elem(data);
                elem* cur = head;
                head = tmp;
                head->next = cur;
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
            Node* top()
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
        };
        Node* cur; //current
        Node* iterator_nil;
        Stack* stack;
    public:
        TreeIterator(Node* start, Node* _nil)
        {
            cur = start;
            iterator_nil = _nil;
            stack = new Stack();
        }
        bool has_next() override
        {
            return cur != iterator_nil;
        }
        Node* next() override
        {
            if (!has_next())
            {
                throw out_of_range("No more elements");
            }
            Node* tmp = cur;
            if (cur->right != iterator_nil)
            {
                stack->push(cur->right);
            }
            if (cur->left != iterator_nil)
            {
                cur = cur->left;
            }
            else
            {
                try
                {
                    cur = stack->top();
                    stack->pop();
                }
                catch (out_of_range)
                {
                    cur = iterator_nil;
                }
            }
            return tmp;
        }
    };
    Iterator<Node*>* create_TreeIterator()
    {
        return new TreeIterator(root, nil);
    }
    Node* findNode(T1 key)
    {
        Node* cur = root; //current
        while (cur != nil)
        {
            if (*cur->key != key)
            {
                if (*cur->key < key)
                {
                    cur = cur->right;
                }
                else
                {
                    cur = cur->left;
                }
            }
            else
            {
                return cur;
            }
        }
        throw invalid_argument("this key does not exist");
    }
public:
    RBTree()
    {
        nil = new Node();
        nil->color = 1;
        root = nil;
    }
    void insert(T1 newKey, T2 newData)
    {
        if (root == nil)
        {
            root = new Node(newKey, newData);
            root->color = 1;
            root->left = nil;
            root->right = nil;
        }
        else
        {
            Node* parentForNewNode = findParentNode(newKey);
            Node* newNode = new Node(newKey, newData);
            if (newKey < *parentForNewNode->key)
            {
                parentForNewNode->left = newNode;
            }
            else
            {
                parentForNewNode->right = newNode;
            }
            newNode->parent = parentForNewNode;
            newNode->left = nil;
            newNode->right = nil;
            fixRBTreeFromInsert(newNode);
        }
    }
    T2 find(T1 key)
    {
        Node* cur = root; //current
        while (cur != nil)
        {
            if (*cur->key != key)
            {
                if (*cur->key < key)
                {
                    cur = cur->right;
                }
                else
                {
                    cur = cur->left;
                }
            }
            else
            {
                return cur->data;
            }
        }
        throw invalid_argument("this key does not exist");
    }
    void remove(T1 key)
    {
        Node* nodeToBeDeleted = findNode(key);
        bool originalColor = nodeToBeDeleted->color;
        Node* x;
        if (nodeToBeDeleted->left == nil)
        {
            x = nodeToBeDeleted->right;
            swap(x, nodeToBeDeleted);
        }
        else
        {
            if (nodeToBeDeleted->right == nil)
            {
                x = nodeToBeDeleted->left;
                swap(x, nodeToBeDeleted);
            }
            else
            {
                Node* y = minNode(nodeToBeDeleted->right);
                originalColor = y->color;
                x = y->right;
                if (y->parent == nodeToBeDeleted)
                {
                    x->parent = y;
                }
                else
                {
                    swap(x, y);
                    y->right = nodeToBeDeleted->right;
                    y->right->parent = y;
                }
                swap(y, nodeToBeDeleted);
                y->color = originalColor;
                y->left = nodeToBeDeleted->left;
                y->left->parent = y;
            }
        }
        delete nodeToBeDeleted;
        if (originalColor == 1)
        {
            fixRBTreeFromRemove(x);
        }
    }
    void print()
    {
        Node* forPrint;
        Iterator<Node*>* iterator = create_TreeIterator();
        cout << "\n\n";
        while (iterator->has_next())
        {
            forPrint = iterator->next();
            cout << "[key = " << *forPrint->key << ", data = " << forPrint->data << "]->";
        }
        cout << "XXX\n\n";
        delete iterator;
    }
    List<T1> get_keys()
    {
        List<T1> list;
        Node* forList;
        Iterator<Node*>* iterator = create_TreeIterator();
        cout << "\n\n";
        while (iterator->has_next())
        {
            forList = iterator->next();
            list.push_back(*forList->key);
        }
        delete iterator;
        return list;
    }
    List<T1> get_values()
    {
        List<T1> list;
        Node* forList;
        Iterator<Node*>* iterator = create_TreeIterator();
        cout << "\n\n";
        while (iterator->has_next())
        {
            forList = iterator->next();
            list.push_back(forList->data);
        }
        delete iterator;
        return list;
    }
    void clear()
    {
        Node* forClear;
        Iterator<Node*>* iterator = create_TreeIterator();
        cout << "\n\n";
        while (iterator->has_next())
        {
            forClear = iterator->next();
            delete forClear;
        }
        delete iterator;
    }
    bool NotEmpty()
    {
        return (root != nil);
    }
};


