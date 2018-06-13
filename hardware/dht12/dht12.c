/*
*dht12.c dht12 with io_i2c
*/

#include "dht12.h"

void  DHT12_I2C_GPIO_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
    
    DHT12_SCL_GPIO_CLK_ENABLE();
	DHT12_SDA_GPIO_CLK_ENABLE();
    GPIO_InitStruct.Pin   = DHT12_SCL_PIN | DHT12_SDA_PIN;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;
    HAL_GPIO_Init(DHT12_SCL_GPIOx, &GPIO_InitStruct);
    
    I2C2_SCL_OUT(1);
    I2C2_SDA_OUT(1);
    
    I2C2_Stop();
}


//no need
void  I2C2_SDA_In()
{
//	GPIO_InitTypeDef GPIO_InitStruct;
//    
//    DHT12_SCL_GPIO_CLK_ENABLE();
//    GPIO_InitStruct.Pin   = DHT12_SDA_PIN;
//    GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
//    GPIO_InitStruct.Pull  = GPIO_PULLUP;
//    GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;
//    HAL_GPIO_Init(DHT12_SCL_GPIOx, &GPIO_InitStruct);
}
//no need
void  I2C2_SDA_Out()
{
//	GPIO_InitTypeDef GPIO_InitStruct;
//    
//    DHT12_SCL_GPIO_CLK_ENABLE();
//    GPIO_InitStruct.Pin   = DHT12_SDA_PIN;
//    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
//    GPIO_InitStruct.Pull  = GPIO_NOPULL;
//    GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;
//    HAL_GPIO_Init(DHT12_SCL_GPIOx, &GPIO_InitStruct);
}

/*
call Delay_us(n) which can accurate count time
*/
void I2C2_Delay_us(uint16_t cnt)
{
//    uint16_t i;
//    for(i=0;i<cnt * 200;i++);
	Delay_us(cnt);
}
    
/************************************************
*	函 数 名: I2C_Start
*	功能说明: CPU发起I2C总线停止信号
*	形    参：无
*	返 回 值: 无
**************************************************/ 
void I2C2_Start(void)  
{ 
	I2C2_SDA_Out();//sda:out
    I2C2_SDA_OUT(1);
    I2C2_SCL_OUT(1);
    I2C2_Delay_us(14);
    I2C2_SDA_OUT(0);
    I2C2_Delay_us(14);
    I2C2_SCL_OUT(0); 
} 

/****************************************************
*	函 数 名: I2C_Stop
*	功能说明: CPU发起I2C总线停止信号
*	形    参：无
*	返 回 值: 无
****************************************************/
void I2C2_Stop(void)  
{ 
	I2C2_SDA_Out();//sda:out
    I2C2_SDA_OUT(0);
    I2C2_SCL_OUT(0);
    I2C2_Delay_us(14);
    I2C2_SCL_OUT(1);
    I2C2_Delay_us(14);
	I2C2_SDA_OUT(1);
}

/************************************** 
*	函 数 名: I2C_Ack
*	功能说明: CPU产生一个ACK信号
*	形    参：无
*	返 回 值: 无 
**************************************/
void I2C2_Ack(void) 
{ 
    I2C2_SCL_OUT(0);
	I2C2_SDA_Out();//sda:out
    I2C2_SDA_OUT(0);
    I2C2_Delay_us(15);
    I2C2_SCL_OUT(1);
    I2C2_Delay_us(15);
    I2C2_SCL_OUT(0);
} 
/*
*************************************************
*	函 数 名: I2C_NoAck
*	功能说明: CPU产生1个NACK信号
*	形    参：无
*	返 回 值: 无
*************************************************
*/
void I2C2_NoAck(void)
{
    I2C2_SCL_OUT(0);
	I2C2_SDA_Out();//sda:out
    I2C2_SDA_OUT(1);
    I2C2_Delay_us(15);
    I2C2_SCL_OUT(1);
    I2C2_Delay_us(15);
    I2C2_SCL_OUT(0);    
}
/*************************************************************
*	函 数 名: I2C_WaitAck
*	功能说明: CPU产生一个时钟，并读取器件的ACK应答信号
*	形    参：无
*	返 回 值: 返回0表示正确应答，1表示无器件响应
*************************************************************/
uint8_t I2C2_WaitAck(void)
{ 
    __IO uint16_t t = 0;
	I2C2_SCL_OUT(0);
    I2C2_SDA_OUT(1);
	I2C2_SDA_In();//sda:in
    I2C2_Delay_us(14);
    I2C2_SCL_OUT(1);
    I2C2_Delay_us(14);
    
    while(I2C2_SDA_READ())//wait untill sda->0
    {
        t++;
        if(t>300)
        {
            I2C2_Stop();
            return 1;
        }   
    }

    I2C2_SCL_OUT(0);
	I2C2_Delay_us(10);
    return 0; 
}

