
#include <iostream>
#include "BestPrices.h"
using namespace std;

int main()
{
    Prices all;
    all.remember_list("text.txt");
    all.FormMatrix_fromFile();
    //all.printMatrix();
    all.print_price("Vladivostok", "Saint-P");
    all.print_price("Moscow", "Vladivostok");
    all.print_price("Saint-P", "Vladivostok");
    all.print_price("Moscow", "Moscow");
}