#ifndef __SWIMMPOOL_H_
#define __SWIMMPOOL_H_
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "list.h"

// 执行队列
typedef struct
{
    pthread_t thread_id;
    struct list_head mylist;
} pthread_queue_t;

// 任务队列
typedef struct
{
    void (*func)(void *job);
    void *user_data;
    struct list_head mylist;
} target_queue_t;
// 管理组件
typedef struct
{
    pthread_queue_t *worker;
    target_queue_t *job;

    pthread_cond_t job_cond;
    pthread_mutex_t job_mutex;
} manager_t;

#endif