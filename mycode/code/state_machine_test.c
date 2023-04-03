/***********************************************************
File name : hash_leetcode.c
Author name : xiongyansong
Email address : sanxisui@gmail.com
Create time : 2023-03-22 16:23:17
Description : 状态机
***********************************************************/
#include <stdio.h>

// 状态
typedef enum {
    GOING = 0,
    STOPPING = 1,
    TURN_LEFT = 2,
    TURN_RIGHT = 3,
    GO_BACK = 4
} status_t;
// 错误
typedef enum {
    NO_CONNECT = -1
} error_t;
// 事件
typedef enum {
    NO_EVENT_HAPPEN = 0,
    RX_CMD = 1
} event_t;
// 当前状态转换
typedef struct
{
    status_t status_now;
    status_t status_next;
    void *(*fp)(void);
    event_t event;
} statetransform_t;

int goning()
{
}

int stopping()
{
}
int turn_left()
{
}
int turn_right()
{
}

int main()
{
}