#include <stdio.h>
#include <stdint.h>

void descomponer(unsigned int dv, unsigned int *nvp, unsigned int *offset, unsigned int page_bits) {
    unsigned int mask = (1 << page_bits) - 1;
    *offset = dv & mask;
    *nvp = dv >> page_bits;
}

