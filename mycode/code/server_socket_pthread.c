#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <pthread.h>

#define PORT 7000
typedef enum {
    SOCKET_CREATE_FAILED = -8,
    BIND_FAILED = -7,
    LISTEN_FAILED = -6,
    ACCEPT_FAILED = -5,
    RECV_FAILED = -4
} error_t;

/*线程处理函数*/
int pthread_deal_with(void *arg)
{
    char r_buf[100] = {0};
    char w_buf[100] = {0};

    memset(w_buf, 0, sizeof(w_buf));
    scanf("%s", w_buf);
    printf("%s\n", w_buf);
    send(*(int *)arg, w_buf, sizeof(w_buf), 0);

    // memset(r_buf, 0, sizeof(r_buf));
    // /*int recv(int sockfd, char *buf, int len, int flags);
    //  *int sockfd： 指定接收端套接字描述符
    //  *char *buf:   指明一个缓冲区，该缓冲区用来存放recv函数接收到的数据
    //  *int len:     指明buf的长度
    //  *int flags:   一般设置为0
    //  *返回值：<0失败 =0关闭 >0成功接受到的字节数
    //  */
    // recv(accept_fd, r_buf, sizeof(r_buf), 0);
    // printf("服务器接收%s\n", r_buf);
    pthread_exit;
}
int main(int argc, char *argv[])
{
    int socket_fd, accept_fd;
    pthread_t pthread_thread;
    int pthread_rev;
    /*头文件#include<sys/types.h> #include<sys/socket.h>
     *int socket(int domain, int type, int protocol);
     *int domain :设置网络通信的域IPv4orIPv6——AF_INET/PF_INET6
     *int type   :用于设置套接字通信的类型
     *int protocol：一般为0
     *成功返回一个SOCKFD的值，失败 -1
     */
    /*创建socket*/
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        perror("Socket");
        exit(SOCKET_CREATE_FAILED);
    }
    printf("%d\n", socket_fd);
    /*创建sockaddr_in结构体变量,初始值赋0*/
    struct sockaddr_in my_addr;
    struct sockaddr_in accept_addr;
    bzero(&my_addr, sizeof(struct sockaddr_in));
    socklen_t socklen = 0;
    /*具体的ip地址，inet_addr 将点分十进制的IPv4地址转换为网络字节序列的长整形*/
    my_addr.sin_addr.s_addr = INADDR_ANY;
    /*使用IPv4地址*/
    my_addr.sin_family = AF_INET;
    /*端口,htonl将主机字节顺序转化为->网络字节顺序，反过来是ntonl*/
    my_addr.sin_port = htons(PORT);

    /*头文件#include<sys/types.h> #include<sys/socket.h> (同socket())
     *int bind(int sockfd, ,const struct sockaddr *my_addr, socklen_t addrlen);
     *int sockfd： socket返回的SOCKED值
     *const struct sockaddr *my_addr：sockaddr中包含了地址、端口和IP地址的信息。
     *socklen_t addrlen: my_addr 结构体的大小
     *失败返回-1，成功0
     */
    /*绑定socket和端口号*/
    if (bind(socket_fd, (struct sockaddr *)&my_addr, sizeof(my_addr)) < 0) {
        perror("bind");
        exit(BIND_FAILED);
    }
    /* #include<sys/socket.h>
     *int listen(int sockfd, int backlog)
     *int sockfd： socket返回的SOCKED值
     *int backlog：挂起的连接队列的最大长度。传入 SOMAXCONN 作用是让系统自动选择最合适的个数
     *成功返回0，失败-1
     */
    /*监听端口号*/
    if (listen(socket_fd, 10) < 0) {
        perror("listen");
        exit(LISTEN_FAILED);
    }

    /*头文件#include <sys/socket.h>
     *int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
     *int sockfd： socket返回的SOCKED值
     *addr：   用于记录发起连接请求的那个客户端的IP端口
     *addrlen  表示第二个参数addr的大小，不顾要求给定地址
     * 成功accept返回一个新的SOCKFD的值用于与连接的客户端通信*/
    /*接受来自客户的连接请求*/
    accept_fd = accept(socket_fd, (struct sockaddr *)&accept_addr, &socklen);
    if (accept_fd < 0) {
        perror("accept");
        exit(ACCEPT_FAILED);
    } else {
        /*inet_ntoa()将网络地址转换为"."点隔的字符串格式"*/
        printf("客户端%s已连接\n", inet_ntoa(accept_addr.sin_addr));

        /*头文件 #include<pthread.h>
         *int pthread_create(
         *         pthread_t *restrict tidp,   //新创建的线程ID指向的内存单元。
         *         const pthread_attr_t *restrict attr,  //线程属性，默认为NULL
         *         void *(*start_rtn)(void *), //新创建的线程从start_rtn函数的地址开始运行
         *         void *restrict arg //默认为NULL。若上述函数需要参数，将参数放入结构中并将地址作为arg传入。
         *         );
         *返回值：成功0，失败-1
         */
        while (1) {
            pthread_rev = pthread_create(&pthread_thread, NULL, (void *)pthread_deal_with, &accept_fd);
            if (pthread_rev < 0) {
                printf("%d", pthread_rev);
                perror("pthread_create");
                close(accept_fd);
                close(socket_fd);
                return 0;
            }
        }
    }
    close(accept_fd);
    close(socket_fd);
    return 0;
}