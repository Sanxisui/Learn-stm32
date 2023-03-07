/***********************************************************
File name : tls_server.c
Author name : ouzw
Email address : 1808975575@qq.com
Create time : 2023-02-21 20:20:44
***********************************************************/
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <openssl/err.h>
#include <openssl/ssl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define CERT_FILE "server.crt"
#define KEY_FILE "server.key"
int main()
{
    int server_fd, client_fd;
    struct sockaddr_in6 server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    SSL_CTX *ssl_ctx;
    SSL *ssl;
    char buffer[1024];
    // 初始化
    SSL_library_init();
    SSL_load_error_strings();
    // 创建SSL上下文
    ssl_ctx = SSL_CTX_new(TLSv1_2_server_method());
    if (ssl_ctx == NULL) {
        printf("Create a new SSL context fail\n");
    }
    // 加载服务器证书和私钥
    if (SSL_CTX_use_certificate_file(ssl_ctx, CERT_FILE, SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        return -1;
    }
    if (SSL_CTX_use_PrivateKey_file(ssl_ctx, KEY_FILE, SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        return -1;
    }
    // 建立TCP连接
    server_fd = socket(AF_INET6, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket fail:");
        return -1;
    }
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin6_family = AF_INET6;
    server_addr.sin6_addr = in6addr_any;
    server_addr.sin6_port = htons(4433);
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind fail:");
        return -1;
    }
    if (listen(server_fd, SOMAXCONN) < 0) {
        perror("listen open fail:");
        return -1;
    }
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr,
                       &client_addr_len);
    // 建立SSL连接
    ssl = SSL_new(ssl_ctx);
    SSL_set_fd(ssl, client_fd);
    // 握手
    if (SSL_accept(ssl) <= 0) {
        ERR_print_errors_fp(stderr);
        SSL_shutdown(ssl);
        SSL_free(ssl);
        close(client_fd);
        return -1;
    }
    char send_buf[1024];
    while (1) {
        SSL_read(ssl, buffer, sizeof(buffer));
        printf("Received message: %s\n", buffer);
        sprintf(send_buf, "server recv:%s", buffer);
        SSL_write(ssl, send_buf, strlen(send_buf) + 1);
        bzero(send_buf, sizeof(send_buf));
        bzero(buffer, sizeof(buffer));
    }
    SSL_shutdown(ssl);
    SSL_free(ssl);
    close(client_fd);
    SSL_CTX_free(ssl_ctx);
    close(server_fd);
    return 0;
}