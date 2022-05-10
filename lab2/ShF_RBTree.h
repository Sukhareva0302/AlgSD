#include <iostream>
#include "ShF_List.h"
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
    class RBTreeNode {
    private:
        T1* key; //key for RBTreeNode
        T2 data; //data in the RBTreeNode
        bool color; //0 - Red, 1 - Black

        RBTreeNode* parent; //pointer to the parent RBTreeNode
        RBTreeNode* left; //pointer to the left RBTreeNode
        RBTreeNode* right;//pointer to the right RBTreeNode
    public:
        friend class RBTree;
        RBTreeNode(T1 newKey, T2 newData)
        {
            key = new T1;
            *key = newKey;
            data = newData;
            color = 0;

            parent = NULL;
            left = NULL;
            right = NULL;
        }
        RBTreeNode()
        {
            key = NULL;
            //data = 0;
            color = 0;

            parent = NULL;
            left = NULL;
            right = NULL;
        }
    };
    RBTreeNode* root;
    RBTreeNode* nil;
    RBTreeNode* findParentRBTreeNode(T1 newKey)
    {
        RBTreeNode* cur = root; //current RBTreeNode
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
    void leftTurn(RBTreeNode* newRBTreeNode)
    {
        RBTreeNode* x = newRBTreeNode;
        RBTreeNode* y = newRBTreeNode->right;
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
    void rightTurn(RBTreeNode* newRBTreeNode)
    {
        RBTreeNode* y = newRBTreeNode;
        RBTreeNode* x = newRBTreeNode->left;
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
    void fixRBTreeFromInsert(RBTreeNode* newRBTreeNode)
    {
        while (newRBTreeNode->parent->color == 0)
        {
            RBTreeNode* p = newRBTreeNode->parent;
            RBTreeNode* Gp = newRBTreeNode->parent->parent;
            if (Gp->left == p)
            {
                if (Gp->right->color == 0)
                {
                    Gp->right->color = 1;
                    Gp->left->color = 1;
                    Gp->color = 0;
                    newRBTreeNode = Gp;
                }
                else
                {
                    if (p->right == newRBTreeNode)
                    {
                        newRBTreeNode = p;
                        leftTurn(newRBTreeNode);
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
                    newRBTreeNode = Gp;
                }
                else
                {
                    if (p->left == newRBTreeNode)
                    {
                        newRBTreeNode = p;
                        rightTurn(newRBTreeNode);
                    }
                    else
                    {
                        p->color = 1;
                        Gp->color = 0;
                        leftTurn(Gp);
                    }
                }
            }
            if (newRBTreeNode == root) break;
        }
        root->color = 1;
    }
    RBTreeNode* minRBTreeNode(RBTreeNode* cur)
    {
        while (cur->left != nil)
        {
            cur = cur->left;
        }
        return cur;
    }
    void swap(RBTreeNode* x, RBTreeNode* y)
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
    void fixRBTreeFromRemove(RBTreeNode* x)
    {
        while ((x != root) && (x->color == 1))
        {
            if (x->parent->left == x)
            {
                RBTreeNode* w = x->parent->right;
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
                RBTreeNode* w = x->parent->left;
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
    class TreeIterator :public Iterator<RBTreeNode*>
    {
    private:
        class Stack
        {
        private:
            class elem
            {
            public:
                RBTreeNode* data;
                elem* next;
                elem(RBTreeNode* new_data)
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
            void push(RBTreeNode* data)
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
            RBTreeNode* top()
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
        RBTreeNode* cur; //current
        RBTreeNode* iterator_nil;
        Stack* stack;
    public:
        TreeIterator(RBTreeNode* start, RBTreeNode* _nil)
        {
            cur = start;
            iterator_nil = _nil;
            stack = new Stack();
        }
        bool has_next() override
        {
            return cur != iterator_nil;
        }
        RBTreeNode* next() override
        {
            if (!has_next())
            {
                throw out_of_range("No more elements");
            }
            RBTreeNode* tmp = cur;
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
    Iterator<RBTreeNode*>* create_TreeIterator()
    {
        return new TreeIterator(root, nil);
    }
    RBTreeNode* findRBTreeNode(T1 key)
    {
        RBTreeNode* cur = root; //current
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
        nil = new RBTreeNode();
        nil->color = 1;
        root = nil;
    }
    void insert(T1 newKey, T2 newData)
    {
        if (root == nil)
        {
            root = new RBTreeNode(newKey, newData);
            root->color = 1;
            root->left = nil;
            root->right = nil;
        }
        else
        {
            RBTreeNode* parentForNewRBTreeNode = findParentRBTreeNode(newKey);
            RBTreeNode* newRBTreeNode = new RBTreeNode(newKey, newData);
            if (newKey < *parentForNewRBTreeNode->key)
            {
                parentForNewRBTreeNode->left = newRBTreeNode;
            }
            else
            {
                parentForNewRBTreeNode->right = newRBTreeNode;
            }
            newRBTreeNode->parent = parentForNewRBTreeNode;
            newRBTreeNode->left = nil;
            newRBTreeNode->right = nil;
            fixRBTreeFromInsert(newRBTreeNode);
        }
    }
    T2 find(T1 key)
    {
        RBTreeNode* cur = root; //current
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
        RBTreeNode* RBTreeNodeToBeDeleted = findRBTreeNode(key);
        bool originalColor = RBTreeNodeToBeDeleted->color;
        RBTreeNode* x;
        if (RBTreeNodeToBeDeleted->left == nil)
        {
            x = RBTreeNodeToBeDeleted->right;
            swap(x, RBTreeNodeToBeDeleted);
        }
        else
        {
            if (RBTreeNodeToBeDeleted->right == nil)
            {
                x = RBTreeNodeToBeDeleted->left;
                swap(x, RBTreeNodeToBeDeleted);
            }
            else
            {
                RBTreeNode* y = minRBTreeNode(RBTreeNodeToBeDeleted->right);
                originalColor = y->color;
                x = y->right;
                if (y->parent == RBTreeNodeToBeDeleted)
                {
                    x->parent = y;
                }
                else
                {
                    swap(x, y);
                    y->right = RBTreeNodeToBeDeleted->right;
                    y->right->parent = y;
                }
                swap(y, RBTreeNodeToBeDeleted);
                y->color = originalColor;
                y->left = RBTreeNodeToBeDeleted->left;
                y->left->parent = y;
            }
        }
        delete RBTreeNodeToBeDeleted;
        if (originalColor == 1)
        {
            fixRBTreeFromRemove(x);
        }
    }
    void print()
    {
        RBTreeNode* forPrint;
        Iterator<RBTreeNode*>* iterator = create_TreeIterator();
        cout << "\n\n";
        while (iterator->has_next())
        {
            forPrint = iterator->next();
            //cout << "[key = " << *forPrint->key << ", data = " << forPrint->data << "]->";
            cout << "[key = " << *forPrint->key << ", data = "; forPrint->data.printList(); cout << "]->";
        }
        cout << "XXX\n\n";
        delete iterator;
    }
    List<T1> get_keys()
    {
        List<T1> list;
        RBTreeNode* forList;
        Iterator<RBTreeNode*>* iterator = create_TreeIterator();
        //cout << "\n\n";
        while (iterator->has_next())
        {
            forList = iterator->next();
            list.push_back(*forList->key);
        }
        delete iterator;
        return list;
    }
    List<T2> get_values()
    {
        List<T2> list;
        RBTreeNode* forList;
        Iterator<RBTreeNode*>* iterator = create_TreeIterator();
        //cout << "\n\n";
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
        RBTreeNode* forClear;
        Iterator<RBTreeNode*>* iterator = create_TreeIterator();
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
    /*T1 find_letter(List<bool> list)
    {
        RBTreeNode* tree_cur = root;
        Node<bool>* cur = list.get_head();
        while (cur != NULL)
        {
            if (cur->data)
            {
                tree_cur = tree_cur->left;
            }
            else
            {
                tree_cur = tree_cur->right;
            }
            cur = cur->next;
        }
        return *tree_cur->key;
    }*/
};


