#ifndef LNLAB1_RINGINFO_H
#define LNLAB1_RINGINFO_H

#include <stdio.h>





typedef struct Matrix Matrix;
typedef struct complex_number ComplexNumber;
typedef struct RingInfo RingInfo;
typedef struct RingInfo {
    size_t size;
    void (*sum)(const void *a, const void *b, void *ResSum);
    void (*mult)(const void *a, const void *b, void *ResMult);
    void (*zero)(void *);
    void (*input)(Matrix *);
    void (*output)(Matrix *);
} RingInfo;


RingInfo *InitRingInfo(
        size_t size,
        void (*sum)(const void *a, const void *b, void *ResSum),
        void (*mult)(const void *a, const void *b, void *ResMult),
        void (*zero)(void *),
        void (*input)(Matrix *),
        void (*output)(Matrix *));


#endif //LNLAB1_RINGINFO_H
