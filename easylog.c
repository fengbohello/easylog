/*
 * =====================================================================================
 *
 *       Filename:  easylog.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/22/2017 05:47:57 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "easylog.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <stdarg.h>
#include <sys/time.h>
#include <errno.h>

#define DEBUG(fmt, arg...) \
    do{\
        printf(fmt, ##arg);\
        printf("\n");\
    }while(0)

char g_logfile[128] = {0};
int  g_master_fd = -1;
FILE *g_master_fp = NULL;
int  g_master_flag = 0;
const char * g_master_file = NULL;
int g_master_line = -1;
const char * g_master_fun = NULL;
const char * g_master_lev = NULL;

int get_my_name(char * file_name, int len) {
    if(NULL == file_name || len < 0) {   
        return -1; 
    }   
    int ret = readlink("/proc/self/exe", file_name, len);
    if(ret < 0) {   
        return -1; 
    }
    file_name[ret] = '\0';
    strcat(file_name, ".log");

    return 0;
}

int easylog_file(const char * logfile) {
    if(NULL == logfile || strlen(logfile) == 0) {
        return get_my_name(g_logfile, sizeof(g_logfile));
    }
    snprintf(g_logfile, sizeof(g_logfile), "%s", logfile);

    return 0;
}

int easylog_open_file() {
    if(strlen(g_logfile) == 0) {
        easylog_file(NULL);
    }
    if(strlen(g_logfile) == 0) {
        return -1;
    }
#if 0
    errno = 0;
    g_master_fd = open(g_logfile, O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
    if (g_master_fd < 0) {
        DEBUG("open file faild. [%s], errno = [%d]", g_logfile, errno);
        return -1;
    }
    errno = 0;
    g_master_fp = fdopen(g_master_fd, "a");
    if (NULL == g_master_fp) {
        close(g_master_fd);
        DEBUG("fdopen file faild. [%s], errno = [%d], error = [%s]", g_logfile, errno, strerror(errno));
        return -1;
    }
#else
    g_master_fp = fopen(g_logfile, "a");
    if(NULL == g_master_fp) {
        return -1;
    }
    g_master_fd = fileno(g_master_fp);
#endif

    return 0;
}

int file_stat_ok() {
    if(NULL == g_master_fp) {
        return 0;
    }
    struct stat buf;
    errno = 0;
    int r = fstat(fileno(g_master_fp), &buf);
    if (0 == r) {
        return 1;
    }

    return 0;
}

int easylog_write_log(const char * fmt, va_list arg_list) {
    if (0 == file_stat_ok()) {
        easylog_open_file();
    }
    if (0 == file_stat_ok()) {
        return -1;
    }
    struct timeval start;
    gettimeofday(&start, NULL);
    struct tm t;
    bzero(&t, sizeof(t));
    localtime_r(&start.tv_sec, &t);
    if (g_master_flag & EASYLOG_DATE) {
        fprintf(g_master_fp, "%04d-%02d-%02d ", t.tm_year + 1900, t.tm_mon + 1, t.tm_mday);
    }
    if (g_master_flag & EASYLOG_TIME) {
        fprintf(g_master_fp, "%02d:%02d:%02d.%03ld ", t.tm_hour, t.tm_min, t.tm_sec, start.tv_usec / 1000);
    }
    if (g_master_flag & EASYLOG_LEVEL && NULL != g_master_lev) {
        fprintf(g_master_fp, "[%s] ", g_master_lev);
    }
    if (g_master_flag & EASYLOG_FILE && NULL != g_master_file) {
        fprintf(g_master_fp, "%s ", g_master_file);
    }
    if (g_master_flag & EASYLOG_LINE && g_master_line > 0) {
        fprintf(g_master_fp, "%d ", g_master_line);
    }
    if (g_master_flag & EASYLOG_FUNC && NULL != g_master_fun) {
        fprintf(g_master_fp, "%s() ", g_master_fun);
    }
    if(g_master_flag) {
        fprintf(g_master_fp, "%s", "-- ");
    }
    vfprintf(g_master_fp, fmt, arg_list);
    fprintf(g_master_fp, "\n");
    if(g_master_flag & EASYLOG_FLUSH) {
        fflush(g_master_fp);
    }

    return 0;
}

int easylog_write(const char * fmt, ...) {
    va_list argptr;
    int ret;

    va_start(argptr, fmt);
    ret = easylog_write_log(fmt, argptr);
    va_end(argptr);

    return ret;
}

int easylog_flag_add(int flag) {
    g_master_flag |= flag;

    return 0;
}

int easylog_flag_rm(int flag) {
    g_master_flag &= ~flag;

    return 0;
}


