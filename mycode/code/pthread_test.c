#if 0

#include <pthread.h>
#include <stdio.h>

typedef struct
{
    char b;
    void *(*fp)(void *);
} test_t;

int pthread_one(test_t pthread_struct)
{
    // printf("a=\n");
    printf("pthread_one2:%p\n", pthread_struct.fp);
    pthread_exit;
}

int main()
{
    test_t pthread_struct = {'a', (void *)pthread_one};
    // printf("%p\n", pthread_one);
    printf("pthread_one:%p\n", pthread_one);
    printf("pthread_struct.fp:%p\n", pthread_struct.fp);
    printf("&pthread_struct:%p\n", &pthread_struct);
    pthread_t pthread_thread, a;
    // a = 5;
    int pthread_recv;
    /*头文件 #include<pthread.h>
     *int pthread_create(
     *         pthread_t *restrict tidp,   //新创建的线程ID指向的内存单元。
     *         const pthread_attr_t *restrict attr,  //线程属性，默认为NULL
     *         void *(*start_rtn)(void *), //新创建的线程从start_rtn函数的地址开始运行
     *         void *restrict arg //默认为NULL。若上述函数需要参数，将参数放入结构中并将地址作为arg传入。
     *         );
     *返回值：成功0，失败-1
     */
    pthread_recv = pthread_create(&pthread_thread, NULL, pthread_struct.fp, &pthread_struct);
    if (pthread_recv < 0) {
        perror("pthread_create");
        return 0;
    }
    return 0;
}
#endif
#if 0
#include <stdio.h>
#include <pthread.h>
#include "list.h"
#include <unistd.h>
typedef struct
{
    struct list_head my_list;
    int a;
} arg_t;

int pth_fun(void *arg)
{
    arg_t pth_fun_arg = *(arg_t *)arg;
    printf("**************************************\n");
    printf("sizeof(arg_t):%ld\n", sizeof(pth_fun_arg));
    printf("hello,pthread1\n");
    printf("pth_fun_arg:%d\n", pth_fun_arg.a);
    // pthread_exit((void *)&pth_fun_arg.a);
}

int main(int argc, char argv[])
{
    pthread_t pthread_id;
    int pthread_recv, cnt = 3;
    arg_t arg = {0};
    arg.a = 10;
    int text_t = 0;
    while (cnt > 0) {
        pthread_recv = pthread_create(&pthread_id, NULL, (void *)pth_fun, (void *)&arg);
        // printf("pthread_recv_after_join:%ld\n", pthread_id);
        if (pthread_recv < 0) {
            break;
        }
        printf("**************************************\n");
        pthread_recv = pthread_join(pthread_id, (void *)&text_t);
        if (pthread_recv != 0) {
            break;
        }
        printf("text_t:%d\n", text_t);
        cnt = cnt - 1;
    }
    // pthread_join(pthread_id, (void *)&text_t);
    // printf("**************************************\n");
    // printf("pthread_recv_after_join:%d\n", pthread_id);
    // printf("text_t:%d\n", *text_t);
    return 0;
}
#endif
#if 0
#include <stdio.h>
#include <pthread.h>
#include "list.h"
#include <unistd.h>

typedef struct
{
    struct list_head my_list;
    int a;
} arg_t;

int pth_fun(void *arg)
{
    arg_t pth_fun_arg = *(arg_t *)arg;
    printf("**************************************\n");
    printf("sizeof(arg_t):%ld\n", sizeof(pth_fun_arg));
    printf("hello,pthread1\n");
    pthread_testcancel();
    sleep(1);
    printf("pth_fun_arg:%d\n", pth_fun_arg.a);
    pthread_exit((void *)&pth_fun_arg.a);
}
int main(int argv, char argc[])
{
    pthread_t pthread_id;
    int pthread_recv, cnt = 3;
    arg_t arg = {0};
    pthread_recv = pthread_create(&pthread_id, NULL, (void *)pth_fun, (void *)&arg);
    cnt = pthread_cancel(pthread_id);
    printf("%d\n", cnt);
    // printf();
    return 0;
}
#endif

#if 0
#include <stdio.h>
#include <pthread.h>
#include "list.h"
#include <unistd.h>
#include <stdlib.h>
typedef struct
{
    struct list_head my_list;
    int a;
} arg_t;

