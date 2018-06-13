#include  "led.h"

void  LED_GPIO_init(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;
    // LED1的引脚初始化
    LED1_GPIO_CLK_ENABLE();
    GPIO_InitStruct.Pin  = LED1_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStruct);
    LED1_OFF();
    
    // LED2,LED3,LED4 的引脚初始化
    LED2_GPIO_CLK_ENABLE();
    GPIO_InitStruct.Pin  = LED2_PIN ;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStruct);
    LED2_ON();
	LED1_ON();
    
}


