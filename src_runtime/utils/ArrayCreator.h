#ifndef ARRAYCREATOR_H
#define ARRAYCREATOR_H

#include <stdlib.h>

template <typename T>
class ArrayCreator
{
public:


    T **createMatrix(int dim_1, int dim_2);
    T ***createTensor(int dim_1, int dim_2, int dim_3);
};

#include "ArrayCreator.h"


template <typename T> T** ArrayCreator<T>::createMatrix(int dim_1, int dim_2) {
    T** matrix;

    matrix = (T**) calloc(dim_1, sizeof(T*));
    for(int i = 0; i < dim_1; i++) {
        matrix[i] = (T*) calloc(dim_2, sizeof(T));
    }

    return matrix;
}



template <typename T> T*** ArrayCreator<T>::createTensor(int dim_1, int dim_2, int dim_3) {
    T*** tensor;
    tensor = (T***) malloc(dim_1*sizeof(T**));
    for(int i = 0; i < dim_1; i++) {
        tensor[i] = (T**) malloc(dim_2*sizeof(T*));
        for(int j = 0; j < dim_2; j++) {
            tensor[i][j] = (T*) malloc(dim_3*sizeof(T));
        }
    }

    return tensor;
}



#endif // ARRAYCREATOR_H
