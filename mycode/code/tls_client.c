/***********************************************************
File name : tls_client.c
Author name : ouzw
Email address : 1808975575@qq.com
Create time : 2023-2-22 14:48:59
***********************************************************/
#include <arpa/inet.h>
#include <netinet/in.h>
#include <openssl/err.h>
#include <openssl/ssl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#define SERVER_PORT 4433
#define CERT_FILE "client.crt"
#define KEY_FILE "client.key"
int main()
{
    int client_fd;
    struct sockaddr_in6 server_addr;
    SSL_CTX *ssl_ctx;
    SSL *ssl;
    char buffer[1024];
    // 初始化SSL库
    SSL_library_init();
    SSL_load_error_strings();
    // 创建SSL上下文
    ssl_ctx = SSL_CTX_new(TLSv1_2_client_method());
    if (ssl_ctx == NULL) {
        printf("Create a new SSL context fail\n");
    }
    // 加载客户端证书和私钥
    if (SSL_CTX_use_certificate_file(ssl_ctx, CERT_FILE, SSL_FILETYPE_PEM) <= 0) {
        printf("1-error\n");
    }
    if (SSL_CTX_use_PrivateKey_file(ssl_ctx, KEY_FILE, SSL_FILETYPE_PEM) <= 0) {
        printf("2-error\n");
    }
    // 建立TCP连接
    client_fd = socket(AF_INET6, SOCK_STREAM, 0);
    if (client_fd < 0) {
        perror("socket fail:");
        return -1;
    }
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin6_family = AF_INET6;
    // inet_pton(AF_INET6, SERVER_ADDR, &server_addr.sin6_addr);
    server_addr.sin6_addr = in6addr_any;
    server_addr.sin6_port = htons(SERVER_PORT);
    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect fail:");
        return -1;
    }
    // 建立SSL连接
    ssl = SSL_new(ssl_ctx);
    SSL_set_fd(ssl, client_fd);
    // 进行握手
    if (SSL_connect(ssl) <= 0) {
        perror("why:");
        ERR_print_errors_fp(stderr);
        SSL_shutdown(ssl);

        SSL_free(ssl);
        close(client_fd);
        return 1;
    }
    while (1) {
        SSL_write(ssl, "Hello, server!", strlen("Hello, server!"));
        sleep(1);
        SSL_read(ssl, buffer, sizeof(buffer));
        printf("Received message: %s\n", buffer);
        memset(buffer, 0, sizeof(buffer));
    }
    // Shut down the SSL connection and close the socket
    SSL_shutdown(ssl);
    SSL_free(ssl);
    close(client_fd);
    // Clean up the SSL context
    SSL_CTX_free(ssl_ctx);
    return 0;
}