#include "rbc_sens.h"

static int position(int32_t *a){
    int32_t x,y;
    if (a == NULL){
        return -1;
    }
    // read position sensor here
    a[0] = x;
    a[1] = y;
    return 0;
}

static int motion(double * motion)
{
    // motion in Euler or uqarter
    return 0;
}

void rbc_sens_init(rbc_sens * handler){
    handler->position = position;
}