int pth_fun(void *arg)
{
    arg_t *pth_fun_arg = (arg_t *)arg;
    // printf("%d\n", pth_fun_arg->a);
    printf("**************************************\n");
    pth_fun_arg->a = 10;
    printf("pth_fun_arg:%d\n", pth_fun_arg->a);
    pthread_exit(pth_fun_arg);
}
int main(int argv, char argc[])
{

    pthread_t pthread_id_one, pthread_id_two;

    int pthread_recv, cnt = 3;
    arg_t *arg, *pth_return_val;
    arg = (arg_t *)malloc(sizeof(arg_t));
    pthread_recv = pthread_create(&pthread_id_one, NULL, (void *)pth_fun, arg);
    pthread_join(pthread_id_one, (void **)&pth_return_val);
    printf("2:%d\n", pth_return_val->a);

    return 0;
}
#endif
/**/
#if 0
#include <stdio.h>
#include <pthread.h>

int Ga = 10;

int pth_fun_one(void *arg)
{
    Ga--;
    int pth_arg = *(int *)arg;
    printf("*************************\n");
    printf("this is %d pthread\n", pth_arg);
    printf("this is %d pthread\n", Ga);
    printf("*************************\n");
}
int pth_fun_two(void *arg)
{
    printf("*************************");
    printf("this is 2 pthread\n");
    printf("*************************");
}

int pth_fun_three(void *arg)
{
    printf("*************************");
    printf("this is 3 pthread\n");
    printf("*************************");
}

int pth_fun_four(void *arg)
{
    printf("*************************");
    printf("this is 4 pthread\n");
    printf("*************************");
}

int main(int argc, char *argv[])
{
    pthread_t pthread_one;
    int arg = 100;
    int cnt = 4;
    while (cnt > 0) {
        pthread_create(&pthread_one, NULL, (void *)pth_fun_one, (void *)&cnt);
        cnt--;
    }
}

#endif

#if 0
#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <asm-generic/errno.h>
int pth_fun_one(void *arg)
{

    int pth_arg = *(int *)arg;
    printf("%d\n", pth_arg);
    pthread_exit(0);
}

int main(int argv, char argc[])
{
    pthread_t pthread_one;
    int a = 10;
    if ((pthread_create(&pthread_one, NULL, (void *)pth_fun_one, &a)) != 0) {
        perror("pthread_create:");
        return 0;
    }

    pthread_join(pthread_one, NULL);
    sleep(5);
    if ((pthread_kill(pthread_one, 0)) == ESRCH) {
        printf("线程不存在\n");
    } else {
        printf("线程存在\n");
    }
    printf("%d\n", pthread_kill(pthread_one, 0));
    return 0;
}

#endif
#if 0
#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <errno.h>

int thread_id1, thread_id2;

void *function1(void *arg)
{
    thread_id1 = pthread_self();
    printf("start thread1  id = %x \n", thread_id1);
    return;
}

void *function2(void *arg)
{
    thread_id2 = pthread_self();
    printf("start thread2  id = %x \n", thread_id2);
    sleep(3);
    return;
}

int main()
{
    pthread_t tid1, tid2;

    if (-1 == pthread_create(&tid1, NULL, function1, NULL))
        printf("tid1 create fail\n");
    else
        pthread_detach(tid1);
    if (-1 == pthread_create(&tid2, NULL, function2, NULL))
        printf("tid1 create fail\n");
    else
        pthread_detach(tid2);

    sleep(1);

    int kill_ret1 = pthread_kill(tid1, 0);
    printf("kill_ret1=%d\n", kill_ret1);
    if (kill_ret1 == ESRCH) {
        printf("线程1不存在 id = %x \n", thread_id1);
    } else if (kill_ret1 == 0) {
        printf("线程1存活 id = %x \n", thread_id1);
    }

    sleep(4);
    int kill_ret2 = pthread_kill(tid2, 0);
    printf("kill_ret2=%d\n", kill_ret2);
    if (kill_ret2 == ESRCH) {
        printf("线程2不存在 id = %x \n", thread_id2);
    } else if (kill_ret2 == 0) {
        printf("线程2存活 id = %x \n", thread_id2);
    }

    return 0;
}
#endif

#if 0
#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <asm-generic/errno.h>
int pth_fun_one(void *arg)
{
    pthread_setcancelstate();
    int pth_arg = *(int *)arg;
    printf("%d\n", pth_arg);
    pthread_exit(0);
}

int main(int argv, char argc[])
{
    pthread_t pthread_one;
    int a = 10;
    if ((pthread_create(&pthread_one, NULL, (void *)pth_fun_one, &a)) != 0) {
        perror("pthread_create:");
        return 0;
    }
    pthread_cancel(pthread_one);
    // pthread_kill(pthread_one, SIGQUIT);
    sleep(5);
    a = pthread_join(pthread_one, NULL);
    if (a != 0) {
        printf("%d\n", a);
    }
    return 0;
}

#endif

#if 1
#include <stdio.h>
int main()
{
    int p = NULL;
    return 0;
    int a = 0x64;
    int b = 0x65;
    int c = 0x74;
}

#endif