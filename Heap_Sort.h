// Sorting alg 1 - Heap Sort?
#pragma once
#include "Piece.h"
#include <vector>
#include <iostream> // testing

/*
	Sorts each piece by its hashed ID
	Will make an operator to just compare each thing if you dont want to do piece.id
*/
#include <bits/stdc++.h>

using namespace std;

bool heapify_down(int i, std::vector<Piece>& collection)
{
    bool swapped = false;

    int lChildIndex = 2*i + 1;
    int rChildIndex = 2*i + 2;

    while(lChildIndex < collection.size())
    {
        int greaterIndex = 0;

        if(rChildIndex >= collection.size())
            greaterIndex = lChildIndex;
        else if(collection[lChildIndex].value > collection[rChildIndex].value)
            greaterIndex = lChildIndex;
        else
            greaterIndex = rChildIndex;

        if(collection[i].value < collection[greaterIndex].value)
        {
            swapped = true;
            auto temp = collection[greaterIndex];
            collection[greaterIndex] = collection[i];
            collection[i] = temp;

            i = greaterIndex;
            lChildIndex = 2*i + 1;
            rChildIndex = 2*i + 2;
        }
        else
            return swapped;
    }

    return swapped;
}

std::vector<Piece> heap_sort(std::vector<Piece> gallery)
{
    for (int i = 0; i < gallery.size() / 2; i++)
    {
        heapify_down(0, gallery);
    }

    //Swap all nodes with top value
    for(int i = gallery.size() - 1; i > 0; i--)
    {
        auto temp = gallery[0];
        gallery[0] = gallery[i];
        gallery[i] = temp;

        heapify_down(0, gallery);
    }


    for(auto num : gallery)
    {
        num.print();
    }

	return gallery;
}

