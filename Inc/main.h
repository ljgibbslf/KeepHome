/**
  ******************************************************************************
  * File Name          : main.hpp
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Includes ------------------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define DHT12_SCL_Pin GPIO_PIN_2
#define DHT12_SCL_GPIO_Port GPIOE
#define CAM_RST_Pin GPIO_PIN_3
#define CAM_RST_GPIO_Port GPIOE
#define Wifi_Ctl_Pin GPIO_PIN_0
#define Wifi_Ctl_GPIO_Port GPIOC
#define LED1_Pin GPIO_PIN_2
#define LED1_GPIO_Port GPIOC
#define LED2_Pin GPIO_PIN_3
#define LED2_GPIO_Port GPIOC
#define Inf_Pin GPIO_PIN_0
#define Inf_GPIO_Port GPIOA
#define CH4_ADC_Pin GPIO_PIN_7
#define CH4_ADC_GPIO_Port GPIOA
#define LCD_RST_Pin GPIO_PIN_5
#define LCD_RST_GPIO_Port GPIOC
#define TOUCH_SDA_Pin GPIO_PIN_0
#define TOUCH_SDA_GPIO_Port GPIOB
#define TOUCH_SCL_Pin GPIO_PIN_1
#define TOUCH_SCL_GPIO_Port GPIOB
#define SPI2_CS_Pin GPIO_PIN_12
#define SPI2_CS_GPIO_Port GPIOB
#define FSMC_LCD_RS_Pin GPIO_PIN_11
#define FSMC_LCD_RS_GPIO_Port GPIOD
#define CH4_CTL_Pin GPIO_PIN_12
#define CH4_CTL_GPIO_Port GPIOD
#define PM25_CTL_Pin GPIO_PIN_13
#define PM25_CTL_GPIO_Port GPIOD
#define CAM_XCLK_Pin GPIO_PIN_8
#define CAM_XCLK_GPIO_Port GPIOA
#define LCD_INT_Pin GPIO_PIN_11
#define LCD_INT_GPIO_Port GPIOA
#define CAM_CTL_Pin GPIO_PIN_12
#define CAM_CTL_GPIO_Port GPIOA
#define LCD_PWM_Pin GPIO_PIN_15
#define LCD_PWM_GPIO_Port GPIOA
#define NRF_IRQ_Pin GPIO_PIN_2
#define NRF_IRQ_GPIO_Port GPIOD
#define NRF_IRQ_EXTI_IRQn EXTI2_IRQn
#define CAM_SIOC_Pin GPIO_PIN_3
#define CAM_SIOC_GPIO_Port GPIOD
#define FSMC_LCD_RD_Pin GPIO_PIN_4
#define FSMC_LCD_RD_GPIO_Port GPIOD
#define FSMC_LCD_WR_Pin GPIO_PIN_5
#define FSMC_LCD_WR_GPIO_Port GPIOD
#define CAM_SIOD_Pin GPIO_PIN_6
#define CAM_SIOD_GPIO_Port GPIOD
#define FSMC_LCD_CS_Pin GPIO_PIN_7
#define FSMC_LCD_CS_GPIO_Port GPIOD
#define NRF_CS_Pin GPIO_PIN_8
#define NRF_CS_GPIO_Port GPIOB
#define Buzzer_Pin GPIO_PIN_9
#define Buzzer_GPIO_Port GPIOB
#define NRF_CE_Pin GPIO_PIN_0
#define NRF_CE_GPIO_Port GPIOE
#define DHT12_SDA_Pin GPIO_PIN_1
#define DHT12_SDA_GPIO_Port GPIOE

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
