#Linux下简单的日志库

你可以只需要写两三行代码就完成配置，然后就可以轻快记录日志了。

一个小例子：

    #nclude <stdio.h>
    #include "easylog.h"
    
    int main(int argc, char* argv[]) {
        easylog_file("test.log");
        easylog_flag_add(EASYLOG_DATE | 
                EASYLOG_TIME |
                EASYLOG_FILE |
                EASYLOG_LINE |
                EASYLOG_FUNC);
        easylog("hello 我的");
        easylog_flag_rm(EASYLOG_DATE);
        easylog("hello 你的");
    
        return 0;
    }


gcc -o main main.c easylog.c

./main

test.log 里面的内容：

2017-06-10 04:42:42.996 main.c 11 main() -- hello 我的
04:42:42.997 main.c 13 main() -- hello 你的

然后就可以用啦，更详细一些的使用在我的博客([http://www.fengbohello.top/code/easylog](http://www.fengbohello.top/code/easylog))里面也有说明哦~



