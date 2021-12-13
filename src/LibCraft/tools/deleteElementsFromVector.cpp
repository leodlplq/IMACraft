//
// Created by Léo on 13/12/2021.
//

#include "./include/deleteElementsFromVector.hpp"

using namespace std;

template <typename T>
void deleteElementsFromVector(vector<T> &v){
    v.erase(v.begin(), v.end());
    v.shrink_to_fit();
}

