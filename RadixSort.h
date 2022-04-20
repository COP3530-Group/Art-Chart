//
// Created by Roland on 4/17/2022.
//
#pragma once
#include <vector>
#include "Piece.h"

//Used from stack overflow, as the c++ standard library did not have an integer exponent function
//https://stackoverflow.com/a/1505791
int cpow(int x, unsigned int p){
    if (p == 0) return 1;
    if (p == 1) return x;

    int tmp = cpow(x, p/2);
    if (p%2 == 0) return tmp * tmp;
    else return x * tmp * tmp;
}


void clearBuckets(std::vector<std::vector<Piece>>& bucket){
    for (auto& b: bucket){
        b.clear();
    }
}

std::vector<Piece> radixSort(std::vector<Piece>& list, int nBuckets){
    int max = INT_MIN;
    int min = INT_MAX;

    //Grabs the min and max of the list
    //This is to both normalize the values to always be non-negative,
    //and to know the maximum number of digits any value in the list has
    for (auto v: list){
        if (v.value < min){
            min = v.value;
        }
        if (v.value > max){
            max = v.value;
        }
    }

    std::vector<std::vector<Piece>> buckets(nBuckets); buckets[0] = list;
    std::vector<std::vector<Piece>> temp(nBuckets);

    for (int i = 0;; i++){
        int nPowI = cpow(nBuckets, i);
        if (nPowI > max-min) break;

        for (auto& bucket: buckets){
            for (auto value: bucket){
                int index = (value.value - min) / nPowI % nBuckets;

                temp[index].push_back(value);
            }
        }
        
        //faster to swap them, than to reassign
        buckets.swap(temp);
        clearBuckets(temp);
    }

    //moves everything from the buckets to the resulting list
    std::vector<Piece> result;
    for (auto& b: buckets){
        for (auto v: b){
            result.push_back(v);
        }
    }
    return result;
}
