#include <iostream>
#include "TownList.h"
using namespace std;

class Prices
{
private:
    int** A; //matrix
    int n; //size of matrix
    int** formMatrix()
    {
        n = townList.get_size();
        Node* cur = townList.get_head();
        int** A = new int* [n];
        for (int count = 0; count < n; count++)
            A[count] = new int[n];
        int size_des;
        Destanation des;
        int index;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                A[i][j] = -1;
            }
        }
        for (int i = 0; i < n; i++)
        {
            size_des = cur->list.get_size();
            for (int j = 0; j < size_des; j++)
            {
                des = cur->list.at(j);
                index = townList.get_index(des.name);
                A[i][index] = des.to;
                A[index][i] = des.from;
            }
            cur = cur->next;
        }
        for (int i = 0; i < n; i++)
        {
            A[i][i] = 0;
        }
        //printMatrix(A, n);
        return A;
    }
    TownList form_TownList_from_file(string file_name)
    {
        TownList listT;
        string str;
        string town_from;
        string town_to;
        int to;
        string sub_str;
        int from;
        int pos;
        fstream file;
        file.open(file_name, ios::in);
        while (!file.eof())
        {
            getline(file, str);
            pos = str.find(";");
            town_from = str.substr(0, pos);
            str.erase(0, (pos + 1));
            pos = str.find(";");
            town_to = str.substr(0, pos);
            str.erase(0, (pos + 1));
            pos = str.find(";");
            sub_str = str.substr(0, pos);
            str.erase(0, (pos + 1));
            if (sub_str != "N/A")
            {
                to = stoi(sub_str);
            }
            else
            {
                to = -1;
            }
            if (str != "N/A")
            {
                from = stoi(str);
            }
            else
            {
                from = -1;
            }
            if (!listT.contains(town_from))
            {
                listT.push_back(town_from, town_to, to, from);
            }
            else
            {
                listT.update_destanation(town_from, town_to, to, from);
            }
            if (!listT.contains(town_to))
            {
                listT.push_name_only(town_to);
            }
        }
        file.close();
        return listT;
    }
public:
    TownList townList;
    Prices()
    {
        n = -1;
    }
    void remember_list(string file_name)
    {
        townList = form_TownList_from_file(file_name);
    }
    void FormMatrix_fromFile()
    {

        A = formMatrix();
        for (int k=0; k<n; k++)
            for(int i=0; i<n; i++)
                for (int j = 0; j < n; j++)
                {
                    if (A[i][j] == -1)
                    {
                        if ((A[i][k] != -1) && (A[k][j] != -1))
                        {
                            A[i][j] = A[i][k] + A[k][j];
                        }
                        else
                        {
                            A[i][j] = A[i][j];
                        }
                    }
                    else
                    {
                        if ((A[i][j] > A[i][k] + A[k][j])&& ((A[i][k] != -1) && (A[k][j] != -1)))
                        {
                            A[i][j] = A[i][k] + A[k][j];
                        }
                        else
                        {
                            A[i][j] = A[i][j];
                        }
                    }
                }
    }
    int get_price(string from, string to)
    {
        int index_from = townList.get_index(from);
        int index_to = townList.get_index(to);
        return A[index_from][index_to];
    }
    void print_price(string from, string to)
    {
        int price = get_price(from, to);
        if (price == 0)
        {
            cout << "You already here\n";
        }
        else
        {
            if (price == -1)
            {
                cout << "No way to destanation\n";
            }
            else
            {
                cout << "Best price from "<<from<<" to "<<to<<" is: " << price << "\n";
            }
        }
    }
    void printMatrix()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << A[i][j] << " ";
            }
            cout << "\n";
        }
    }
};