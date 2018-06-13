#ifndef DHT12_H
#define DHT12_H

#include "stm32f4xx_hal.h"
#include "usart.h"
#include  "common.h"
//  DHT12Ð¾Æ¬Çý¶¯
//////////////////////////////////////////////////////////////////////////////////
#define     DHT12_SCL_PIN                   GPIO_PIN_2
#define     DHT12_SCL_GPIOx                 GPIOE
#define     DHT12_SCL_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOE_CLK_ENABLE()

#define     DHT12_SDA_PIN                   GPIO_PIN_1
#define     DHT12_SDA_GPIOx                 GPIOE
#define     DHT12_SDA_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOE_CLK_ENABLE()


#define     I2C2_SCL_OUT(x)     if(x){ HAL_GPIO_WritePin(DHT12_SCL_GPIOx, DHT12_SCL_PIN, GPIO_PIN_SET);   } \
                                else { HAL_GPIO_WritePin(DHT12_SCL_GPIOx, DHT12_SCL_PIN, GPIO_PIN_RESET); }

#define     I2C2_SDA_OUT(x)     if(x){ HAL_GPIO_WritePin(DHT12_SDA_GPIOx, DHT12_SDA_PIN, GPIO_PIN_SET);   } \
                                else { HAL_GPIO_WritePin(DHT12_SDA_GPIOx, DHT12_SDA_PIN, GPIO_PIN_RESET); }

#define     I2C2_SDA_READ()       HAL_GPIO_ReadPin(DHT12_SDA_GPIOx,DHT12_SDA_PIN)    // ¶ÁSDA¿ÚÏß×´Ì¬ 
                                
#define     NOP()  __ASM("NOP")

#define     DHT12_ADDR         0xb8
#define     DHT12_READ 		   0xb9
//////////////////////////////////////////////////////////////////////////////////

void  DHT12_I2C_GPIO_init(void);
void  I2C2_SDA_In(void);
void  I2C2_SDA_Out(void);								
								
void  I2C2_Start(void);
void  I2C2_Stop(void);
void  I2C2_Ack(void);
void  I2C2_NoAck(void);

void  I2C2_Send_Byte(uint8_t dat);
uint8_t I2C2_Read_Byte(uint8_t ack);
uint8_t I2C2_WaitAck(void);

void  I2C2_Delay_us(uint16_t cnt);
								
void DHT12_Read_Data(struData *);
#endif