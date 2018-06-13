#ifndef __OV7670_H__
#define __OV7670_H__

#include "common.h"
#include "sccb.h"
//----------------------------------------------
#define     OV7670_RST_PIN                       GPIO_PIN_3
#define     OV7670_RST_GPIO_PORT                 GPIOE
#define     OV7670_RST_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOE_CLK_ENABLE()
#define     OV7670_RST_ON()                      HAL_GPIO_WritePin(OV7670_RST_GPIO_PORT,OV7670_RST_PIN, GPIO_PIN_SET)
#define     OV7670_RST_OFF()                     HAL_GPIO_WritePin(OV7670_RST_GPIO_PORT,OV7670_RST_PIN, GPIO_PIN_RESET)

#define     OV7670_CTL_PIN                       GPIO_PIN_12
#define     OV7670_CTL_GPIO_PORT                 GPIOA
#define     OV7670_CTL_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOA_CLK_ENABLE()
#define     OV7670_CTL_ON()                      HAL_GPIO_WritePin(OV7670_CTL_GPIO_PORT,OV7670_CTL_PIN, GPIO_PIN_SET)
#define     OV7670_CTL_OFF()                     HAL_GPIO_WritePin(OV7670_CTL_GPIO_PORT,OV7670_CTL_PIN, GPIO_PIN_RESET)
//----------------------------------------------

uint8_t Wr_OV7670_Reg(uint8_t reg,uint8_t val);
uint8_t Rd_OV7670_Reg(uint8_t reg,uint8_t * val);
void OV7670_Init(void);
void OV7670_config_win(uint16_t startx,uint16_t starty,uint16_t width,uint16_t height);
void OV7670_set_reg();
void set_qvga(void);
#endif