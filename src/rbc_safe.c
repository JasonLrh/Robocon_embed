#include "rbc_safe.h"

// include nrf24l01
#include "rbc_pwr.h"
// extern value
extern rbc_pwr * host_rbc_pwr;

// local vars
static uint8_t backup_stop;

static void int_nrf(uint8_t pip, uint8_t * data){
    //read nrf data. check if CMD STOP;
    switch (pip)
    {
    case 0:{

    }break;
    case 1:{// period reload
        // refresh TIM reg;
    }break;
    case 2:{// if check OK, then resum 
        if (data[0] + 1 == backup_stop){
            RBC_LOGS("WIRELESS check OK, restart power system");
            host_rbc_pwr->power_on();
        }else{
            RBC_LOGEF("invalid resume data or state. check your device");
        }
    }break;
    case 3:{

    }break;
    case 4:{

    }break;
    case 5:{// if this line get data, that must be stop in no accont
        host_rbc_pwr->force_stop();
        RBC_LOGEF("WIRELESS STOP");
        backup_stop = data[0]; // used for resume
        
    }break;
    default:
        RBC_LOGE("invalid pip line : %02x", pip);
        break;
    }
}

static void int_tim(void){
    host_rbc_pwr->force_stop();
    RBC_LOGEF("Tim for WIRELESS Timeout");
}

void rbc_safe_init(rbc_safe * handler){
    handler->int_nrf = int_nrf;
    handler->int_tim = int_tim;
}