#include <stdio.h>
#include "rbc_log.h"

#ifdef RBC_LOG_STD
#define RBC_LOGRAW(fmt, ...) printf(fmt, ...)
#elif defined RBC_LOG_DISABLE
int RBC_LOGRAW(char * fmt, ...){
    return 0;
}
#elif defined RBC_LOG_USER
static char buff[100];
static LOG_FUNCTION log_user = NULL;

int RBC_LOGRAW(char * fmt, ...) {
    va_list aptr;int ret;
    va_start(aptr, fmt);
    ret = vsprintf(buff,fmt,aptr);
    va_end(aptr);
    if(ret>0){
        if(log_user != NULL){
            log_user(buff,ret);
        }
    }
    return ret;
}

static void change_output_direction(LOG_FUNCTION t){
    if (t!=NULL){
        log_user = t;
    }
    RBC_LOGM("LOG function Has been set");
}

#else
#error "Plese select LOG type: RBC_LOG_STD,RBC_LOG_DISABLE,RBC_LOG_USER"
#endif

#ifndef RBC_LOG_USER 
static void change_output_direction(LOG_FUNCTION t){
    if (t!=NULL){

    }
}
#elif defined RBC_LOGRAW
#error "mutiple log config defined"
#endif

void rbc_log_init(rbc_log * handler){
    handler->change_output_location = change_output_direction; // blink led ...
    RBC_LOGE("quem");
}