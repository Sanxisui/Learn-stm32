#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <openssl/ssl.h>
#define PORT 7000

typedef enum {
    SOCKET_CREATE_FAILED = -8,
    CONNNECT_FAILED,
    RECV_FAILED
} error_t;

int main(int argc, char *argv[])
{
    int socket_recv, connect_recv;
    char r_buf[100] = {0};
    char w_buf[100] = {0};
    /*头文件#include<sys/types.h> #include<sys/socket.h>
     *int socket(int domain, int type, int protocol);
     *int domain :设置网络通信的域IPv4orIPv6——AF_INET/PF_INET6
     *int type   :用于设置套接字通信的类型
     *int protocol：一般为0
     *成功返回一个SOCKFD的值，失败 -1
     */
    /*创建socket*/
    if ((socket_recv = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket:");
        exit(SOCKET_CREATE_FAILED);
    }
    printf("hello1\n");
    /*创建sockaddr_in结构体变量,初始值赋0*/
    struct sockaddr_in my_addr = {0};
    // struct sockaddr_in connect_addr = {0};
    // socklen_t socklen = 0;
    /*具体的ip地址，inet_addr 将点分十进制的IPv4地址转换为网络字节序列的长整形*/
    my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    /*使用IPv4地址*/
    my_addr.sin_family = AF_INET;
    /*端口,htonl将主机字节顺序转化为->网络字节顺序，反过来是ntonl*/
    my_addr.sin_port = htons(PORT);
    /*头文件	<sys/types.h> <sys/socket.h>
     *int connect(int sockfd, const struct sockaddr *serv_addr, socklen_t addrlen);
     *类似accpet
     *返回值：成功0，失败-1
     */
    printf("%d\n", socket_recv);
    connect_recv = connect(socket_recv, (struct sockaddr *)&my_addr, sizeof(my_addr));
    if (connect_recv < 0) {
        printf("%d\n", connect_recv);
        perror("connect:");
        exit(CONNNECT_FAILED);
    }
    printf("服务器连接成功\n");
    while (1) {
        /*inet_ntoa()将网络地址转换为"."点隔的字符串格式"*/
        // printf("服务器%s已连接\n", inet_ntoa(my_addr.sin_addr));
        memset(r_buf, 0, sizeof(r_buf));
        /*int recv(int sockfd, char *buf, int len, int flags);
         *int sockfd： 指定接收端套接字描述符
         *char *buf:   指明一个缓冲区，该缓冲区用来存放recv函数接收到的数据
         *int len:     指明buf的长度
         *int flags:   一般设置为0
         *返回值：<0失败 =0关闭 >0成功接受到的字节数
         */
        recv(socket_recv, r_buf, sizeof(r_buf), 0);
        printf("%s\n", r_buf);
        // printf("服务器发送\n");
        // memset(w_buf, 0, sizeof(w_buf));
        // scanf("%s", w_buf);
        // send(socket_recv, w_buf, sizeof(w_buf), 0);
    }
    close(socket_recv);
    return 0;
}