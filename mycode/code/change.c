#if 0
#include <stdio.h>

int main(int argc, char *argv)
{
    char a, ch;
    FILE *fp = fopen("hello.txt", "r");
    if (fp == NULL) {
        perror("Error1");
        return -1;
    }
    // printf("%p\n", fp);
    ch = fgetc(fp);
    if (a == -1) {
        perror("Errora3");
        return -1;
    }
    printf("1%c\n", fgetc(fp));
    // FILE *fp1 = fp;
    FILE *fp1 = fopen("hello.txt", "r");
    if (fp1 == NULL) {
        perror("Error2");
        return -1;
    }

    a = fgetc(fp1);
    if (a == -1) {
        perror("Errora3");
        return -1;
    }
    printf("2%c\n", fgetc(fp1));
    printf("%d\n", a + '0');
    printf("%p\n", fp1);
    // fclose(fp);
    return 0;
}

#endif