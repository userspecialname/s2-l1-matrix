#ifndef LNLAB1_RINGINFO_H
#define LNLAB1_RINGINFO_H

#include <stdio.h>





typedef struct Matrix Matrix;
typedef struct complex_number ComplexNumber;
typedef struct RingInfo RingInfo;
typedef struct RingInfo {
    size_t size;
    void (*sum)(const void *, const void *, void *);
    void (*mult)(const void *, const void *, void *);
    void (*zero)(void *);
    void (*input)(Matrix *);
    void (*output)(Matrix *);
} RingInfo;


RingInfo *InitRingInfo(
        size_t size,
        void (*sum)(const void *, const void *, void *),
        void (*mult)(const void *, const void *, void *),
        void (*zero)(void *),
        void (*input)(Matrix *),
        void (*output)(Matrix *));


#endif //LNLAB1_RINGINFO_H
