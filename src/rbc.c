#include "rbc.h"
#include <stdlib.h>

#include "usart.h"

// var extend 
rbc_state * host_state = NULL;
uint8_t * host_info = NULL;

void rbc_loop(rbc * handler){
    handler->pwr->voltage(); // needn't to get voltage
    // read sensor 
    // run section
    if (handler->state != POWERON){
        if (READ_BIT(*host_info, BIT_LOW_VOLTAGE) | READ_BIT(*host_info, BIT_SAFE_TIMEOUT)){
            RBC_LOGS("please check error log");
            while(1);
        }else{
            handler->pwr->power_on();
        }
    }
}

// quickly generate and init rbc submodule
#define RBC_CREATE_HANDLER(name,hrbc) rbc_##name*name=malloc(sizeof(rbc_##name)); rbc_##name##_init(name);hrbc->name=name
static uint8_t num = 0;
void rbc_init(rbc * handler, LOG_FUNCTION log_func){
    num+=1;
    if (num > 1){
        RBC_LOGEF("More than one rbc has been init");
        return;
    }else if(handler->state != UN_INIT){
        RBC_LOGEF("This handler has been inited yet");
        return;
    }
    host_info = &(handler->info);
    host_state = &(handler->state);
    // inner compounents initial
    RBC_CREATE_HANDLER( log  , handler );
    log->change_output_location(log_func);

    RBC_CREATE_HANDLER( pwr  , handler );
    RBC_CREATE_HANDLER( safe , handler );
    // give into rbc stucture
    handler->state = INITED;
    RBC_LOGI("rbc inital OK");
}
// quickly delet submodule
#define RBC_DELETE_HANDLER(name,hrbc) free(hrbc->name)
void rbc_deinit(rbc * handler){
    num = 0;
    if (handler->state == POWERON){
        handler->pwr->force_stop();
        RBC_LOGM("Machine is running. trying stoping ...");
    }
    RBC_DELETE_HANDLER( log, handler);
    RBC_DELETE_HANDLER( pwr, handler);
    RBC_DELETE_HANDLER( safe,handler);
    handler->state = UN_INIT;
}
