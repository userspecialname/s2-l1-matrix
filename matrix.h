#ifndef LNLAB1_MATRIX_H
#define LNLAB1_MATRIX_H

#include "ringinfo.h"
#include "complex.h"

typedef struct Matrix Matrix;
typedef struct complex_number ComplexNumber;
typedef struct RingInfo RingInfo;

struct Matrix {
    int size_matrix;
    void *data;
    const RingInfo *ring;
};

void SumOfMatrix(const Matrix *s1, const Matrix *s2, Matrix *res);
void MultiplicationOfMatrix(const Matrix *s1, const Matrix *s2, Matrix *res);
void AddLinearCombination(Matrix *this, int A, int B, const void *scalar);
void OutputMatrix(const Matrix *this);
void InputMatrix(Matrix *this);
Matrix *InitMatrix(int size, const RingInfo *ring);
void CleanMemory(Matrix *this);





#endif //LNLAB1_MATRIX_H
