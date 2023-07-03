#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

int is_key_down(char *key_name)
{
    printf("%s\n", key_name);
    int ret = strcmp(key_name, "reset");
    printf("strcmp result: %d\n", ret);
    return ret;
}

int main(int argc, char const *argv[])
{

    // int status;
    // pid_t pid;
    // pid = fork();

    // if (pid < 0) {
    //     return -1;
    // } else if (pid == 0) {
    //     // 子进程
    //     printf("Child process executing\n");
    //     exit(42);
    // } else {
    //     // 父进程
    //     wait(&status);
    //     WIFEXITED
    // }
    char key_name[32];
    snprintf(key_name, sizeof(key_name) - 1, "reset");
    printf("%s\n", key_name);
    is_key_down(key_name);
    return 0;
}
