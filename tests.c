#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "tests.h"
#include "matrix.h"
#include "int_algebra.h"
#include "complex.h"
#include "math.h"


Matrix *m0() {
    Matrix *result = InitMatrix(1, GetIntRingInfo());
    result->data = malloc(sizeof(int));
    *(int*)(result->data) = 0;
    return result;
}

Matrix *m100500() {
    Matrix *result = InitMatrix(1, GetIntRingInfo());
    result->data = malloc(sizeof(int));
    *(int*)(result->data) = 100500;
    return result;
}

void freeMatrix(Matrix *m) {
    free(m->data);
    free(m);
}

void tezzt() {
    Matrix *a = m0();
    Matrix *b = m0();
    Matrix *res = m100500();

    printf("a: "); OutputMatrix(a);
    printf("b: "); OutputMatrix(b);
    printf("result: "); OutputMatrix(res);

    assert(*(int*)(res->data) == 100500);

    SumOfMatrix(a, b, res);

    printf("After SumOfMatrix:\n");
    printf("result: "); OutputMatrix(res);

    assert(*(int*)(res->data) == 0);

    freeMatrix(a);
    freeMatrix(b);
    freeMatrix(res);
}


void TestSum(const Matrix *s1, const Matrix *s2, const Matrix *expected, const RingInfo *ring);
void TestMult(const Matrix *s1, const Matrix *s2, const Matrix *expected, const RingInfo *ring);


void RunAllTests() {
    TestIntMatrix();
    TestDoubleMatrix();
    TestComplexMatrix();
    printf("All tests passed.\n");
}

void TestIntMatrix() {
    RingInfo* intRing = GetIntRingInfo();
    
    Matrix *matrix1 = InitMatrix(2, intRing);
    Matrix *matrix2 = InitMatrix(2, intRing);
    Matrix *resultMatrix = InitMatrix(2, intRing);
    
    int data1[] = {1, 2, 3, 4};
    int data2[] = {5, 6, 7, 8};
    
    matrix1->data = malloc(sizeof(data1));
    matrix2->data = malloc(sizeof(data2));
    
    memcpy(matrix1->data, data1, sizeof(data1));
    memcpy(matrix2->data, data2, sizeof(data2));
    
    // Test SumOfMatrix
    SumOfMatrix(matrix1, matrix2, resultMatrix);
    int expectedSum[] = {6, 8, 10, 12};
    for (int i = 0; i < 4; i++) {
        assert(((int*)resultMatrix->data)[i] == expectedSum[i]);
    }
    
    // Test MultiplicationOfMatrix
    MultiplicationOfMatrix(matrix1, matrix2, resultMatrix);
    int expectedMult[] = {19, 22, 43, 50};
    for (int i = 0; i < 4; i++) {
        assert(((int*)resultMatrix->data)[i] == expectedMult[i]);
    }
    
    
    free(matrix1->data);
    free(matrix2->data);
    free(resultMatrix->data);
    free(matrix1);
    free(matrix2);
    free(resultMatrix);
    free(intRing);
}


void TestDoubleMatrix() {
    RingInfo* doubleRing = GetDoubleRingInfo();
    
    Matrix *matrix1 = InitMatrix(2, doubleRing);
    Matrix *matrix2 = InitMatrix(2, doubleRing);
    
    double data1[] = {1.0, 2.0, 3.0, 4.0};
    double data2[] = {5.0, 6.0, 7.0, 8.0};
    
    matrix1->data = malloc(sizeof(data1));
    matrix2->data = malloc(sizeof(data2));
    
    memcpy(matrix1->data, data1, sizeof(data1));
    memcpy(matrix2->data, data2, sizeof(data2));
    
    // Test SumOfMatrix
    Matrix *expectedSum = InitMatrix(2, doubleRing);
    double expectedSumData[] = {6.0, 8.0, 10.0, 12.0};
    expectedSum->data = malloc(sizeof(expectedSumData));
    memcpy(expectedSum->data, expectedSumData, sizeof(expectedSumData));
    
    TestSum(matrix1, matrix2, expectedSum, doubleRing);
    
    CleanMemory(expectedSum);
    free(expectedSum);
    
    // Test MultiplicationOfMatrix
    Matrix *expectedMult = InitMatrix(2, doubleRing);
    double expectedMultData[] = {19.0, 22.0, 43.0, 50.0};
    expectedMult->data = malloc(sizeof(expectedMultData));
    memcpy(expectedMult->data, expectedMultData, sizeof(expectedMultData));
    
    TestMult(matrix1, matrix2, expectedMult, doubleRing);
    
    CleanMemory(expectedMult);
    free(expectedMult);
    
    
    
    free(matrix1->data);
    free(matrix2->data);
    free(matrix1);
    free(matrix2);
    free(doubleRing);
}


void TestComplexMatrix() {
    RingInfo* complexRing = GetComplexRingInfo();
    
    Matrix *matrix1 = InitMatrix(2, complexRing);
    Matrix *matrix2 = InitMatrix(2, complexRing);
    Matrix *resultMatrix = InitMatrix(2, complexRing);

    
    ComplexNumber data1[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
    ComplexNumber data2[] = {{9, 10}, {11, 12}, {13, 14}, {15, 16}};
    
    matrix1->data = malloc(4 * sizeof(ComplexNumber));
    matrix2->data = malloc(4 * sizeof(ComplexNumber));
    
    memcpy(matrix1->data, data1, 4 * sizeof(ComplexNumber));
    memcpy(matrix2->data, data2, 4 * sizeof(ComplexNumber));
    
    // Test SumOfMatrix
    SumOfMatrix(matrix1, matrix2, resultMatrix);
    ComplexNumber expectedSum[] = {{10, 12}, {14, 16}, {18, 20}, {22, 24}};
    for (int i = 0; i < 4; i++) {
        ComplexNumber* res_elem = (ComplexNumber*)resultMatrix->data + i;
        if (res_elem->Re != expectedSum[i].Re || res_elem->Im != expectedSum[i].Im) {
            printf("SumOfMatrix test failed: Expected (%lf, %lf), got (%lf, %lf)\n",
                   expectedSum[i].Re, expectedSum[i].Im, res_elem->Re, res_elem->Im);
        }
    }
    
    // Test MultiplicationOfMatrix
    MultiplicationOfMatrix(matrix1, matrix2, resultMatrix);
    ComplexNumber expectedMult[] = {{-28, 122}, {-32, 142}, {-36, 306}, {-40, 358}};
    for (int i = 0; i < 4; i++) {
        ComplexNumber* res_elem = (ComplexNumber*)resultMatrix->data + i;
        if (res_elem->Re != expectedMult[i].Re || res_elem->Im != expectedMult[i].Im) {
            printf("MultiplicationOfMatrix test failed: Expected (%lf, %lf), got (%lf, %lf)\n",
                   expectedMult[i].Re, expectedMult[i].Im, res_elem->Re, res_elem->Im);
        }
    }
    
    
    free(matrix1->data);
    free(matrix2->data);
    free(resultMatrix->data);
    free(matrix1);
    free(matrix2);
    free(resultMatrix);
    free(complexRing);
}
