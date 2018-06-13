/*************************************************
//File name:	nrf24l0.c
//File info:
//Author:		fan Li
//Date:			2018.3.24
*************************************************/

#include "nrf24l0.h"
//temp and just for DEBUG
//const uint8_t SP2_ADDRESS[EP_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x03};
const uint8_t EP_ADDRESS[EP_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x02}; //????
const uint8_t SP1_ADDRESS[SP1_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //????
extern uniNrfMess 	    nrf_Rec_Mess;
extern BOOL 	  		flag_nrf_Rec_mess;
//----------------------------------------------
void NRF24_init(void)
{
	//init GPIO & SPI in their own file
	NRF_CE_LOW();//enable nRF
	NRF_CSN_HIGH();//cancel spi1 chip choose
}
//----------------------------------------------
uint8_t NRF24_SPI2_WRByte(uint8_t txData)
{
	uint8_t rxData;
	HAL_SPI_TransmitReceive(&hspi1,&txData,&rxData,1,1000);
	//Delay_us(100);
	//HAL_SPI_TransmitReceive(&hspi1,&txData,&rxData,1,1000);
	return rxData;
}
//----------------------------------------------
uint8_t NRF24_Write_Reg(uint8_t reg,uint8_t value)
{
	uint8_t status;
	NRF_CSN_LOW();
	NRF24_SPI2_WRByte(reg);
	status = NRF24_SPI2_WRByte(value);
//	Delay_us(10);
//	NRF24_SPI2_WRByte(reg);
//	status = NRF24_SPI2_WRByte(value);
	NRF_CSN_HIGH();
	return status;
}
//----------------------------------------------
uint8_t NRF24_Read_Reg(uint8_t reg)
{
	uint8_t data,status;
	
	NRF_CSN_LOW();
	
	status = NRF24_SPI2_WRByte(reg);
	data = NRF24_SPI2_WRByte(0xFF);
//	Delay_us(10);
//	status = NRF24_SPI2_WRByte(reg);
//	data = NRF24_SPI2_WRByte(0xFF);
	NRF_CSN_HIGH();
	
	return data;
}
//----------------------------------------------
uint8_t NRF24_Write_Buffer(uint8_t reg,uint8_t* bufferPtr,uint8_t len)
{
	uint8_t rxBuf[TX_PLOAD_WIDTH];//TODO maybe consume too  many space
	uint8_t status;
	
	NRF_CSN_LOW();
	
	status = NRF24_SPI2_WRByte(reg);
	//HAL_SPI_TransmitReceive(&hspi1,bufferPtr,rxBuf,len,100);
	for(uint8_t i =0;i<len;i++){NRF24_SPI2_WRByte(*bufferPtr++);}
	
	NRF_CSN_HIGH();
	
	return status;
}
//----------------------------------------------
uint8_t NRF24_Read_Buffer(uint8_t reg,uint8_t* bufferPtr,uint8_t len)
{
	uint8_t status;
	NRF_CSN_LOW();
	
	status = NRF24_SPI2_WRByte(reg);
	while(len-- > 0)
	{
		*bufferPtr = NRF24_SPI2_WRByte(0xFF);
		bufferPtr++;
	}
	
	NRF_CSN_HIGH();
	return status;
}
//----------------------------------------------
/************************************************************************
//Func Name:	NRF24_Check
//Func Info:	check if nRF exist by wirte ,read and verify reg
//Func args:
//Func return:
//Func author:	fan Li
************************************************************************/
BOOL NRF24_Check(void)
{
	uint8_t testBuf[5] = {0x11,0x22,0x33,0x44,0x55};
	uint8_t check_out_buf[5]={0x00};
	uint8_t i;
	
	//NRF24_Write_Buffer(NRF_WRITE_REG+TX_ADDR,testBuf,5);
	//Delay_us(1000);//without delay Boom!
	NRF24_Write_Buffer(NRF_WRITE_REG+TX_ADDR,testBuf,5);
	Delay_us(1000);
	NRF24_Read_Buffer(TX_ADDR,check_out_buf,5);
	
	
	if((check_out_buf[0] == 0x11)&&\
	(check_out_buf[1] == 0x22)&&\
	(check_out_buf[2] == 0x33)&&\
	(check_out_buf[3] == 0x44)&&\
	(check_out_buf[4] == 0x55))return TRUE;

	return FALSE;
}

uint8_t NRF24_Write_Packet(uint8_t *txbuf)
{
	uint8_t status;
	NRF_CE_LOW();   
	NRF24_Write_Buffer(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);
	NRF_CE_HIGH();
	while(NRF_IRQ_READ() != GPIO_PIN_RESET);//wait for tx
	status = NRF24_Read_Reg(STATUS);
	Delay_us(1000);
	NRF24_Write_Reg(NRF_WRITE_REG + STATUS,status);
	
	if(status & MAX_TX)
	{
		NRF24_Write_Reg(FLUSH_TX,0xff);//clear TX
		return MAX_TX;
	}
	if(status & TX_OK)
	{
		//turn to rx after receive
		return 0;
	}
	return 1;
}
uint8_t NRF24_Read_Packet(uint8_t *rxbuf)
{
	uint8_t status;
	status = NRF24_Read_Reg(STATUS);
	NRF24_Write_Reg(NRF_WRITE_REG + STATUS,status);
	if(status & RX_OK)
	{
		NRF24_Read_Buffer(RD_RX_PLOAD,rxbuf,RX_PLOAD_WIDTH);
		NRF24_Write_Reg(FLUSH_RX,0xff);
		return 0;
	}
	return 1;
}

void NRF24_TxMode(void)
{
	NRF_CE_LOW();
	
	NRF24_Write_Buffer(NRF_WRITE_REG+TX_ADDR,(uint8_t*)EP_ADDRESS,EP_ADR_WIDTH);//TX addr
	NRF24_Write_Buffer(NRF_WRITE_REG+RX_ADDR_P0,(uint8_t*)EP_ADDRESS,EP_ADR_WIDTH); //RX addr for ACk
	
	NRF24_Write_Reg(NRF_WRITE_REG+EN_AA,0x01);     
	NRF24_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01); 
	NRF24_Write_Reg(NRF_WRITE_REG+SETUP_RETR,0xfa);//
	NRF24_Write_Reg(NRF_WRITE_REG+RF_CH,50);       //RF channel 40
	NRF24_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f);  //0f:2M 27:250k
	NRF24_Write_Reg(NRF_WRITE_REG+CONFIG,0x0e);    
	
	NRF_CE_HIGH();
}

