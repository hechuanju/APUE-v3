#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sigint_haldle(int signum)
{
    printf("Received SIGINT (%d). Exiting...\n", signum);
}

int main(int argc, char const *argv[])
{
    if (signal(SIGINT, sigint_haldle) == SIG_ERR) {
        perror("signal");
        return 1;
    }
    printf("Press Ctrl+C to trigger SIGINT...\n");
    pause(); // 等待信号，阻塞主线程
    printf("eixt main\n");
    return 0;
}
