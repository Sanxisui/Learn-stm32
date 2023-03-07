#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <netinet/in.h>
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
// int pthread_deal_with(void *arg)
// {

// }

int main(int argc, char *argv[])
{
    int socket_fd, ret;

    char r_buf[100] = {0};
    char w_buf[100] = {0};
    /*创建socket*/
    socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_fd < 0) {
        perror("Socket:");
        exit(SOCKET_CREATE_FAILED);
    }

    struct sockaddr_in my_addr;
    bzero(&my_addr, sizeof(struct sockaddr_in));

    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(PORT);
    socklen_t socklen = sizeof(my_addr);
    while (1) {
        scanf("%s", w_buf);
        printf("准备发送数据.......\n");
        // sleep(5);
        ret = sendto(socket_fd, w_buf, sizeof(w_buf), 0, (struct sockaddr *)&my_addr, socklen);
        if (ret < 0) {
            perror("sendto");
            close(socket_fd);
            exit(SENDTO_FAILED);
        }

        /*关闭套接字*/
    }

    scanf("%s", w_buf);
    printf("准备发送数据.......\n");
    // sleep(5);
    ret = sendto(socket_fd, w_buf, sizeof(w_buf), 0, (struct sockaddr *)&my_addr, socklen);
    if (ret < 0) {
        perror("sendto");
        close(socket_fd);
        exit(SENDTO_FAILED);
    }

    /*关闭套接字*/
    close(socket_fd);
    return 0;
}