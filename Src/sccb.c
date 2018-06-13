/*************************************************
//File name:	sccb.c
//File info:    io on SCCB protocl
//Author:		fan Li
//Date:
*************************************************/

#include "sccb.h"

void  SCCB_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
    
	SCCB_SDA_GPIO_CLK_ENABLE();
    SCCB_SCL_GPIO_CLK_ENABLE();
    
	GPIO_InitStruct.Pin   = SCCB_SCL_PIN | SCCB_SDA_PIN;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;
    HAL_GPIO_Init(SCCB_SCL_GPIOx, &GPIO_InitStruct);
    
    SCCB_SCL_OUT(1);
    SCCB_SDA_OUT(1);
    
    SCCB_Stop();
}
							
void  SCCB_Start(void)
{

    SCCB_SDA_OUT(1);
    SCCB_SCL_OUT(1);

    SCCB_SDA_OUT(0);
    Delay_us(15);
    SCCB_SCL_OUT(0); 
}
void  SCCB_Stop(void)
{
	//sda:out
    SCCB_SDA_OUT(0);
	Delay_us(15);
    SCCB_SCL_OUT(1);
    Delay_us(15);
	SCCB_SDA_OUT(1);
	Delay_us(15);
}
void  SCCB_Ack(void)
{
	SCCB_SCL_OUT(0);
	//sda:out
    SCCB_SDA_OUT(0);
    Delay_us(15);
    SCCB_SCL_OUT(1);
    Delay_us(15);
    SCCB_SCL_OUT(0);
}
void  SCCB_NoAck(void)
{
	Delay_us(15);
	SCCB_SCL_OUT(1);
	//sda:out
    SCCB_SDA_OUT(1);
    Delay_us(15);
    SCCB_SCL_OUT(0);
    Delay_us(15);
    SCCB_SDA_OUT(0); 
	Delay_us(15);
}

uint8_t  SCCB_Send_Byte(uint8_t dat)
{
	 __IO uint8_t i;
	
	//sda:out
    SCCB_SCL_OUT(0);

    for(i=0; i<8; i++)
    {   
		
        if(dat & 0x80) { SCCB_SDA_OUT(1); }
        else           { SCCB_SDA_OUT(0); }
		dat <<= 1;
        Delay_us(15);
        SCCB_SCL_OUT(1);    
        Delay_us(15); 
		SCCB_SCL_OUT(0);
          
    }
	Delay_us(15); 
	SCCB_SCL_OUT(1);
	Delay_us(15);
	if(SCCB_SDA_READ())
	{
		SCCB_SCL_OUT(0);
		return 1;
	}
	else
	{
		SCCB_SCL_OUT(0);
		return 0;
	}
	
}

uint8_t SCCB_Read_Byte()
{
	uint8_t  i,receive=0;
    
    SCCB_SDA_OUT(1);
	//sda:in
	
    for(i=0;i<8;i++ )
    {
        
        Delay_us(15);
        SCCB_SCL_OUT(1);
        receive<<=1;
		//Delay_us(10);//add delay with dht12
        if(SCCB_SDA_READ()) { receive++; } 
		Delay_us(15);
		SCCB_SCL_OUT(0); 
    }    
	//SCCB_SCL_OUT(1);
    return receive;
}
uint8_t SCCB_WaitAck(void)
{
	__IO uint16_t t = 0;
	SCCB_SCL_OUT(0);
    SCCB_SDA_OUT(1);
	//sda:in
    Delay_us(15);
    SCCB_SCL_OUT(1);
    Delay_us(15);
    
    while(SCCB_SDA_READ())//wait untill sda->0
    {
        t++;
        if(t>300)
        {
            SCCB_Stop();
            //return 1;
        }   
    }

    SCCB_SCL_OUT(0);
	Delay_us(10);
    return 0; 
}