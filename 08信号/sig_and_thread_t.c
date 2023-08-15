/*
 * @Author: hechuanju
 * @Date: 2023-08-15 16:57:11
 * @LastEditTime: 2023-08-15 17:50:31
 * @LastEditors: hechuanju
 * @Description: 信号与线程的关系
 * 每个线程都有各自的阻塞信号集，这意味着相同的信号它们可以有自己不同的处理方式。在这个例子中，线程1忽略了SIGUSR1信号继续运行，而线程2接收该信号后退出
 * Copyright (c) 2023 by ${hechuanju}, All Rights Reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>

void* thread1_function(void* arg) {
    int cnt = 10;
    printf("Thread 1 is ignoring SIGUSR1...\n");

    // 忽略 SIGUSR1 信号
    sigset_t block_set;
    sigemptyset(&block_set);
    sigaddset(&block_set, SIGUSR1); // 阻塞 SIGINT 信号
    if (pthread_sigmask(SIG_BLOCK, &block_set, NULL) != 0) {
        perror("pthread_sigmask");
        return NULL;
    }

    while (cnt--) {
        // 模拟线程1的执行
        sleep(1);
        printf("thread 1 is running\n");
    }
    printf("thread 1 exit\n");
    return NULL;
}

void sigusr1_handler(int signum, siginfo_t *info, void *context) {
    printf("Thread 2 received SIGUSR1 (%d).\n", signum);
}

void* thread2_function(void* arg) {
    struct sigaction sa;
    sa.sa_sigaction = sigusr1_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO | SA_RESTART;

    // 安装 SIGUSR1 信号处理函数
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        return NULL;
    }

    printf("Thread 2 is waiting for SIGUSR1...\n");

    pause();

    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    if (pthread_create(&thread1, NULL, thread1_function, NULL) != 0 ||
        pthread_create(&thread2, NULL, thread2_function, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }

    sleep(3);
    // 等待一段时间后，开始向自身发送SIGUSR1信号
    printf("start sending SIGUSR1\n");
    raise(SIGUSR1);

    // 等待线程结束
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}

