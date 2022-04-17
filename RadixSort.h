//
// Created by Roland on 4/17/2022.
//

#include "RadixSort.h"

//https://stackoverflow.com/a/1505791
int pow(int x, unsigned int p){
    if (p == 0) return 1;
    if (p == 1) return x;

    int tmp = pow(x, p/2);
    if (p%2 == 0) return tmp * tmp;
    else return x * tmp * tmp;
}


void clearBuckets(std::vector<std::vector<int>>& bucket){
    for (auto& b: bucket){
        b.clear();
    }
}

std::vector<Piece> sort(std::vector<Piece>& list, int nBuckets){
    int max = INT_MIN;
    int min = INT_MAX;

    for (auto v: list){
        if (v < min){
            min = v;
        }
        if (v > max){
            max = v;
        }
    }

    std::vector<std::vector<int>> buckets(nBuckets); buckets[0] = list;
    std::vector<std::vector<int>> temp(nBuckets);

    for (int i = 0;; i++){
        int nPowI = pow(nBuckets, i);
        if (nPowI > max-min) break;

        for (auto& bucket: buckets){
            for (auto value: bucket){
                int index = (value - min) / nPowI % nBuckets;

                temp[index].push_back(value);
            }
        }
        buckets = temp;
        clearBuckets(temp);
    }

    std::vector<int> result;
    for (auto& b: buckets){
        for (auto v: b){
            result.push_back(v);
        }
    }
    return result;
}