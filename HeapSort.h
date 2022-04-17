#ifndef ARTCHART_HEAPSORT_H
#define ARTCHART_HEAPSORT_H

#include <vector>
#include "Piece.h"

using namespace std;

void heapify_down_min(int i, vector<Piece>& collection)
{
    int parentIndex = i;
    int lChildIndex = 2*parentIndex + 1;
    int rChildIndex = 2*parentIndex + 2;

    while(lChildIndex < collection.size())
    {
        int lesserChildIndex;

        if(rChildIndex >= collection.size())
            lesserChildIndex = lChildIndex;
        else if(collection[lChildIndex].value < collection[rChildIndex].value)
            lesserChildIndex = lChildIndex;
        else
            lesserChildIndex = rChildIndex;

        if(collection[parentIndex].value > collection[lesserChildIndex].value)
        {
            auto swap = collection[lesserChildIndex];
            collection[lesserChildIndex] = collection[parentIndex];
            collection[parentIndex] = swap;

            //Setup next
            parentIndex = lesserChildIndex;
            lChildIndex = 2*parentIndex + 1;
            rChildIndex = 2*parentIndex + 2;
        }else
            return;
    }
}

void heapify_down_max(int i, vector<Piece>& collection)
{
    int parentIndex = i;
    int lChildIndex = 2*parentIndex + 1;
    int rChildIndex = 2*parentIndex + 2;

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

            //Setup next
            parentIndex = greaterChildIndex;
            lChildIndex = 2*parentIndex + 1;
            rChildIndex = 2*parentIndex + 2;
        } else
            return;
    }
}

std::vector<Piece> heap_sort(std::vector<Piece> gallery)
{
    //Heapify
    for (int i = gallery.size()/2; i >= 0; i--)
    {
        heapify_down_min(i, gallery);
    }

    //Extract
    vector<Piece> sortedGallery;

    int size = gallery.size();
    for(int i = 0; i < size; i++)
    {
        sortedGallery.push_back(gallery[0]);

        //Bring last element to front
        int lastIndex = gallery.size() - 1;
        gallery[0] = gallery[lastIndex];
        gallery.pop_back();

        heapify_down_min(0, gallery);
    }

    return sortedGallery;
}

#endif //ARTCHART_HEAPSORT_H
