#include <stdio.h>
#include "ringinfo.h"
#include "complex.h"
#include "int_algebra.h"
#include "stdlib.h"
#include "matrix.h"
#include "tests.h"


int main() {
    int dataTypeChoice = 1;
    int operationMenuChoice;
    int dataType;
    int matrixSize = 0;
    int flag = 1;
    
    while (dataTypeChoice) {
        printf("Choose type of data you want to use:\n0 Integer\n1 Real\n2 Complex\n3 Exit\n");
        dataType = input_integer();
        
        if (dataType == 3) {
            return 0;
        } else if (dataType >= 0 && dataType <= 2) {
            dataTypeChoice = 0;
        } else {
            printf("Error: wrong number, try again\n");
        }
    }
    
    while (matrixSize < 1) {
        printf("Enter size of matrix:");
        matrixSize = input_integer();
        
        if (matrixSize < 1) {
            printf("Error: size cannot be zero or negative\n");
        }
    }
    
    RingInfo* ringInfo;
    switch (dataType) {
        case 0:
            ringInfo = GetIntRingInfo();
            break;
        case 1:
            ringInfo = GetDoubleRingInfo();
            break;
        case 2:
            ringInfo = GetComplexRingInfo();
            break;
    }
    
    Matrix *matrix1 = InitMatrix(matrixSize, ringInfo);
    Matrix *matrix2 = InitMatrix(matrixSize, ringInfo);
    Matrix *resultMatrix = InitMatrix(matrixSize, ringInfo);
    
    Matrix *matrices[3] = {matrix1, matrix2, resultMatrix};
    
    operationMenuChoice = 1;
    
    while (flag) {
        printf("What do you want to do?\n0 Input matrix\n1 Output matrix\n2 Sum of two matrices\n3 Multiplication of two matrices\n"
               "4 Add linear combination of lines\n5 Delete matrix\n6 Tests\n7 Exit\n");
        operationMenuChoice = input_integer();
        
        switch (operationMenuChoice) {
            case 0:
                printf("Choose matrix:\n0 First matrix\n1 Second matrix\n");
                int selectedMatrixIndex = input_integer();
                
                if (selectedMatrixIndex == 0 || selectedMatrixIndex == 1) {
                    InputMatrix(matrices[selectedMatrixIndex]);
                } else {
                    printf("Error: wrong number\n");
                }
                break;

            case 1:
                printf("Choose matrix:\n0 First matrix\n1 Second matrix\n2 Result-matrix\n");
                int outputMatrixIndex = input_integer();
                
                if (outputMatrixIndex >= 0 && outputMatrixIndex <= 2) {
                    if (matrices[outputMatrixIndex]->data == NULL) {
                        printf("Error: matrix doesn't exist\n");
                        break;
                    }
                    OutputMatrix(matrices[outputMatrixIndex]);
                } else {
                    printf("Error: wrong number\n");
                }
                break;

            case 2:
                if (matrix1->data == NULL || matrix2->data == NULL) {
                    printf("Error: one of matrix doesn't exist\n");
                    break;
                }
                printf("Result will be saved into result-matrix\n");
                SumOfMatrix(matrix1, matrix2, resultMatrix);
                printf("Done\n");
                break;

            case 3:
                printf("0 First on first\n1 First on second\n2 Second on first\n3 Second on second\n");
                int matrixMultiplicationOption = input_integer();
                if (matrixMultiplicationOption >= 0 && matrixMultiplicationOption <= 3) {
                    printf("Result will be saved into result-matrix\n");
                    switch (matrixMultiplicationOption) {
                        case 0:
                            if (matrix1->data == NULL) {
                                printf("Error: first matrix doesn't exist\n");
                                break;
                            }
                            MultiplicationOfMatrix(matrix1, matrix1, resultMatrix);
                            printf("Done\n");
                            break;
                        case 1:
                            if (matrix1->data == NULL || matrix2->data == NULL) {
                                printf("Error: one of matrix doesn't exist\n");
                                break;
                            }
                            MultiplicationOfMatrix(matrix1, matrix2, resultMatrix);
                            printf("Done\n");
                            break;
                        case 2:
                            if (matrix1->data == NULL || matrix2->data == NULL) {
                                printf("Error: one of matrix doesn't exist\n");
                                break;
                            }
                            MultiplicationOfMatrix(matrix2, matrix1, resultMatrix);
                            printf("Done\n");
                            break;
                        case 3:
                            if (matrix2->data == NULL) {
                                printf("Error: second matrix doesn't exist\n");
                                break;
                            }
                            MultiplicationOfMatrix(matrix2, matrix2, resultMatrix);
                            printf("Done\n");
                            break;
                    }
                } else {
                    printf("Error: wrong number\n");
                }
                break;

            case 4:
                printf("Choose matrix:\n0 First matrix\n1 Second matrix\n");
                int selectedMatrix = input_integer();
                if (selectedMatrix == 0 || selectedMatrix == 1) {
                    if (matrices[selectedMatrix]->data == NULL) {
                        printf("Error: matrix doesn't exist\n");
                        break;
                    }
                    int n = matrices[selectedMatrix]->size_matrix;
                    int lineA, lineB;
                    printf("Which line A * scalar you want to add to line B. Enter A and B\n");
                    lineA = input_integer();
                    lineB = input_integer();
                    if (!(lineA > 0 && lineB > 0 && lineA <= n && lineB <= n)) {
                        printf("Error: wrong line numbers\n");
                        break;
                    }
                    printf("Enter scalar: ");
                    void *scalar = calloc(1, matrices[selectedMatrix]->ring->size);
                    if (dataType == 0) {
                        *(int *)scalar = input_integer();
                    } else {
                        *(double *)scalar = input_double();
                    }
                    AddLinearCombination(matrices[selectedMatrix], lineA, lineB, scalar);
                    printf("Done\n");
                    free(scalar);
                } else {
                    printf("Error: wrong number\n");
                }
                break;

            case 5:
                printf("Choose matrix:\n0 First matrix\n1 Second matrix\n");
                int matrixToDelete = input_integer();
                if (matrixToDelete == 0 || matrixToDelete == 1) {
                    if (matrices[matrixToDelete]->data == NULL) {
                        printf("Error: matrix doesn't exist\n");
                        break;
                    }
                    CleanMemory(matrices[matrixToDelete]);
                } else {
                    printf("Error: wrong number\n");
                }
                break;
            
            case 6:
                RunAllTests();

            case 7:
                flag = 0;
                break;
            default:
                printf("Error: wrong number\n");
        }
    }

    for (int i = 0; i < 3; i++) {
        if (matrices[i]->data != NULL) {
            CleanMemory(matrices[i]);
        }
        free(matrices[i]);
    }

    free(ringInfo);

    return 0;
}
