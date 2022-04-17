#ifndef ARTCHART_HEAPSORT_H
#define ARTCHART_HEAPSORT_H

#include <bits/stdc++.h>
#include "Piece.h"

using namespace std;

void heapify_down(int i, std::vector<Piece>& collection)
{
    int parentIndex = i;
    int lChildIndex = 2*i + 1;
    int rChildIndex = 2*i + 2;

    while(lChildIndex < collection.size())
    {
        int greaterChildIndex;

        if(rChildIndex >= collection.size())
            greaterChildIndex = lChildIndex;
        else if(collection[lChildIndex].value > collection[rChildIndex].value)
            greaterChildIndex = lChildIndex;
        else
            greaterChildIndex = rChildIndex;

        if(collection[parentIndex].value < collection[greaterChildIndex].value)
        {
            auto swap = collection[greaterChildIndex];
            collection[greaterChildIndex] = collection[parentIndex];
            collection[parentIndex] = swap;

            //Recalculate
            parentIndex = greaterChildIndex;
            lChildIndex = 2*i + 1;
            rChildIndex = 2*i + 2;
        }
        else
            return;
    }
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

    vector<Piece> sortedGallery(gallery.size());

    for(int i = 0; i < gallery.size(); i++)
    {
        sortedGallery.push_back(gallery[0]);

        //Bring last element to front
        int lastIndex = gallery.size() - 1;
        gallery[0] = gallery[lastIndex];
        gallery.pop_back();

        heapify_down(0, gallery);
    }

    return sortedGallery;
}

#endif //ARTCHART_HEAPSORT_H

