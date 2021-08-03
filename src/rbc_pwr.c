#include "rbc_pwr.h"
#include "rbc.h"
// extern value 
extern rbc_state * host_state;
extern uint8_t * host_info;
// var extend
rbc_pwr * host_rbc_pwr = NULL;

static void force_stop(void){
    RBC_LOGSF("Force Power OFF");
    * host_state = FORCE_STOP;
    // 强制关闭电机电源
}

static void power_on(void){
    if (!(*host_info)){
        RBC_LOGE("Can't Power On : %02x", host_info);
    }
    // 先做判断条件，再考虑开启电源
    RBC_LOGSF("system power on");
    * host_state = POWERON;
}

static float voltage_read(void){
    // value = 0.0
    float value = 24.0;
    // read adc here
    if (value < 18.0){
        force_stop();
        RBC_LOGE("Battery not healthy : %.2f V", value);
        SET_BIT(*host_info, BIT_LOW_VOLTAGE);
    }else{
        RBC_LOGM("Battery voltage : %.2f V", value);
        CLEAR_BIT(*host_info, BIT_LOW_VOLTAGE);
    }

    return value;
}

void rbc_pwr_init(rbc_pwr * handler){
    handler->force_stop = force_stop;
    handler->power_on = power_on;
    handler->voltage = voltage_read;
    host_rbc_pwr = handler;
}

