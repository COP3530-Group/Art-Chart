//
// Created by Roland on 4/17/2022.
//

#ifndef ART_CHART_DISTANCETO_H
#define ART_CHART_DISTANCETO_H

#pragma once
#include <vector>
#include "Piece.h"

int binarySearch(Piece piece, std::vector<Piece> list, int min, int max){
    if (min > max){
        return min;
    }

    int mid = min + (max - min) / 2;

    if (list[mid].value == piece.value) return mid;

    if (list[mid].value > piece.value) return binarySearch(piece, list, min, mid-1);

    return binarySearch(piece, list, mid+1, max);
}

int dist(int a, int b){
    if (a > b) return a-b;

    return b-a;
}

std::vector<Piece> sortByRelevance(Piece piece, std::vector<Piece>& list){
    int index = binarySearch(piece, list, 0, list.size());

    int left = index-1;
    int right = index+1;

    std::vector<Piece> result; result.push_back(list[index]);

    while (true){
        bool canLeft = left >= 0;
        bool canRight = right < (int)list.size();

        if (canLeft && canRight){
            int lDist = dist(list[left].value, piece.value);
            int rDist = dist(list[right].value, piece.value);

            if (lDist < rDist){
                result.push_back(list[left]);
                left--;
            }
            else {
                result.push_back(list[right]);
                right++;
            }
        }
        else if (canLeft) {
            result.push_back(list[left]);
            left--;
        }
        else if (canRight){
            result.push_back(list[right]);
            right++;
        }
        else {
            break;
        }
    }

    return result;
}

#endif //ART_CHART_DISTANCETO_H
