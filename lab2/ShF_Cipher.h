#pragma once

#include <iostream>
#include "ShF_Tree.h"
using namespace std;

class ShF_Cipher
{
private:
    int start_size;
    Tree tree;
    List2 periodicity;
    List<bool> code_for_char;
    List<List<bool>> code;
public:
    ShF_Cipher(string input)
    {
        start_size = input.length()*8;
        periodicity = tree.getSequence(input);
        tree.create_tree(tree.root, periodicity, code_for_char);
        code = tree.create_code(input);
    }
    void printPeriodicity()
    {
        cout << "\n\nPeriodicity:\n";
        periodicity.printList2();
    }
    void printCodeForChar()
    {
        cout << "\n\nCode for each symbol:\n";
        tree.map.print();
    }
    void printSize()
    {
        cout << "\n\nBefore: " << start_size << "\n";
        cout << "\n\nAfter: " << tree.get_code_size(code) << "\n";
    }
    void printCode()
    {
        cout << "\n\nCoded message:\n";
        tree.print_code(code);
    }
    void printDecode()
    {
        cout << "\n\nDecoded message:\n";
        cout<<tree.decode(code);
    }
    void printCoefficient()
    {
        cout << "\n\nCompression ratio: " << ((start_size*1.0) / (tree.get_code_size(code)*1.0)) * 100 << "%\n";
    }
};