//
// Created by tirio on 4/18/2022.
//
#include <iostream>
#include <regex>
#include "Parser.h"
#include "RadixSort.h"
#include "HeapSort.h"

using namespace std;

int main()
{
    vector<Piece> gallery;

    for(int i = 0; i < 10; i++)
    {
        Piece p("","","","", 0);
        gallery.push_back(p);
    }

    string test = "Hello there is Chasse ";

    for(Piece& piece : gallery)
    {
        piece.print();
    }

    return 0;
}