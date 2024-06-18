#include "ringinfo.h"
#include "stdlib.h"
#include "time.h"
#include "matrix.h"
#include "complex.h"

#define MAX_RING_INFOS 10
static RingInfo* ringInfos[MAX_RING_INFOS] = {NULL};
static int numRingInfos = 0;

RingInfo* InitRingInfo(
        size_t size,
        void (*sum)(const void *, const void *, void *),
        void (*mult)(const void *, const void *, void *),
        void (*zero)(void *),
        void (*input)(Matrix *),
        void (*output)(Matrix *)) {

  
    for (int i = 0; i < numRingInfos; i++) {
        RingInfo* ring = ringInfos[i];
        if (ring->size == size && ring->sum == sum && ring->mult == mult &&
            ring->zero == zero && ring->input == input && ring->output == output) {
            return ring;
        }
    }

    
    RingInfo* ring = calloc(1, sizeof(RingInfo));
    ring->size = size;
    ring->sum = sum;
    ring->mult = mult;
    ring->zero = zero;
    ring->input = input;
    ring->output = output;


    ringInfos[numRingInfos++] = ring;

    return ring;
}
