#ifndef _EASYLOG_H_
#define _EASYLOG_H_

extern const char* g_master_file;
extern int         g_master_line;
extern const char* g_master_fun;
extern const char* g_master_lev;

#define EASYLOG_DATE    (1 << 0)
#define EASYLOG_TIME    (1 << 1)
#define EASYLOG_FILE    (1 << 2)
#define EASYLOG_LINE    (1 << 3)
#define EASYLOG_FUNC    (1 << 4)
#define EASYLOG_LEVEL   (1 << 5)
#define EASYLOG_FLUSH   (1 << 8)

int easylog_flag_add(int flag);
int easylog_flag_rm(int flag);
int easylog_file(const char * logfile);
int easylog_write(const char * fmt, ...);

#define easylog_log(fmt, arg...) \
    do{\
        g_master_file = __FILE__;\
        g_master_line = __LINE__;\
        g_master_fun  = __func__;\
        g_master_lev  = "INFO";\
        easylog_write(fmt, ##arg);\
    }while(0)

#define easylog_err(fmt, arg...) \
    do{\
        g_master_file = __FILE__;\
        g_master_line = __LINE__;\
        g_master_fun  = __func__;\
        g_master_lev  = "ERROR";\
        easylog_write(fmt, ##arg);\
    }while(0)


#define easylog(fmt, arg...) \
    do{\
        g_master_file = __FILE__;\
        g_master_line = __LINE__;\
        g_master_fun  = __func__;\
        g_master_lev  = "INFO";\
        easylog_write(fmt, ##arg);\
    }while(0)

#endif

