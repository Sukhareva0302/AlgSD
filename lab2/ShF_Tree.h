#include <iostream>
#include "ShF_Map.h"
#include "ShF_List2.h"

using namespace std;

class Tree
{
private:
    class TreeNode //class of the element of the Tree
    {
    private:

    public:
        List2 data; //data in the node
        TreeNode* left; //pointer to the left node
        TreeNode* right; //pointer to the right node
        TreeNode(List2 intdata)
        {
            data = intdata; //the initialized data is set as the head
            left = NULL; //the left node is set as 'NULL', as there no next node
            right = NULL;//the right node is set as 'NULL', as there no next node
        }
    };
    //TreeNode* root;
    //Map<char, List<bool>> map;
public:
    Map<char, List<bool>> map;
    TreeNode* root;
	Tree()
	{
		root = NULL;
	}
    List2 sortSequence(List2 list)
    {
        int sequence_size = list.get_size();
        char* arrayForFixChar =new char[sequence_size];
        int* arrayForFixInt = new int[sequence_size];
        Node2* cur = list.get_head();
        for (int i = 0; i < sequence_size; i++)
        {
            arrayForFixChar[i] = cur->key;
            arrayForFixInt[i] = cur->data;
            cur = cur->next;
        }
        //QuickSort(arrayForFix, 0, sequence_size);
        for (int i = 0; i < sequence_size - 1; i++)
        {
            for (int j = 0; j < sequence_size - 1 - i; j++)
            {
                if (arrayForFixInt[j] > arrayForFixInt[j + 1])
                {
                    swap(arrayForFixInt[j], arrayForFixInt[j + 1]);
                    swap(arrayForFixChar[j], arrayForFixChar[j + 1]);
                }
            }
        }
        List2 list_new;
        for (int i = 0; i < sequence_size; i++)
        {
            list_new.push_front(arrayForFixChar[i], arrayForFixInt[i]);
        }
        return list_new;
    }
    List2 getSequence(string input)
    {
        List2 list; //sequence of symbols and periodicity
        for (int i = 0; i < input.length(); i++)
        {
            if (list.contains(input[i]))
            {
                list.increase_periodicity(input[i]);
            }
            else
            {
                list.push_back(input[i], 1);
            }
        }
        list = sortSequence(list);
        return list;
    }
    List2 fix_left(List2 old_list, char key)
    {
        List2 list;
        list.copy(old_list);
        Node2* cur = list.get_head();
        while (cur->key != key)
        {
            cur = cur->next;
        }
        while (cur->next != NULL)
        {
            list.pop_back();
        }
        return list;
    }
    List2 fix_right(List2 old_list, char key)
    {
        List2 right = fix_left(old_list, key);
        return right.reverse();
    }
    /*void set_root(List2 list)
    {
        TreeNode* newNode = new TreeNode(list);
        root = newNode;
    }
    void set_left(TreeNode* cur, List2 list)
    {
        TreeNode* newNode = new TreeNode(list);
        cur->left = newNode;
    }
    void set_right(TreeNode* cur, List2 list)
    {
        TreeNode* newNode = new TreeNode(list);
        cur->right = newNode;
    }*/
    void create_tree(TreeNode* cur, List2 list, List<bool> code)
    {
        cur = new TreeNode(list);
        /*if (root == NULL)
        {
            set_root(list);
        }*/
        if (list.get_size() > 1)
        {
            List2 left_list = list;
            List2 right_list = list.reverse();
            Node2* left = left_list.get_head();
            Node2* right = right_list.get_head();
            int left_counter = left->data;
            int right_counter = right->data;
            while (right->next->key != left->key)
            {
                while ((right_counter < left_counter) && (right->next->key != left->key))
                {
                    right = right->next;
                    right_counter = right_counter + right->data;
                }
                if (right->next->key != left->key)
                {
                    left = left->next;
                    left_counter = left_counter + left->data;
                }
            }
            List<bool> code_left;
            code_left.copy(code);
            code_left.push_back(true);
            left_list = fix_left(left_list, left->key);
            //set_left(cur, left_list);
            create_tree(cur->left, left_list, code_left);

            List<bool> code_right;
            code_right.copy(code);
            code_right.push_back(false);
            right_list = fix_right(right_list, right->key);
            //set_right(cur, right_list);
            create_tree(cur->right, right_list, code_right);
        }
        else
        {
            map.insert(list.return_char_one(), code);
        }
        //root = cur;
    }
    List<List<bool>> create_code(string input)
    {
        List<List<bool>> list;
        for (int i = 0; i < input.length(); i++)
        {
            list.push_back(map.find(input[i]));
        }
        return list;
    }
    void print_code(List<List<bool>> list)
    {
        for (int i = 0; i < list.get_size(); i++)
        {
            list.at(i).printList();
        }
    }
    int get_code_size(List<List<bool>> list)
    {
        int sum_size=0;
        for (int i = 0; i < list.get_size(); i++)
        {
            sum_size=sum_size+list.at(i).get_size();
        }
        return sum_size;
    }
    char decode_one_char(List<bool> list)
    {
        List<char> keys = map.get_keys();
        List< List<bool>> values = map.get_values();
        for (int i = 0; i < values.get_size(); i++)
        {
            if (list.equal(values.at(i)))
            {
                return keys.at(i);
            }
        }
    }
    string decode(List<List<bool>> list)
    {
        //List <List<bool>> list;
        string rez = "";
        //List<bool> list2;
        //list.copy(code);
        for (int i = 0; i < list.get_size(); i++)
        {
            //list2.copy(list.at(i));
            rez = rez + decode_one_char(list.at(i));
            //rez = rez + map.find_letter(list.at(i));
        }
        return rez;
    }
};