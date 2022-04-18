#pragma once
#include <vector>
#include "Piece.h"

int pow(int x, unsigned int p){
    if (p == 0) return 1;
    if (p == 1) return x;

    int tmp = pow(x, p/2);
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

    for (auto v: list){
        if (v.value < min){
            min = v.value;
        }
        if (v.value > max){
            max = v.value;
        }
    }

    std::vector<std::vector<Piece>> buckets(nBuckets); 
    buckets[0] = list;
    std::vector<std::vector<Piece>> temp(nBuckets);

    for (int i = 0;; i++){
        int nPowI = pow(nBuckets, i);
        if (nPowI > max-min) break;

        for (auto& bucket: buckets){
            for (auto value: bucket){
                int index = (value.value - min) / nPowI % nBuckets;

                temp[index].push_back(value);
            }
        }
        buckets = temp;
        clearBuckets(temp);
    }

    std::vector<Piece> result;
    for (auto& b: buckets){
        for (auto v: b){
            result.push_back(v);
        }
    }
    return result;
}