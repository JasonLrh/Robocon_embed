/* using nrf24l01 to safely operate all the devices
public channel:
    pip0:period release state OK buffer
    pip1:STOP ALL THE CALL(whatever received)
我们需要几个管道，
    公共信道
        一个无论收到什么都需要停止所有输出系统
        一个收到特定信号确定停转恢复（stop信号值+1）
        一个周期性接收在线信号（暂定500ms 用定时器判断，如果到1s，则也停止所有输出）
*/
#ifndef RBC_SAFE_H
#define RBC_SAFE_H

#include <stdint.h>


/* LOCAL DEFINES BEGIN */
#define RBC_SAFE_MODULE_ENABLE
/* LOCAL DEFINES END */



typedef struct rbc_safe{
    void (*int_nrf)(uint8_t,uint8_t*);
    void (*int_tim)(void);

}rbc_safe;


void rbc_safe_init(rbc_safe * handler);

#endif