void NRF24_RxMode(void)
{
	NRF_CE_LOW();
	
	NRF24_Write_Buffer(NRF_WRITE_REG+RX_ADDR_P1,(uint8_t*)SP1_ADDRESS,SP1_ADR_WIDTH); //RX addr
	
	NRF24_Write_Reg(NRF_WRITE_REG+EN_AA,0x03);     
	NRF24_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x03); 
	NRF24_Write_Reg(NRF_WRITE_REG+RX_PW_P1,RX_PLOAD_WIDTH);
	NRF24_Write_Reg(NRF_WRITE_REG+RF_CH,50);       //RF channel 40
	NRF24_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f);  
	NRF24_Write_Reg(NRF_WRITE_REG+CONFIG,0x0f);    
	
	NRF_CE_HIGH();
}
static BOOL flag_wait_rec;
void NRF24_send_cmd(uint8_t sub_id,uint8_t cmd_type)
{
	NRF24_TxMode();
	uniNrfMess mess;
	for(int i = 0;i < MESS_DATA_LENG;i++)
	{
		mess.message_Buffer[i] = 0x0;
			
	}
	mess.nrfMess.startByte = START_BYTE;
	mess.nrfMess.endByte = END_BYTE;
	mess.nrfMess.user_id[0] = sub_id;
	mess.nrfMess.dir_Type = (DIR_SEND << 4) + cmd_type;
	NRF24_Write_Packet(mess.message_Buffer);
	NRF24_RxMode();
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	
	//NRF24_read_data(0,0);
	if(GPIO_Pin == GPIO_PIN_2)
	{
		LED1_TOGGLE();
		uint8_t status;
		status = NRF24_Read_Reg(STATUS);
		//printf("2.4g:status:%X\n",status);
		//NRF24_Write_Reg(NRF_WRITE_REG + STATUS,status);
		if(status & 0x40)
		{
			printf("2.4g:rec\n");
			NRF24_Read_Packet(nrf_Rec_Mess.message_Buffer);
			//NRF24_read_data(0,0);
			flag_nrf_Rec_mess = TRUE;
		}
		else if(status & TX_OK)
		{
			//send 
			printf("2.4g:send_ok\n");
		}	
		else if(status & MAX_TX)
		{
			//wrong
			printf("2.4g:max_rt\n");
			
		}
		else
		{
			printf("2.4g:None\n");
		}
		//printf("2.4g:FIFO status:%X",NRF24_Read_Reg(NRF_FIFO_STATUS));
		
	}
	
}


uint32_t NRF24_read_data(uint8_t sub_id,uint8_t data_type)
{
	//uniNrfMess mess;
	if(!flag_nrf_Rec_mess)
	{
		flag_nrf_Rec_mess = TRUE;
		NRF24_Read_Packet(nrf_Rec_Mess.message_Buffer);
		
	}
}

void NRF24_pwdown()
{
	NRF_CSN_LOW();
	
	Delay_us(200);
	//NRF24_Write_Reg(NRF_WRITE_REG+CONFIG,0x02);    
	
	NRF_CSN_HIGH();
}

void NRF24_rec_mess()
{
//check nrf Rec
	if(flag_nrf_Rec_mess)
	{
		if(nrf_Rec_Mess.nrfMess.startByte == START_BYTE 
			&& nrf_Rec_Mess.nrfMess.endByte == END_BYTE)
		{
			sensor_data_now.data_sp1_temp = (nrf_Rec_Mess.nrfMess.data[0] << 8) + nrf_Rec_Mess.nrfMess.data[1];
			sensor_data_now.data_sp1_humi = (nrf_Rec_Mess.nrfMess.data[2] << 8) + nrf_Rec_Mess.nrfMess.data[3];
		}
		flag_nrf_Rec_mess = FALSE;
	}
}
