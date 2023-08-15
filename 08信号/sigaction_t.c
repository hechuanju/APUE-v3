#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sigint_handler(int signum, siginfo_t *info, void *context) {
    
    printf("Received SIGINT (%d).\n", signum);
    printf("signal number is %d\n", info->si_signo);
    printf("pid = %d\n", info->si_pid);
    printf("sigval = %d\n", info->si_value.sival_int);
    exit(0);
}

int main() {
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = sigint_handler;
    sigemptyset(&sa.sa_mask); // 清空阻塞信号集掩码，即不屏蔽任何辛信号
    sa.sa_flags = SA_SIGINFO | SA_RESTART;

    // 安装 SIGINT 信号处理函数
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    printf("Press Ctrl+C to trigger SIGINT...\n");

    pause(); //等待信号，阻塞主线程

    return 0;
}


