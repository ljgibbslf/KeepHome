/*************************************************
//File name:	sensor.h
//File info:	
//Author:		fan Li
//Date:
*************************************************/
#include "common.h"
#include "adc.h"
#include "usart.h"
#include "dht12.h"
//----------------------------------------------
#define CH4_ALR_VAL	1200

//USART3 
extern uint8_t   UPm25_Rec_Buffer[PM25_DATA_LENGTH*PM25_BUFFER_NUM];
                    // 接收指针

//USART4 
extern uint8_t   UCH2O_Rec_Buffer[CH2O_DATA_LENGTH*CH2O_BUFFER_NUM];
                  // 接收指针
				  
extern uint16_t  ADC1_Value[SIZEofADC1];

extern struData		sensor_data_now;		// 当前传感器数据


//----------------------------------------------
#define  PM25_CE_PIN                       GPIO_PIN_13
#define  PM25_CE_GPIO_PORT                 GPIOD
#define  PM25_CE_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOD_CLK_ENABLE()
#define  PM25_CE_ON()                      HAL_GPIO_WritePin(PM25_CE_GPIO_PORT, PM25_CE_PIN, GPIO_PIN_SET)
#define  PM25_CE_OFF()                     HAL_GPIO_WritePin(PM25_CE_GPIO_PORT, PM25_CE_PIN, GPIO_PIN_RESET)


#define  CH4_CE_PIN                       GPIO_PIN_12
#define  CH4_CE_GPIO_PORT                 GPIOD
#define  CH4_CE_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOD_CLK_ENABLE()
#define  CH4_CE_ON()                      HAL_GPIO_WritePin(CH4_CE_GPIO_PORT, CH4_CE_PIN, GPIO_PIN_SET)
#define  CH4_CE_OFF()                     HAL_GPIO_WritePin(CH4_CE_GPIO_PORT, CH4_CE_PIN, GPIO_PIN_RESET)
#define  CH4_CE_TOGGLE()                  HAL_GPIO_TogglePin(CH4_CE_GPIO_PORT, CH4_CE_PIN) 

#define 	INF_GPIOx       GPIOA
#define		INF_PIN			GPIO_PIN_0
#define     PM25_Rec_Buffer	UPm25_Rec_Buffer
#define     CH2O_Rec_Buffer	UCH2O_Rec_Buffer

#define  HCHO_H 4
#define  HCHO_L 5
//----------------------------------------------
#define SAMPLE_NUM	3
void sensor_data_proc();
void cho_avg();
void pm25_avg();
void ch4_avg();
void sensor_init();
void sensor_deinit();
void ch4_sensor_onoff();
void ch4_sensor_warn();
uint8_t Read_Inf();