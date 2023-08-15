/*
 * @Author: hechuanju
 * @Date: 2023-08-15 16:26:01
 * @LastEditTime: 2023-08-15 16:27:33
 * @LastEditors: hechuanju
 * @Description: 使用sigqueue发送附带简单信息的信号，请结合sigaction_t.c来食用
 * 
 * Copyright (c) 2023 by ${hechuanju}, All Rights Reserved.
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <pid> <value>\n", argv[0]);
        return 1;
    }

    pid_t target_pid = atoi(argv[1]);
    int value = atoi(argv[2]);

    union sigval sigval_data;
    sigval_data.sival_int = value;

    int result = sigqueue(target_pid, SIGINT, sigval_data);
    if (result == -1) {
        perror("sigqueue");
        return 1;
    }

    printf("Sent SIGINT signal to process %d with value %d\n", target_pid, value);

    return 0;
}
