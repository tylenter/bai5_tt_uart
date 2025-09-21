#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "string.h"
#include "misc.h"

#define LED GPIO_Pin_5
#define TX GPIO_Pin_9
#define RX GPIO_Pin_10

 char command[16];
 int idx = 0;
 int ready = 0;

void GPIO_Config(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    GPIO_InitTypeDef g;

    g.GPIO_Pin = LED;
    g.GPIO_Mode = GPIO_Mode_Out_PP;
    g.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &g);

    g.GPIO_Pin = TX;
    g.GPIO_Mode = GPIO_Mode_AF_PP;
    g.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &g);

    g.GPIO_Pin = RX;
    g.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &g);
}

void UART_Config(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    USART_InitTypeDef usart;
    USART_StructInit(&usart);

    usart.USART_BaudRate = 115200;
    usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    usart.USART_Parity = USART_Parity_No;
    usart.USART_WordLength = USART_WordLength_8b;
    usart.USART_StopBits = USART_StopBits_1;
    usart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART1, &usart);

    NVIC_InitTypeDef nvic;
    nvic.NVIC_IRQChannel = USART1_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 0;
    nvic.NVIC_IRQChannelSubPriority = 0;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART1, ENABLE);
}

void Print_Char(char c)
{
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    USART_SendData(USART1, (uint16_t)c);
}

void Print_String(char *s)
{
    while (*s)
    {
        Print_Char(*s++);
    }
}

void USART1_IRQHandler(void)
{
    if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
    {
        char c = (char)USART_ReceiveData(USART1);
        if (c == '\n')
        {
            command[idx] = '\0';
            ready = 1;
            Print_String("\n\r");
        }
        else if (c == '\r')
        {
        }
        else
        {
            if(idx < 16){
				command[idx++] = c;
				Print_Char(c);
			}
        }
    }
}

int main(void)
{
    GPIO_Config();
    UART_Config();
    GPIO_ResetBits(GPIOA, LED);
    Print_String("Hello FROM STM32 !\r\n");
    while (1)
    {
        if (ready)
        {
            if (strcmp(command, "ON") == 0)
            {
                GPIO_SetBits(GPIOA, LED);
                Print_String("LED ON\r\n");
            }
            else if (strcmp(command, "OFF") == 0)
            {
                GPIO_ResetBits(GPIOA, LED);
                Print_String("LED OFF\r\n");
            }
            else
            {
                Print_String("Invalid command\r\n");
            }
            ready = 0;
            idx = 0;
            memset(command, 0, 16);

        }
    }
}
