/*************************************************
//File name:	sensor.c
//File info:	func about sensor(except dht12)
//Author:		fan Li
//Date:
*************************************************/

#include "sensor.h"

void sensor_data_proc()
{
	uint8_t offset = 0;
	//dataProc CQLMT7
	//cho data[4]:H data[5]:L
	
	while(CH2O_Rec_Buffer[offset] != 0xFF){offset++;if(offset >= CH2O_DATA_LENGTH){return;}}
	
	if(sensor_data_now.data_cho == 0)
		sensor_data_now.data_cho = (CH2O_Rec_Buffer[4 + offset] << 8) + CH2O_Rec_Buffer[5 + offset];
	else{cho_avg();}
	
	offset = 0;
	
	while(PM25_Rec_Buffer[offset] != 0x42){offset++;if(offset >= PM25_DATA_LENGTH){return;}}
	if(sensor_data_now.data_pm25 == 0)
	{
		sensor_data_now.data_pm25 = (PM25_Rec_Buffer[6 + offset]  << 8 ) + PM25_Rec_Buffer[7 + offset];
		sensor_data_now.data_pm10 = (PM25_Rec_Buffer[8 + offset]  << 8 ) + PM25_Rec_Buffer[9 + offset];
	}
	else{pm25_avg();}
	
	
	//ch4 read data from adc directly
	//sensor_data_now.data_ch4 = HAL_ADC_GetValue(&hadc1);
	if(sensor_data_now.data_ch4==0){sensor_data_now.data_ch4 = HAL_ADC_GetValue(&hadc1);}
	else{ch4_avg();}
	
	
	//call dht12 read()
	DHT12_Read_Data(&sensor_data_now);
	
}

void cho_avg()
{
	uint16_t temp = sensor_data_now.data_cho;
	uint8_t count = 0;
	uint8_t offset = 0;
	
	while(CH2O_Rec_Buffer[offset] != 0xFF){offset++;}//定位数据帧头部
	while(count <= SAMPLE_NUM)//多帧采样
	{
			temp += ((CH2O_Rec_Buffer[HCHO_H + count * CH2O_DATA_LENGTH + offset] << 8 )
				+ CH2O_Rec_Buffer[HCHO_L + count * CH2O_DATA_LENGTH + offset]);
			temp >>= 1;//取平均值滤波
		count++;
	}
	sensor_data_now.data_cho = temp;
}

void pm25_avg()
{
	uint16_t temp = sensor_data_now.data_pm25;
	uint16_t temp_p10 = sensor_data_now.data_pm10;
	uint8_t count = 0;
	
	uint8_t offset = 0;
	while(PM25_Rec_Buffer[offset] != 0x42){offset++;}
	
	while(count <= SAMPLE_NUM)
	{
		
			temp += ((PM25_Rec_Buffer[6 + count * PM25_DATA_LENGTH + offset] << 8 )
				+ PM25_Rec_Buffer[7 + count * PM25_DATA_LENGTH + offset]);
			temp >>= 1;
			temp_p10 += ((PM25_Rec_Buffer[8 + count * PM25_DATA_LENGTH + offset] << 8 )
				+ PM25_Rec_Buffer[9 + count * PM25_DATA_LENGTH + offset]);
			temp_p10 >>= 1;
		
		count++;
	}
	sensor_data_now.data_pm25 = temp;
	sensor_data_now.data_pm10 = temp_p10;
}

/************************************************************************
//Func Name:	ch4_sensor_warn()
//Func Info:	
//Func args:	
//Func return:	
//Func author:	fan Li
************************************************************************/
void ch4_avg()
{
	uint16_t tmp = HAL_ADC_GetValue(&hadc1);
	if(sensor_data_now.flag_ch4_on)
	{
		sensor_data_now.data_ch4 = (sensor_data_now.data_ch4 + tmp)>>1;
	}
}
uint8_t Read_Inf()
{
	return HAL_GPIO_ReadPin(INF_GPIOx,INF_PIN);
}

void sensor_init()
{
	Uart_sensor_init();
	CH4_CE_ON();
	PM25_CE_ON();
}

void sensor_deinit()
{
	HAL_UART_MspDeInit(&HUART_HCHO);
	HAL_UART_MspDeInit(&HUART_PM25);
	CH4_CE_OFF();
	PM25_CE_OFF();
}
/************************************************************************
//Func Name:	ch4_sensor_onoff()
//Func Info:	turn on&off ch4 sensor
//Func args:	None
//Func return:	None
//Func author:	fan Li
************************************************************************/
static uint8_t pwr_on_count=0;
void ch4_sensor_onoff()
{
	sensor_data_now.flag_ch4_on=!sensor_data_now.flag_ch4_on;//toggle sensor
	
	if(pwr_on_count<=12){CH4_CE_ON();pwr_on_count++;}//keep sensor on within the first min after power on
	
	if(sensor_data_now.flag_ch4_on)
	{
		CH4_CE_ON();
	}
	else if(sensor_data_now.data_ch4 <= CH4_ALR_VAL)//just turn off without warning
	{
		CH4_CE_OFF();
	}

}
/************************************************************************
//Func Name:	ch4_sensor_warn()
//Func Info:	
//Func args:	
//Func return:	
//Func author:	fan Li
************************************************************************/
void ch4_sensor_warn();

