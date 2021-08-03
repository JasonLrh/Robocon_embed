#ifndef RBC_PWR_H
#define RBC_PWR_H

#include "rbc_log.h"
// #include "rbc.h"

typedef struct rbc_pwr{
    void (*force_stop)(void);
    void (*power_on)(void);
    float (*voltage)(void);
    // output motor
}rbc_pwr;


void rbc_pwr_init(rbc_pwr * handler);

#endif