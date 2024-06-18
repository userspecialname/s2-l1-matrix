#include <stdio.h>
#include "matrix.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"


#define TEST_SIZE 3


void SumOfMatrix(const Matrix *s1, const Matrix *s2, Matrix *res) {
    if (s1->ring != s2->ring || s1->ring != res->ring) {
        printf("Error: matrices have different ring types\n");
        return;
    }

    int n = res->size_matrix;
    if (s1->size_matrix != n || s2->size_matrix != n) {
        printf("Error: matrices have different sizes\n");
        return;
    }

    if (res->data != NULL) {
        CleanMemory(res);
    }
    res->data = calloc(n * n, res->ring->size);
    if (!res->data) {
        printf("Error: failed to allocate memory for result matrix\n");
        return;
    }

    for (int i = 0; i < n * n; i++) {
        res->ring->sum((char *)s1->data + i * s1->ring->size,
                       (char *)s2->data + i * s2->ring->size,
                       (char *)res->data + i * res->ring->size);
    }
}

void MultiplicationOfMatrix(const Matrix *s1, const Matrix *s2, Matrix *res) {
    if (s1->ring != s2->ring || s1->ring != res->ring) {
        printf("Error: matrices have different ring types\n");
        return;
    }

    int n = res->size_matrix;
    if (s1->size_matrix != n || s2->size_matrix != n) {
        printf("Error: matrices have different sizes\n");
        return;
    }

    if (res->data != NULL) {
        CleanMemory(res);
    }
    res->data = calloc(n * n, res->ring->size);
    if (!res->data) {
        printf("Error: failed to allocate memory for result matrix\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res->ring->zero(res->data + (i * n + j) * res->ring->size);
            for (int k = 0; k < n; k++) {
                void *temp = calloc(1, res->ring->size);
                if (!temp) {
                    printf("Error: failed to allocate memory for temporary storage\n");
                    CleanMemory(res);
                    return;
                }
                res->ring->mult(s1->data + (i * n + k) * s1->ring->size, s2->data + (k * n + j) * res->ring->size, temp);
                res->ring->sum(res->data + (i * n + j) * res->ring->size, temp, res->data + (i * n + j) * res->ring->size);
                free(temp);
            }
        }
    }
}
 //Произведение матриц

void AddLinearCombination(Matrix *this, int A, int B, const void *scalar) {
    int n = this->size_matrix;
    if (A < 1 || A > n || B < 1 || B > n) {
        printf("Error: invalid row indices\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        void *temp = calloc(1, this->ring->size);
        if (!temp) {
            printf("Error: failed to allocate memory for temporary storage\n");
            return;
        }
        this->ring->zero(temp);
        this->ring->mult(scalar, this->data + ((A - 1) * n + i) * this->ring->size, temp);
        this->ring->sum(this->data + ((B - 1) * n + i) * this->ring->size, temp, this->data + ((B - 1) * n + i) * this->ring->size);
        free(temp);
    }

} //Добавление линейной комбинации строки к другой строке

void OutputMatrix(const Matrix *this) {
    this->ring->output(this);
} //Вывод матрицы

void InputMatrix(Matrix *this) {
    if (this->data != NULL) {
        CleanMemory(this);
    }
    this->ring->input(this);
} //Ввод матрицы

Matrix *InitMatrix(int size, const RingInfo *ring) {
    Matrix *this = (Matrix *)calloc(1, sizeof(struct Matrix));
    this->data = NULL;
    this->size_matrix = size;
    this->ring = ring;
    return this;
} //Иницилизация матрицы размером n*n

void CleanMemory(Matrix *this) {
    free(this->data);
    this->data = NULL;
} //Ручной сборщик мусора



void TestSum(const Matrix *s1, const Matrix *s2, const Matrix *expected, const RingInfo *ring) {
    Matrix *res = InitMatrix(s1->size_matrix, ring);
    SumOfMatrix(s1, s2, res);
    for (int i = 0; i < s1->size_matrix * s1->size_matrix; i++) {
        void *s1_elem = s1->data + i * s1->ring->size;
        void *s2_elem = s2->data + i * s2->ring->size;
        void *res_elem = res->data + i * res->ring->size;
        void *expected_elem = expected->data + i * expected->ring->size;
        assert(memcmp(res_elem, expected_elem, res->ring->size) == 0);
    }
    CleanMemory(res);
    free(res);
}

void TestMult(const Matrix *s1, const Matrix *s2, const Matrix *expected, const RingInfo *ring) {
    Matrix *res = InitMatrix(s1->size_matrix, ring);
    MultiplicationOfMatrix(s1, s2, res);
    for (int i = 0; i < s1->size_matrix * s1->size_matrix; i++) {
        void *res_elem = res->data + i * res->ring->size;
        void *expected_elem = expected->data + i * expected->ring->size;
        assert(memcmp(res_elem, expected_elem, res->ring->size) == 0);
    }
    CleanMemory(res);
    free(res);
}


