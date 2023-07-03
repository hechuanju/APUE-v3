#include <stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <unistd.h>

#define MAX_EVENT 10

int main(int argc, char const *argv[])
{
    int epfd, nfds;
    struct epoll_event ev, events[MAX_EVENT];

    // 创建epoll实例
    epfd = epoll_create1(0);
    

    // 设置要监听的文件描述符
    ev.events = EPOLLIN; // 监听可读时间
    ev.data.fd = STDIN_FILENO;
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &ev) == -1) {
        perror("epoll_ctl");
        exit(1);
    }

    // 进入事件循环
    while (1) {
        nfds = epoll_wait(epfd, events, MAX_EVENT, -1);
        if (nfds == -1) {
            perror("epoll_wait");
            exit(1);
        }

        // 处理可读事件
        for (int i = 0; i < nfds; i++) {
            if (events[i].data.fd == STDIN_FILENO) {
                printf("Data available\n");
            }
        }
    }
    return 0;
}
