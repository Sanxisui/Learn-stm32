/***********************************************************
File name : tls_server_my.c
Author name : xiongyansong
Email address : 750670526@qq.com
Create time : 2023-02-24 15:33:27
***********************************************************/
#include <stdio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <linux/sockios.h>
#include <net/if.h>

#define PORT 7000

int main(void)
{
    int ret = 0;

    int socket_fd = 0;
    /*创建一个结构体指针*/
    SSL_CTX *ssl_ctx;

    /*初使化SSL环境*/
    SSL_library_init();
    /*载入所有ssl算法*/
    // OpenSSL_add_all_algorithms();
    /*载入所有SSL错误信息*/
    SSL_load_error_strings();
    /*产生一个SSL_CTX,建立上下文连接*/
    /*const SSL_METHOD *meth // 传入的版本*/
    ssl_ctx = SSL_CTX_new(TLSv1_2_server_method());

    if (ssl_ctx == NULL) {
        printf(" Create a new SSL context fail\n");
        return 0;
    }

    socket_fd = socket(AF_INET6, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        perror("Socket:");
        return -1;
    }

    struct sockaddr_in6 my_addr = {0};

    my_addr.sin6_family = AF_INET6;
    my_addr.sin6_port = htons(PORT);
    my_addr.sin6_addr = in6addr_any;

    /*创建套接字*/

    ret = connect(socket_fd, (struct sockaddr *)&my_addr, sizeof(my_addr));
    if (ret < 0) {
        printf("%d\n", ret);
        perror("connect");
        return 0;
    }
    /*产生一个新的SSL*/
    SSL *ssl = SSL_new(ssl_ctx);
    /*socket加入到ssl*/
    ret = SSL_set_fd(ssl, socket_fd);
    if (ret < 0) {
        printf("ssl_set_fd fail\n");
        return 0;
    }
    /*建立ssl链接/握手*/
    ret = SSL_connect(ssl);
    if (ret < 0) {
        printf("ssl_connect fail\n");
        return 0;
    }
    printf("SSL handshake success! \n");

    int cnt = 10;
    int w_buf[1] = {0};
    char buffer[1024];
    while (cnt > 0) {
        w_buf[1] = cnt;
        ret = SSL_write(ssl, w_buf, 1);
        sleep(1);
        if (ret < 0) {
            printf("SSL_write failed\n");
            SSL_free(ssl);
            close(socket_fd);
            break;
        }
        printf("%d", w_buf[1]);
        memset(w_buf, 0, 1);
        cnt--;
    }
    SSL_shutdown(ssl);
    close(socket_fd);
    SSL_CTX_free(ssl_ctx);
    return 0;
}