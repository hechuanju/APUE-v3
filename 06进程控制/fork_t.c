#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    pid_t pid;
    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) {
        // 子进程代码
        printf("This is the child process. PID: %d\n", getpid());
    } else {
        // 父进程代码
        printf("This is the parent process. PID: %d, Child PID: %d\n", getpid(), pid);
    }
    return 0;
}
