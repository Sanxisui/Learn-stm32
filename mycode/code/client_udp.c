#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#define PORT 7541

typedef enum {
    SOCKET_CREATE_FAILED = -8,
    BIND_FAILED = -7,
    LISTEN_FAILED = -6,
    ACCEPT_FAILED = -5,
    RECV_FAILED = -4,
    SENDTO_FAILED = -3
} error_t;

/*线程处理函数*/
int pthread_deal_with(void *arg)
{
    int socket_fd = *(int *)arg;
    char r_buf[100] = {0};
    int ret_1 = 0;
    struct sockaddr_in recv_addr = {0};
    socklen_t socklen = sizeof(recv_addr);
    ret_1 = recvfrom(socket_fd, r_buf, sizeof(r_buf), 0, (struct sockaddr *)&recv_addr, &socklen);
    if (ret_1 < 0) {
        printf("%d\n", ret_1);
        perror("recvfrom");
        close(socket_fd);
        exit(SENDTO_FAILED);
    }
    printf("接收到的数据：\n");
    printf("r_buf:%s\n", r_buf);
    memset(r_buf, 0, sizeof(r_buf));
    pthread_exit;
}

int main(int argc, char *argv[])
{
    int socket_fd, ret;
    pthread_t pthread_recv;
    char w_buf[100] = {0};
    /*创建socket*/
    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_fd < 0) {
        perror("Socket:");
        exit(SOCKET_CREATE_FAILED);
    }
    printf("%d\n", socket_fd);

    struct sockaddr_in my_addr = {0};

    // bzero(&my_addr, sizeof(struct sockaddr_in));
    my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(PORT);
    /*监听数据*/
    ret = bind(socket_fd, (struct sockaddr *)&my_addr, (socklen_t)sizeof(my_addr));
    if (ret < 0) {
        perror("bind");
        close(socket_fd);
        exit(BIND_FAILED);
    }
    // ret = pthread_create(&pthread_recv, NULL, (void *)pthread_deal_with, (void *)&socket_fd);

    while (1) {

        printf("请输入发送数据.......\n");
        scanf("%s", w_buf);
        // printf("%s", w_buf);
        ret = sendto(socket_fd, w_buf, sizeof(w_buf), 0, (struct sockaddr *)&my_addr, sizeof(my_addr));
        if (ret < 0) {
            perror("sendto");
            close(socket_fd);
            exit(SENDTO_FAILED);
        }
        ret = pthread_create(&pthread_recv, NULL, (void *)pthread_deal_with, (void *)&socket_fd);
        if (ret < 0) {
            perror("pthread_create");
            close(socket_fd);
            exit(SENDTO_FAILED);
        }
    }
    /*关闭套接字*/
    close(socket_fd);
    return 0;
}