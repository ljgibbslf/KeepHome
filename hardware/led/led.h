#ifndef  __LED_H__
#define  __LED_H__

#include "stm32f4xx_hal.h"

////////////////////////////////////////////////////////////
#define  LED1_PIN                       GPIO_PIN_2
#define  LED1_GPIO_PORT                 GPIOC
#define  LED1_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOC_CLK_ENABLE()
#define  LED1_ON()                      HAL_GPIO_WritePin(LED1_GPIO_PORT, LED1_PIN, GPIO_PIN_SET)
#define  LED1_OFF()                     HAL_GPIO_WritePin(LED1_GPIO_PORT, LED1_PIN, GPIO_PIN_RESET)
#define  LED1_TOGGLE()                  HAL_GPIO_TogglePin(LED1_GPIO_PORT, LED1_PIN) 

#define  LED2_PIN                       GPIO_PIN_3
#define  LED2_GPIO_PORT                 GPIOC
#define  LED2_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOF_CLK_ENABLE()
#define  LED2_ON()                      HAL_GPIO_WritePin(LED2_GPIO_PORT, LED2_PIN, GPIO_PIN_SET)
#define  LED2_OFF()                     HAL_GPIO_WritePin(LED2_GPIO_PORT, LED2_PIN, GPIO_PIN_RESET)
#define  LED2_TOGGLE()                  HAL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN)


////////////////////////////////////////////////////////////

void  LED_GPIO_init(void);
    
#endif

