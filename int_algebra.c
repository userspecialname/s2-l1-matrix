#include <stdio.h>
#include <stdlib.h>
#include "int_algebra.h"
#include "matrix.h"


// МЕТОДЫ INT RING


void IntSum(const void* x, const void* y, void* res) {
    *(int*)res = *(const int*)x + *(const int*)y;
}

void IntMult(const void* x, const void* y, void* res) {
    *(int*)res = *(const int*)x * *(const int*)y;
}

void IntZero(void *x) {
    *(int *) x = 0;
}


void IntOutput(Matrix *this) {
    int n = this->size_matrix;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%8d ", *(int *) (this->data + (i * n + j) * this->ring->size));
        }
        printf("\n");
    }
    printf("\n");
}

// МЕТОДЫ INT RING

// МЕТОДЫ DOUBLE RING

void DoubleSum(const void *x, const void *y, void *res) {
    *(double *) res = *(double *) x + *(double *) y;
}

void DoubleMult(const void *x, const void *y, void *res) {
    *(double *) res = (*(double *) x) * (*(double *) y);
}

void DoubleZero(void *x) {
    *(double *) x = 0.0;
}

void IntInput(Matrix *this) {
    int n = this->size_matrix;
    this->data = calloc(n * n, this->ring->size);
    for (int i = 0; i < n * n; i++) {
        printf("I[%d][%d]: ", i / n + 1, i % n + 1);
        *((int *)(this->data + i * this->ring->size)) = input_integer();
    }
}

void DoubleInput(Matrix *this) {
    int n = this->size_matrix;
    this->data = calloc(n * n, this->ring->size);
    for (int i = 0; i < n * n; i++) {
        printf("R[%d][%d]: ", i / n + 1, i % n + 1);
        *((double *)(this->data + i * this->ring->size)) = input_double();
    }
}

void ComplexInput(Matrix *this) {
    int n = this->size_matrix;
    this->data = calloc(n * n, this->ring->size);
    for (int i = 0; i < n * n; i++) {
        printf("Z[%d][%d]: ", i / n + 1, i % n + 1);
        *((ComplexNumber *)(this->data + i * this->ring->size)) = input_complex();
    }
}
void DoubleOutput(Matrix *this) {
    int n = this->size_matrix;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%5lf ", *(double *) (this->data + (i * n + j) * this->ring->size));
        }
        printf("\n");
    }
    printf("\n");
}

// МЕТОДЫ DOUBLE RING

// МЕТОДЫ COMPLEX RING

void ComplexSum(const void *x, const void *y, void *res) {
    ((ComplexNumber *) res)->Re = ((ComplexNumber *) x)->Re + ((ComplexNumber *) y)->Re;
    ((ComplexNumber *) res)->Im = ((ComplexNumber *) x)->Im + ((ComplexNumber *) y)->Im;
}

void ComplexZero(void *x) {
    ((ComplexNumber *) x)->Re = 0.0;
    ((ComplexNumber *) x)->Im = 0.0;
}

void ComplexMult(const void *x, const void *y, void *res) {
    ((ComplexNumber *) res)->Re = ((ComplexNumber *) x)->Re * ((ComplexNumber *) y)->Re -
                                  ((ComplexNumber *) x)->Im * ((ComplexNumber *) y)->Im;
    ((ComplexNumber *) res)->Im = ((ComplexNumber *) x)->Re * ((ComplexNumber *) y)->Im +
                                  ((ComplexNumber *) x)->Im * ((ComplexNumber *) y)->Re;
}


void ComplexOutput(Matrix *this) {
    int n = this->size_matrix;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            output_complex(*(ComplexNumber *) (this->data + (i * n + j) * this->ring->size));
        }
        printf("\n");
    }
    printf("\n");
}




RingInfo* GetIntRingInfo() {
    return InitRingInfo(
        sizeof(int),
        IntSum,
        IntMult,
        IntZero,
        IntInput,
        IntOutput
    );
}

RingInfo* GetDoubleRingInfo() {
    return InitRingInfo(
        sizeof(double),
        DoubleSum,
        DoubleMult,
        DoubleZero,
        DoubleInput,
        DoubleOutput
    );
}

RingInfo* GetComplexRingInfo() {
    return InitRingInfo(
        sizeof(ComplexNumber),
        ComplexSum,
        ComplexMult,
        ComplexZero,
        ComplexInput,
        ComplexOutput
    );
}
