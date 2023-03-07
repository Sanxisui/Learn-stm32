#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int main(int argv, char *argc)
{

    pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
    // printf("", mutex1.__align);
    // printf("%s\n", mutex1.__data);
    // printf("%ld\n", mutex1.__size);
    pthread_t one;
    one = pthread_self();
    printf("%ld\n", one);
    while (1) {
    }

    return 0;
}