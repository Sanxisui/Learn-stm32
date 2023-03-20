#include <stdio.h>

int *func()
{
    int i = 10;
    return &i;
}

int main()
{
    //*p不变，也就是指向的内容不变
    const int *p;
    // 指针指向的地址不变
    int *const p;
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    printf("this is c\n");
    int *p = func();
    printf("");
    printf("%d\n", a);
    return 0;
}