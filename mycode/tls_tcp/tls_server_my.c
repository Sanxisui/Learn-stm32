/***********************************************************
File name : tls_server_my.c
Author name : xiongyansong
Email address : 750670526@qq.com
Create time : 2023-02-23 16:34:26
***********************************************************/
/*
    1）初使化SSL环境。
    2）创建SSL上下文。
    3）配置SSL上下文证书及公钥信息。
    4）创建SSL上下文。
    5）创建TCP通讯端口。
    6）建立SSL和TCP通讯端口的关联。
    7）执行SSL握手。
    8）执行SSL数据读写交互。
    9）关闭SSL连接。
    10）关于TCP通讯端口。
    11）释放SSL上下文。
*/

#include <stdio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <net/if.h>

#define CERT_FILE "xys.crt"
#define KEY_FILE "xys.key"
#define PORT 7000

int socket_tcp_make()
{
    int socket_fd;

    socket_fd = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
    if (socket_fd < 0) {
        perror("Socket:");
        return -1;
    }

    struct sockaddr_in6 my_addr;
    memset(&my_addr, 0, sizeof(my_addr));
    struct sockaddr_in6 accept_addr;
    memset(&accept_addr, 0, sizeof(accept_addr));
    socklen_t socklen = 0;

    my_addr.sin6_addr = in6addr_any;
    my_addr.sin6_family = AF_INET6;
    my_addr.sin6_port = htons(PORT);

    if (bind(socket_fd, (struct sockaddr *)&my_addr, sizeof(my_addr)) < 0) {
        perror("bind:");
        close(socket_fd);
        return -1;
    }
    if (listen(socket_fd, 10) < 0) {
        perror("listen:");
        close(socket_fd);
        return -1;
    }
    return socket_fd;
}

int main(void)
{
    int ret = 0;
    int new_fd = 0;
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
    /*载入用户的数字证书*/
    ret = SSL_CTX_use_certificate_file(ssl_ctx, CERT_FILE, SSL_FILETYPE_PEM);
    if (ret < 0) {
        printf("use_certificate_file failed\n");
        return 0;
    }
    /*载入用户密钥*/
    ret = SSL_CTX_use_PrivateKey_file(ssl_ctx, KEY_FILE, SSL_FILETYPE_PEM);
    if (ret < 0) {
        printf("use_PrivateKey_file failed\n");
        return 0;
    }
    /*检测用户密钥*/
    ret = SSL_CTX_check_private_key(ssl_ctx);
    if (ret < 0) {
        printf("check_private_key failed\n");
        return 0;
    }
    /*创建套接字*/
    int socked_fd = socket_tcp_make();
    if (socked_fd < 0) {
        SSL_CTX_free(ssl_ctx);
        return -1;
    }

    struct sockaddr_in6 accept_addr = {0};
    socklen_t socklen = sizeof(accept_addr);
    new_fd = accept(socked_fd, (struct sockaddr *)&accept_addr, &socklen);
    if (new_fd < 0) {
        printf("accept failed\n");
        return 0;
    }
    // printf("客户端%s已连接\n", inet_ntoa(accept_addr.sin6_addr));
    /*产生一个新的SSL*/
    SSL *ssl = SSL_new(ssl_ctx);
    /*socket加入到ssl*/
    ret = SSL_set_fd(ssl, new_fd);
    if (ret < 0) {
        printf("ssl_set_fd fail\n");
        return 0;
    }
    /*建立ssl链接/握手*/
    ret = SSL_accept(ssl);
    if (ret < 0) {
        printf("ssl_accept fail\n");
        return 0;
    }
    printf("SSL handshake success! \n");

    int cnt = 10;
    int r_buf[1] = {0};

    while (cnt > 0) {

        ret = SSL_read(ssl, r_buf, 1);
        sleep(1);
        if (ret < 0) {
            printf("SSL_read failed\n");
            SSL_free(ssl);
            close(new_fd);
            close(socked_fd);
            break;
        }
        // printf("%s\n", r_buf);
        cnt--;
    }

    SSL_shutdown(ssl);
    close(new_fd);
    close(socked_fd);
    SSL_CTX_free(ssl_ctx);
    return 0;
}