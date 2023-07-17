#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_LINE 1024

int main(int argc, char const *argv[])
{
    pid_t pid;
    int fd[2];
    char line[MAX_LINE];
    int n;

    if (pipe(fd) < 0) {
        perror("pipe");
        exit(EXIT_SUCCESS);
    }

    pid = fork();
    if (pid > 0) {
        close(fd[0]);
        write(fd[1], "hello world\n", 12);
    } else if (pid == 0) {
        close(fd[1]);
        n = read(fd[0], line, MAX_LINE);
        write(STDOUT_FILENO, line, n);
    } else {
        exit(EXIT_FAILURE);
    }

    return 0;
}
