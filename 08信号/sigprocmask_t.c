/*
 * @Author: hechuanju
 * @Date: 2023-08-15 16:33:19
 * @LastEditTime: 2023-08-15 16:34:46
 * @LastEditors: hechuanju
 * @Description: 阻塞信号集
 * 
 * Copyright (c) 2023 by ${hechuanju}, All Rights Reserved.
 */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    sigset_t block_set, pending_set;

    sigemptyset(&block_set);
    sigaddset(&block_set, SIGINT); // 阻塞 SIGINT 信号
    sigaddset(&block_set, SIGTERM); // 阻塞 SIGTERM 信号

    sigprocmask(SIG_BLOCK, &block_set, NULL); // 阻塞指定信号

    printf("Blocking SIGINT and SIGTERM...\n");
    sleep(3); // 等待一段时间，期间无法接收阻塞的信号

    sigpending(&pending_set); // 获取未决信号集

    if (sigismember(&pending_set, SIGINT)) {
        printf("SIGINT is pending.\n");
    }

    if (sigismember(&pending_set, SIGTERM)) {
        printf("SIGTERM is pending.\n");
    }

    sigprocmask(SIG_UNBLOCK, &block_set, NULL); // 解除阻塞

    printf("Unblocking SIGINT and SIGTERM...\n");

    sleep(5); // 等待一段时间，期间可以接收信号，比如中断信号SIGINT

    return 0;
}
