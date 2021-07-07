# Linux下简单的日志库

你可以只需要写两三行代码就完成配置，然后就可以轻快记录日志了。

一个小例子examples/main.c ：

```
#include <stdio.h>
#include "easylog.h"

int main(int argc, char* argv[]) {
    easylog_file("test.log");
    easylog_flag_add(EASYLOG_DATE |
            EASYLOG_TIME |
            EASYLOG_FILE |
            EASYLOG_LINE);
    easylog_flag_add(EASYLOG_FUNC); // 在日志中增加函数名称

    easylog("hello 我的");
    easylog_flag_rm(EASYLOG_DATE);  //在日志中删除日期
    easylog("hello 你的");

    return 0;
}
```

编译examples 目录中的示例代码 main.c

```
make -C examples
```

运行`main`程序

```
./examples/main
```

main 程序会在当前目录下生成 test.log 文件，
查看 test.log 里面的内容：

```
$ cat test.log
2017-06-10 04:42:42.996 main.c 12 main() -- hello 我的
04:42:42.997 main.c 14 main() -- hello 你的
```

其中各个选项的作用如下：

* EASYLOG_DATE : 在日志中添加日期 
* EASYLOG_TIME : 在日志中添加时间 
* EASYLOG_FILE : 在日志中添加本日志语句所在的文件名 
* EASYLOG_LINE : 在日志中添加本日志语句所在的文件中的行 
* EASYLOG_FUNC : 在日志中添加本日志语句所在的函数
* EASYLOG_FLUSH : 每次记录日志都对文件进行flush操作（会导致性能下降）




