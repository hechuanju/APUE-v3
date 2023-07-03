#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int retval;
    struct timeval tv;
    fd_set rfds;

    // 监听标准输入
    FD_ZERO(&rfds);
    FD_SET(STDIN_FILENO, &rfds);

    tv.tv_sec = 5;
    tv.tv_usec = 0;

    retval = select(STDIN_FILENO + 1, &rfds, NULL, NULL, &tv);

    if (retval == -1) {
        perror("select()");
    } else if (retval == 0) {
        printf("timeout, no data within five seconds\n");
    } else {
        if (FD_ISSET(STDIN_FILENO, &rfds))
            printf("Data is available now\n");
    }

    return 0;
}
