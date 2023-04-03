/***********************************************************
File name : hash_leetcode.c
Author name : xiongyansong
Email address : sanxisui@gmail.com
Create time : 2023-03-21 14:39:21
Description : 尝试学习hash查找 /看过c语言版本的了，现在用go语言写一个！
              变味了，在这里尝试c宏定义函数来了
***********************************************************/
#include <stdio.h>
// #define find_array_member(target, array)         \
//     do {                                         \
//         for (int i = 0; i < sizeof array; i++) { \
//             if (array[i] == target) {            \
//                 return i;                        \
//             }                                    \
//         }
// }
// while (0)

// typedef struct  {
//     void *array;
//     // extern len;
//     int cap
// }slice;

// func()
// {
//     return 1;
// }
int main()
{
    char a = 'c';

    printf("%ld", sizeof 77);

    int array[4] = {0, 1, 2, 3};
    int b = func();
    // int c = find_array_member(3, array);
    printf("c:%d\n", b);
}