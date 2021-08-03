#ifndef RBC_LOG_H
#define RBC_LOG_H

#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>

/* LOCAL DEFINES BEGIN */
/* input method choice : bool */
// #define RBC_LOG_STD
// #define RBC_LOG_DISABLE
#define RBC_LOG_USER
/* use color terminal? input method : bool */
#define COLOR_TERMINAL

#define END_LINE "\r\n"
/* LOCAL DEFINES END */

typedef void (*LOG_FUNCTION)(char *,size_t);
typedef struct rbc_log
{
    void (*change_output_location)(LOG_FUNCTION);
}rbc_log;

void rbc_log_init(rbc_log * handler);

int RBC_LOGRAW(char * fmt, ...);

#ifdef COLOR_TERMINAL
#define COLOR_SET(bg,ft) "\033["#bg";"#ft"m"
#define COLOR_CLEAR "\033[0m"
#else
#define COLOR_SET(bg,fg)
#define COLOR_CLEAR
#endif

#define RBC_F_FORMAT "%s:%d@%s() -> $ "
#define RBC_F_ARGS   __FILE__,__LINE__,__FUNCTION__
#define RBC_LOGEF(fmt,...) RBC_LOGRAW(COLOR_SET(31,40)"[ERROR]"RBC_F_FORMAT fmt COLOR_CLEAR END_LINE,RBC_F_ARGS,##__VA_ARGS__)
#define RBC_LOGIF(fmt,...) RBC_LOGRAW(COLOR_SET(32,40)"[INFO] "RBC_F_FORMAT fmt COLOR_CLEAR END_LINE,RBC_F_ARGS,##__VA_ARGS__)
#define RBC_LOGDF(fmt,...) RBC_LOGRAW(COLOR_SET(33,40)"[DEBUG]"RBC_F_FORMAT fmt COLOR_CLEAR END_LINE,RBC_F_ARGS,##__VA_ARGS__)
#define RBC_LOGMF(fmt,...) RBC_LOGRAW(COLOR_SET(36,40)"[MSG]  "RBC_F_FORMAT fmt COLOR_CLEAR END_LINE,RBC_F_ARGS,##__VA_ARGS__)
#define RBC_LOGSF(fmt,...) RBC_LOGRAW(COLOR_SET(35,40)"[SYS]  "RBC_F_FORMAT fmt COLOR_CLEAR END_LINE,RBC_F_ARGS,##__VA_ARGS__)

#define RBC_STD_FORMAT "-> $ "
#define RBC_LOGE(fmt,...) RBC_LOGRAW(COLOR_SET(31,40)"[ERROR]"RBC_STD_FORMAT fmt COLOR_CLEAR END_LINE,##__VA_ARGS__)
#define RBC_LOGI(fmt,...) RBC_LOGRAW(COLOR_SET(32,40)"[INFO] "RBC_STD_FORMAT fmt COLOR_CLEAR END_LINE,##__VA_ARGS__)
#define RBC_LOGD(fmt,...) RBC_LOGRAW(COLOR_SET(33,40)"[DEBUG]"RBC_STD_FORMAT fmt COLOR_CLEAR END_LINE,##__VA_ARGS__)
#define RBC_LOGM(fmt,...) RBC_LOGRAW(COLOR_SET(36,40)"[MSG]  "RBC_STD_FORMAT fmt COLOR_CLEAR END_LINE,##__VA_ARGS__)
#define RBC_LOGS(fmt,...) RBC_LOGRAW(COLOR_SET(35,40)"[SYS]  "RBC_STD_FORMAT fmt COLOR_CLEAR END_LINE,##__VA_ARGS__)

#endif