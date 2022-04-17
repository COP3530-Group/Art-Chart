//
// Created by Roland on 4/17/2022.
//

#include "Piece.h"

//https://stackoverflow.com/a/1505791
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

std::vector<Piece> sort(std::vector<Piece>& list, int nBuckets){
    int max = INT_MIN;
    int min = INT_MAX;

    for (auto piece: list){
        if (piece < min){
            min = piece;
        }
        if (piece > max){
            max = piece;
        }
    }

    std::vector<std::vector<Piece>> buckets(nBuckets); buckets[0] = list;
    std::vector<std::vector<Piece>> temp(nBuckets);

    for (int i = 0;; i++){
        int nPowI = pow(nBuckets, i);
        if (nPowI > max-min) break;

        for (auto& bucket: buckets){
            for (auto& piece: bucket){
                int index = (piece.value - min) / nPowI % nBuckets;

                temp[index].push_back(piece);
            }
        }
        buckets = temp;
        clearBuckets(temp);
    }

    std::vector<Piece> result;
    for (auto& bucket: buckets){
        for (auto piece: bucket){
            result.push_back(piece);
        }
    }
    return result;
}