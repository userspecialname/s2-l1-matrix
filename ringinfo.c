#include "ringinfo.h"
#include "stdlib.h"
#include "time.h"
#include "matrix.h"
#include "complex.h"

RingInfo *InitRingInfo(
        size_t size,
        void (*sum)(const void * a, const void * b, void * sum),
        void (*mult)(const void *a , const void * b, void * res),
        void (*zero)(void * a),
        void (*input)(Matrix *),
        void (*output)(Matrix *)) {
    RingInfo *ring = calloc(1, sizeof(RingInfo));
    ring->size = size;
    ring->sum = sum;
    ring->mult = mult;
    ring->zero = zero;
    ring->input = input;
    ring->output = output;
    return ring;
}