void I2C2_Send_Byte(uint8_t dat)
{
    __IO uint8_t i;
	
	I2C2_SDA_Out();//sda:out
    I2C2_SCL_OUT(0);

    for(i=0; i<8; i++)
    {   
		I2C2_SCL_OUT(0);
        if(dat & 0x80) { I2C2_SDA_OUT(1); }
        else           { I2C2_SDA_OUT(0); }

        I2C2_Delay_us(14);
        I2C2_SCL_OUT(1);    
        I2C2_Delay_us(14);       
        dat <<= 1;  
    }
	I2C2_SCL_OUT(0);
}

/************************************************
*	函 数 名: I2C_Read_Byte
*	功能说明: CPU从I2C总线设备读取8bit数据
*	形    参：无
*	返 回 值: 读到的数据
*************************************************/
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
uint8_t I2C2_Read_Byte(uint8_t ack)
{
    uint8_t  i,receive=0;
    
    I2C2_SDA_OUT(1);
	I2C2_SDA_In();//sda:in
	
    for(i=0;i<8;i++ )
    {
        I2C2_SCL_OUT(0); 
        I2C2_Delay_us(50);
        I2C2_SCL_OUT(1);
        receive<<=1;
		I2C2_Delay_us(10);//add delay with dht12
        if(I2C2_SDA_READ()) { receive++; }  

    }    
	I2C2_SCL_OUT(1);
    if (!ack) { I2C2_NoAck(); } //发送nACK
    else      { I2C2_Ack();   } //发送ACK   
    
    return receive;
}

/************************************************
*	函 数 名: DHT12_Read_data
*	功能说明: read dht12 data
*	形    参：struData * stru_data
*	返 回 值: void
*************************************************/
void DHT12_Read_Data(struData * sensor_data)
{
	uint16_t cnt;
	uint8_t temp_h=0,temp_l=0,humi_h,humi_l,crc_tmp,tmp;
	
	I2C2_Start();
	I2C2_Send_Byte(DHT12_ADDR);//0xb8
	if(!I2C2_WaitAck())
	{
		cnt = 0;
		I2C2_Send_Byte(0x00);
		while(I2C2_WaitAck())
		{
			if(cnt++ >= 1000)
			{
				break;
			}
		}
		
		cnt = 0;
		I2C2_Start();
		I2C2_Send_Byte(DHT12_READ);//0xb9
		while(I2C2_WaitAck())
		{
			if(cnt++ >= 1000)
			{
				break;
			}
		}
		
		humi_h = I2C2_Read_Byte(1);
		humi_l = I2C2_Read_Byte(1);
		temp_h = I2C2_Read_Byte(1);
		temp_l = I2C2_Read_Byte(1);
		crc_tmp = I2C2_Read_Byte(0);
		
		I2C2_Stop();
		
		tmp = (temp_h + temp_l + humi_h + humi_l);
		
		if(tmp == crc_tmp)
		{
			uint16_t temp = temp_h * 10 + temp_l;
			uint16_t humi = humi_h * 10 + humi_l;
			
			(temp >= 600) ? temp= 600 : temp;
			(humi >= 950) ? humi= 950 : humi;
			
			//printf("temp:%d",temp);
			//printf("humi:%d",humi);
			
			
				
			sensor_data->data_humi=sensor_data->data_humi == 0?humi:((humi + sensor_data->data_humi) >> 1);//(new + old)/2
			sensor_data->data_temp=sensor_data->data_temp == 0?temp:((temp + sensor_data->data_temp) >> 1);//(new + old)/2
			
		}
		else
		{
			//printf("CRC WRONG");
		}
	}
	else
		printf("error");
}
