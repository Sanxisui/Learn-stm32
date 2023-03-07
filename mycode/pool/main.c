#if 0
#include "swimmpool.h"

int main(int argc, char *argv)
{
}

#endif

#if 1
#include "stm32f10x.h"
#include <stdio.h>
#include <string.h>

#define MOTOR1_FORWARD 0x01
#define MOTOR1_BACKWARD 0x02
#define MOTOR1_STOP 0x03
#define MOTOR2_FORWARD 0x04
#define MOTOR2_BACKWARD 0x05
#define MOTOR2_STOP 0x06

USART_InitTypeDef USART_InitStructure;
TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
TIM_OCInitTypeDef TIM_OCInitStruct;

void USART1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    /* USART1_TX */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* USART1_RX */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* USART1 configuration */
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);
}

void USART1_SendString(char *str)
{
    while (*str) {
        USART_SendData(USART1, *str++);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
            ;
    }
}

uint8_t motor1_state = MOTOR1_STOP;
uint8_t motor2_state = MOTOR2_STOP;

void motor1_init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    TIM_TimeBaseInitStruct.TIM_Period = 999;       // PWM周期为1ms
    TIM_TimeBaseInitStruct.TIM_Prescaler = 72 - 1; // PWM时钟频率为72MHz
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);

    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_Pulse = 0;
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OC1Init(TIM3, &TIM_OCInitStruct);
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

    TIM_OC2Init(TIM3, &TIM_OCInitStruct);
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

    TIM_Cmd(TIM3, ENABLE);
}

void motor2_init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    TIM_TimeBaseInitStruct.TIM_Period = 999;       // PWM周期为1ms
    TIM_TimeBaseInitStruct.TIM_Prescaler = 72 - 1; // PWM时钟频率为72MHz
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);

    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_Pulse = 0;
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OC1Init(TIM2, &TIM_OCInitStruct);
    TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);

    TIM_OC2Init(TIM2, &TIM_OCInitStruct);
    TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);

    TIM_OC3Init(TIM2, &TIM_OCInitStruct);
    TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);

    TIM_OC4Init(TIM2, &TIM_OCInitStruct);
    TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);

    TIM_Cmd(TIM2, ENABLE);
}

void motor1_forward(void)
{
    TIM_SetCompare1(TIM3, 800); // 占空比为80%
    TIM_SetCompare2(TIM3, 0);   // 占空比为0%
}

void motor1_backward(void)
{
    TIM_SetCompare1(TIM3, 0);   // 占空比为0%
    TIM_SetCompare2(TIM3, 800); // 占空比为80%
}

void motor1_stop(void)
{
    TIM_SetCompare1(TIM3, 0); // 占空比为0%
    TIM_SetCompare2(TIM3, 0); // 占空比为0%
}

void motor2_forward(void)
{
    GPIO_ResetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2); // IN1 = 1, IN2 = 0
    GPIO_SetBits(GPIOA, GPIO_Pin_3 | GPIO_Pin_4);   // IN3 = 1, IN4 = 1
    TIM_SetCompare1(TIM2, 800);                     // 占空比为80%
    TIM_SetCompare2(TIM2, 0);                       // 占空比为0%
    TIM_SetCompare3(TIM2, 800);                     // 占空比为80%
    TIM_SetCompare4(TIM2, 0);                       // 占空比为0%
}

void motor2_backward(void)
{
    GPIO_ResetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2); // IN1 = 0, IN2 = 1
    GPIO_SetBits(GPIOA, GPIO_Pin_3 | GPIO_Pin_4);   // IN3 = 1, IN4 = 1
    TIM_SetCompare1(TIM2, 0);                       // 占空比为0%
    TIM_SetCompare2(TIM2, 800);                     // 占空比为80%
    TIM_SetCompare3(TIM2, 0);                       // 占空比为0%
    TIM_SetCompare4(TIM2, 800);                     // 占空比为80%
}

void motor2_stop(void)
{
    GPIO_ResetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4); // IN1 = 0, IN2 = 0, IN3 = 0, IN4 = 0
    TIM_SetCompare1(TIM2, 0);                                                 // 占空比为0%
    TIM_SetCompare2(TIM2, 0);                                                 // 占空比为0%
    TIM_SetCompare3(TIM2, 0);                                                 // 占空比为0%
    TIM_SetCompare4(TIM2, 0);                                                 // 占空比为0%
}

int main(void)
{
    motor1_init();
    motor2_init();
    char wifi_rx_buf[1024] = {0};

    while (1) {
        // 等待wifi模块收到命令并返回
        while (!strstr(wifi_rx_buf, "motor1") && !strstr(wifi_rx_buf, "motor2")) {
            uart_receive_string(wifi_rx_buf);
        }

        // 解析命令并执行对应的动作
        if (strstr(wifi_rx_buf, "motor1_forward")) {
            motor1_forward();
        } else if (strstr(wifi_rx_buf, "motor1_backward")) {
            motor1_backward();
        } else if (strstr(wifi_rx_buf, "motor1_stop")) {
            motor1_stop();
        } else if (strstr(wifi_rx_buf, "motor2_forward")) {
            motor2_forward();
        } else if (strstr(wifi_rx_buf, "motor2_backward")) {
            motor2_backward();
        } else if (strstr(wifi_rx_buf, "motor2_stop")) {
            motor2_stop();
        }

        memset(wifi_rx_buf, 0, sizeof(wifi_rx_buf)); // 清空接收缓存
    }
}
#endif