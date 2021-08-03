#ifndef RBC_H
#define RBC_H

#include "main.h"

// include rbc inner includes
#include "rbc_pwr.h"
#include "rbc_log.h"
#include "rbc_safe.h"
// ...
typedef enum rbc_state{
    UN_INIT = 0,
    INITED,
    POWERON,
    FORCE_STOP
}rbc_state;

#define BIT_SAFE_TIMEOUT   1ULL<<0
#define BIT_SAFE_CMD       1ULL<<1
#define BIT_LOW_VOLTAGE    1ULL<<2


typedef struct rbc{
    rbc_state state;
    uint8_t info;
/* submodule */
    rbc_pwr * pwr;
    rbc_log * log;
    rbc_safe* safe;
}rbc;

void rbc_init(rbc * handler, LOG_FUNCTION log_func);
void rbc_loop(rbc * handler);
void rbc_deinit(rbc * handler);


#endif
