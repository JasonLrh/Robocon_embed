#ifndef RBC_SENS_H
#define RBC_SENS_H

#include "rbc_log.h"
// #include "rbc.h"

typedef struct rbc_sens{
    int (*position)(int32_t *); // len 2
    int (*motion)(double *);    // motion 4
    
}rbc_sens;


void rbc_sens_init(rbc_sens * handler);

#endif