/***********************************************************
 *File name :20230325_test.c
 *Author name : xiongyansong
 *Email address : sanxisui@gmail.com
 *Create time : 2023-03-25 11:24:26
 *Description:
 ***********************************************************/

#include <stdio.h>
#define QS_FUN_DICTIONARY(fun_) ((void)0)

int func_test()
{
    printf("hello\n");
    return 0;
}
int main()
{
    QS_FUN_DICTIONARY(&func_test);
    return 0;
}