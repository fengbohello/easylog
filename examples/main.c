#include <stdio.h>
#include "easylog.h"

int main(int argc, char* argv[]) {
    EASYLOG_DEBUG("log will write to file './test.log'"); // EASYLOG_DEBUG 会将日志输出到 stdout
    easylog_file("test.log");
    easylog_flag_add(EASYLOG_DATE |
            EASYLOG_TIME |
            EASYLOG_FILE |
            EASYLOG_LINE);
    easylog_flag_add(EASYLOG_FUNC); // 在日志中增加函数名称

    easylog("hello 我的");          // easylog 会将日志输出到文件
    easylog_flag_rm(EASYLOG_DATE);  //在日志中删除日期
    easylog("hello %s", "你的");
    EASYLOG_DEBUG("test %s", "over");

    return 0;
}
