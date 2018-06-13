#ifndef __NRF24l0_H__
#define __NRF24l0_H__
//----------------------------------------------
#include "common.h"
#include  "spi.h"
#include  "usart.h"
#include  "led.h"
//----------------------------------------------
#define 	START_BYTE			0x10
#define 	END_BYTE			0x20
#define 	MESS_LENG			16  //16 BYTE
#define		MESS_ID_LENG		3
#define		MESS_FLAG_LENG		5//5
#define		MESS_DATA_LENG		(MESS_LENG - MESS_FLAG_LENG - MESS_ID_LENG)
#define		DIR_SEND			0x1

typedef struct  
{
	uint8_t startByte;
	uint8_t	dir_Type;
	uint8_t	user_id[MESS_ID_LENG];
	uint8_t	data[MESS_DATA_LENG];
	uint8_t CRCByte;
	uint8_t res;
	uint8_t	endByte;
	BOOL	is_proc;
}struNrfMess;


typedef union
{
	uint8_t	message_Buffer[MESS_LENG];
	struNrfMess nrfMess;
}uniNrfMess;

//----------------------------------------------
#define NRF_READ_REG    0x00  
#define NRF_WRITE_REG   0x20  
#define RD_RX_PLOAD     0x61  
#define WR_TX_PLOAD     0xA0  
#define FLUSH_TX        0xE1  
#define FLUSH_RX        0xE2  
#define REUSE_TX_PL     0xE3  
#define NOP             0xFF  

#define CONFIG          0x00  
                              
#define EN_AA           0x01  
#define EN_RXADDR       0x02  
#define SETUP_AW        0x03  
#define SETUP_RETR      0x04  
#define RF_CH           0x05  
#define RF_SETUP        0x06  
#define STATUS          0x07  
                              
#define MAX_TX  		0x10  
#define TX_OK   		0x20  
#define RX_OK   		0x40  

#define OBSERVE_TX      0x08  
#define CD              0x09  
#define RX_ADDR_P0      0x0A  
#define RX_ADDR_P1      0x0B  
#define RX_ADDR_P2      0x0C  
#define RX_ADDR_P3      0x0D  
#define RX_ADDR_P4      0x0E  
#define RX_ADDR_P5      0x0F  
#define TX_ADDR         0x10  
#define RX_PW_P0        0x11  
#define RX_PW_P1        0x12  
#define RX_PW_P2        0x13  
#define RX_PW_P3        0x14  
#define RX_PW_P4        0x15  
#define RX_PW_P5        0x16  
#define NRF_FIFO_STATUS 0x17  

//----------------------------------------------

#define EP_ADR_WIDTH    5   	
#define SP1_ADR_WIDTH    5   	
#define TX_PLOAD_WIDTH  16  	
#define RX_PLOAD_WIDTH  16 
//----------------------------------------------
#define NRF_CE_PIN                       GPIO_PIN_0
#define NRF_CE_GPIO_PORT                 GPIOE
#define NRF_CE_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOE_CLK_ENABLE()
#define NRF_CE_HIGH()                    HAL_GPIO_WritePin(NRF_CE_GPIO_PORT, NRF_CE_PIN, GPIO_PIN_SET)
#define NRF_CE_LOW()                     HAL_GPIO_WritePin(NRF_CE_GPIO_PORT, NRF_CE_PIN, GPIO_PIN_RESET)
//----------------------------------------------
#define NRF_CSN_PIN                       GPIO_PIN_8
#define NRF_CSN_GPIO_PORT                 GPIOB
#define NRF_CSN_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOB_CLK_ENABLE()
#define NRF_CSN_HIGH()                    HAL_GPIO_WritePin(NRF_CSN_GPIO_PORT, NRF_CSN_PIN, GPIO_PIN_SET)
#define NRF_CSN_LOW()                     HAL_GPIO_WritePin(NRF_CSN_GPIO_PORT, NRF_CSN_PIN, GPIO_PIN_RESET)
//----------------------------------------------
#define NRF_IRQ_PIN                       GPIO_PIN_2
#define NRF_IRQ_GPIO_PORT                 GPIOD
#define NRF_IRQ_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOD_CLK_ENABLE()
#define NRF_IRQ_READ()         			  HAL_GPIO_ReadPin(NRF_IRQ_GPIO_PORT, NRF_IRQ_PIN)
//----------------------------------------------

void NRF24_init(void);
void NRF24_TxMode(void);
void NRF24_RxMode(void);
void NRF24_pwdown(void);
uint8_t NRF24_Write_Reg(uint8_t reg,uint8_t data);
uint8_t NRF24_Read_Reg(uint8_t reg);
uint8_t NRF24_Write_Buffer(uint8_t reg,uint8_t* bufferPtr,uint8_t num);
uint8_t NRF24_Read_Buffer(uint8_t reg,uint8_t* bufferPtr,uint8_t num);
uint8_t NRF24_Write_Packet(uint8_t *ptr);
uint8_t NRF24_Read_Packet(uint8_t *ptr);
BOOL NRF24_Check(void);
uint8_t NRF24_SPI_WRByte(uint8_t txData);
void NRF24_send_cmd(uint8_t sub_id,uint8_t cmd_type);
uint32_t NRF24_read_data(uint8_t sub_id,uint8_t data_type);
void NRF24_rec_mess();
//----------------------------------------------

#endif