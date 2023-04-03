/***********************************************************
 *File name :20230323_test.c
 *Author name : xiongyansong
 *Email address : sanxisui@gmail.com
 *Create time : 2023-03-23 20:40:42
 *Description: 抄袭了一下，状态机里面的宏定义
 ***********************************************************/

#include <stdio.h>
#include <string.h>
#define my_printf(format_, ...)         \
    do {                                \
        printf(format_, ##__VA_ARGS__); \
    } while (0)

// int main(int argc, const char argv[])
// {
//     my_printf("hello,%s,%s", "world", "word");
// }
typedef enum {
    ZERO,
    ONE,
    TWO,
    THREE
} hello_t;
typedef hello_t (*one)(int a, char b[]);

hello_t two(int a, char b[])
{
    return ZERO;
}
int main()
{
    int a = 1;
    char b[5] = {0};
    int c = 0;
    c = two(a, b);
    printf("%d", c);
}