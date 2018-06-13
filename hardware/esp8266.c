/*************************************************
//File name:	esp8266.c	
//File info:	BSP for esp8266
//Author:		fan Li
//Date:
*************************************************/

#include "esp8266.h"
//TODO lack of return check and just return TRUE

extern uint8_t   UWifi_Rec_Buffer[UWifi_REC_MAX_BYTES];
extern uint8_t   UWifi_Rec_Point;
extern BOOL 	flag_userConf_mode;
extern struTimerTask      tim_task;
extern BOOL 	  		flag_Rec_mess;					//采集数据帧完成标志
extern uniWifiMess 	wifi_Rec_Mess;					//发送和接收消息结构体
extern uniWifiMess 	wifi_Sed_Mess;
/**
  * @brief  This function inits the Esp8266Wifi 's TransTrans.
  * @param  IN: strucWifi OUT: strucWifi.isTransReady
  * @retval None
  */
  
void ESP8266_init(struWifi* conf)
{
	WIFI_CE_ON();
//	//get necessary info form ESP8266_ReadConf(struWifi* conf)
//	ESP8266_ReadConf(conf);
//	
//	if(conf->is_NetConf)
//	{
//		//do nothing if TransT has configed
//		if(conf->is_TransReady == FALSE)
//		{
//			//
//			if(ESP8266_NetConfig(conf->ssid,conf->pwd) &&
//				ESP8266_SaveTrans(conf->addr,conf->port))
//				conf->is_TransReady = TRUE;
//			else
//				conf->is_TransReady = FALSE;
//		}
//	}
//	else
//	{
//		//turn to softAP and seek for network info
//		ESp8266_Wait_Netconf();
//	}
	
}
//----------------------------------------------
void ESP8266_Send(uint8_t * data,enumMessType type,struWifi* conf)
{
	uniWifiMess 	sedMess;
	uint8_t         data_crc;
	uint16_t		dev_id = 0x0001;
	sedMess.wifiMess.startByte = START_BYTE;
	sedMess.wifiMess.endByte = END_BYTE;
	sedMess.wifiMess.dir_Type = (DIR_SEND << 4) + type;	
	
	uint8_t uid = (conf->user_id & 0xFF) - 0x30; 
	sedMess.wifiMess.user_id[0] = uid;
	sedMess.wifiMess.user_id[1] = (uint8_t)(dev_id >> 8);
	sedMess.wifiMess.user_id[2] = dev_id & 0x00FF;
	
	data_crc = data_crc + sedMess.wifiMess.startByte + sedMess.wifiMess.startByte + sedMess.wifiMess.startByte
		+ sedMess.wifiMess.user_id[0] + sedMess.wifiMess.user_id[1]+ sedMess.wifiMess.user_id[2];
	
	if(type == MESS_REPO )	
	{
		//TODO check length
		for(int i = 0;i < MESS_DATA_LENG;i++)
		{
			
			sedMess.wifiMess.data[i] = *data;
			data_crc += *data;
			data++;
		}
	}
	if(type == MESS_ALARM)	
	{
		//TODO check length
		for(int i = 0;i < MESS_DATA_LENG;i++)
		{
			
			sedMess.wifiMess.data[i] = 0x44;
			data_crc += *data;
			data++;
		}
	}
	else if(type == MESS_KEEP_ALIVE)
	{
		for(int i = 0;i < MESS_DATA_LENG;i++)
		{
			
			sedMess.wifiMess.data[i] = 0x11;
			data_crc += 0x11;
		}
	}
	
	if(type == MESS_CONFIG)	
	{
		//TODO check length
		for(int i = 0;i < MESS_DATA_LENG;i++)
		{
			
			sedMess.wifiMess.data[i] = 0x33;
			data_crc += *data;
			data++;
		}
	}
	sedMess.wifiMess.CRCByte = data_crc;
	UWifi_Send_String_mess(sedMess.message_Buffer);
}
//----------------------------------------------
BOOL ESP8266_NetConfig(uint8_t * ssid,uint8_t * pwd)
{
	
	uint8_t strAT[100];
	
	memset(UWifi_Rec_Buffer,'\0',UWifi_REC_MAX_BYTES);
	UWifi_Rec_Point = 0x0;
			
	
	sprintf((char*)strAT,"AT+CWJAP_DEF=\"%s\",\"%s\"\r\n",ssid,pwd);
	UWifi_Send_String(strAT);
	
	
	Delay_ms(6000);//hard to remove
	
	uint8_t fail_count = 0;
	while(strstr((char*)UWifi_Rec_Buffer,"OK")==NULL)
	{
		UWifi_Send_String(strAT);
		Delay_ms(4000);
		fail_count++;
		if(fail_count>=MAX_TRY+5){return FALSE;}
	}
	return TRUE;
}
//----------------------------------------------
BOOL ESP8266_TransConfig(uint8_t * addr,uint16_t port)
{
	
	uint8_t strAT[100];
	sprintf((char*)strAT,"AT+CIPSTART=\"TCP\",\"%s\",%d\r\n",addr,port);
	UWifi_Send_String(strAT);
	return TRUE;
}
//----------------------------------------------
BOOL ESP8266_SaveTrans(uint8_t * addr,uint16_t port)
{
	
	uint8_t strAT[100];
	
	memset(UWifi_Rec_Buffer,'\0',UWifi_REC_MAX_BYTES);
	UWifi_Rec_Point = 0x0;
	
	sprintf((char*)strAT,"AT+SAVETRANSLINK=1,\"%s\",%d,\"TCP\"\r\n",addr,port);
	UWifi_Send_String(strAT);

	Delay_ms(3000);
	uint8_t fail_count;
	while(strstr((char*)UWifi_Rec_Buffer,"OK")==NULL)
	{
		UWifi_Send_String(strAT);
		Delay_ms(1000);
		if(fail_count>=MAX_TRY){break;}
	}
	ESP8266_Soft_Reset();//reset after set poweron TT
	return (strstr((char*)UWifi_Rec_Buffer,"OK")==NULL);
}
//----------------------------------------------
BOOL ESP8266_StopTrans()
{
	memset(UWifi_Rec_Buffer,'\0',UWifi_REC_MAX_BYTES);
	UWifi_Rec_Point = 0x0;
	
	WIFI_Send_String("+++"); //do not need /n
	//Delay_ms(10);
	//WIFI_Send_String("+++");// Make Sure quit TT model
	Delay_ms(2000);
	WIFI_Send_String("AT+SAVETRANSLINK=0\r\n");
	Delay_ms(1000);
//	while(strstr((char*)UWifi_Rec_Buffer,"OK")==NULL)
	uint8_t fail_count;
	while(strstr((char*)UWifi_Rec_Buffer,"OK")==NULL){
		WIFI_Send_String("AT+SAVETRANSLINK=0\r\n");
		Delay_ms(2000);
		if(fail_count>=MAX_TRY){break;}
	}
	return (strstr((char*)UWifi_Rec_Buffer,"OK")==NULL);
}

void ESP8266_Soft_Reset(void)
{
	WIFI_Send_String("AT+RST\r\n");
	Delay_ms(2000);
}
void ESP8266_StartSever(void)
{
	//Because of the complexity of the TCP Sever We start a UDP sever
	WIFI_Send_String("AT+CIPMUX=1\r\n");//enable multi connect
	Delay_ms(100);
	WIFI_Send_String("AT+CIPSERVER=1\r\n");
}

void ESP8266_Sever_Connect(void)
{
	uint8_t strAT[100];
	sprintf((char*)strAT,"AT+CIPSTART=\"UDP\",\"%s\",%d,%d,0\r\n",UDP_REMOTE_IP,UDP_REMOTE_PORT,UDP_LOCAL_PORT);
	WIFI_Send_String(strAT);
	Delay_ms(10);
	WIFI_Send_String("AT+CIPMODE=1\r\n");
}
/**
  * @brief  Read data from flash
  * @param  struWifi* conf
  * @retval None
  */
void ESP8266_ReadConf(struWifi* conf)
{
//	uint8_t tmp_buffer[100];
//	W25Q64_Read(tmp_buffer,CONFIG_ADDR,100);
	
}

void ESP8266_WriteConf(struWifi* conf)
{
//	uint8_t tmp_buffer[30];
//	conf->is_NetConf = TRUE;
//	W25Q64_Write((uint8_t *)conf,CONFIG_ADDR,6);
//	strcpy((char *)tmp_buffer,(const char*)conf->ssid);
//	W25Q64_Write(tmp_buffer,CONFIG_ADDR+6,30);
//	
//	memset(tmp_buffer,'\0',30);
//	strcpy((char *)tmp_buffer,(const char*)conf->pwd);
//	W25Q64_Write(tmp_buffer,CONFIG_ADDR+36,30);
}

void ESP8266_Get_UserConf(struWifi* conf)
{
	if(flag_userConf_get)//获得配置信息
	{
		flag_userConf_get = FALSE;
		uint8_t temp[100];
		strcpy((char *)temp,(const char *)user_conf_buffer);

		//获取逗号相隔的SSID 密码信息 存储于wifi配置结构体中
//		memset(conf->ssid,'\0',strlen((const char *)conf->ssid));
//		memcpy(conf->ssid,temp,((uint8_t *)strchr((const char *)temp,',')-temp));
//		
//		memset(conf->pwd,'\0',strlen((const char *)conf->pwd));
//		strcpy((char *)conf->pwd,strchr((const char *)temp,',')+1);
		
		char * ctmp = strchr((const char *)temp,',');
		memset(conf->ssid,'\0',strlen((const char *)conf->ssid));
		memcpy(conf->ssid,temp,ctmp-(char*)temp);
		
		char * ctmp2 = strchr(ctmp+1,',');
		memset(conf->pwd,'\0',strlen((const char *)conf->pwd));
		memcpy((char *)conf->pwd,ctmp+1,ctmp2-ctmp-1);
		
		char uid = *(ctmp2+1);
		conf->user_id=(uint32_t)uid;
		
		tftDisp_mess("WiFi Configuring... 1/4");
		//停止与手机TCP服务器的透传
		ESP8266_StopTrans();
		tftDisp_mess("WiFi Configuring... 2/4");
		//转变无线模块的工作模式为station 连接网络与远程服务器
		ESP8266_change_mode(1);
		
		Delay_ms(3000);
		tftDisp_mess("WiFi Configuring... 3/4");
		if(!ESP8266_NetConfig(conf->ssid,conf->pwd))
		{
			tftDisp_mess("Err at Stp 3! Try Again.");
			Delay_ms(2000);
			ESP8266_pre_config(TRUE);//重新准备配置工作
			return;//这里可能有问题
		}
		tftDisp_mess("WiFi Configuring... 4/4");
		ESP8266_SaveTrans((uint8_t *)"39.106.213.217",8888);
		

		flag_userConf_mode = FALSE;
		
		//在网络配置信息结构体中置网络信息配置标志位
		conf->is_NetConf = TRUE;
		
		//将更新的配置写入外部Flash中
		write_Wifi_Config(conf);
		
		
		wifi_Sed_Mess.wifiMess.is_first_mess = TRUE;
		tftDisp_mess("WiFi Configuring  Done!");
		tim_task.enable_win_count = ENABLE;
		tim_task.win_count = 3;
		ESP8266_Send(NULL,MESS_CONFIG,conf);
	}
}
void ESp8266_Wait_Netconf(){}
	
BOOL ESP8266_change_mode(uint8_t mode)
{
	uint8_t strAT[100];
	
	memset(UWifi_Rec_Buffer,'\0',UWifi_REC_MAX_BYTES);
	UWifi_Rec_Point = 0x0;
	
	sprintf((char*)strAT,"AT+CWMODE_DEF=%d\r\n",mode);
	UWifi_Send_String(strAT);
	
	
	Delay_ms(2000);
	uint8_t fail_count;
	while(strstr((char*)UWifi_Rec_Buffer,"OK")==NULL)
	{
		UWifi_Send_String(strAT);
		Delay_ms(2000);
		if(fail_count>=MAX_TRY){break;}
	}
	return (strstr((char*)UWifi_Rec_Buffer,"OK")!=NULL);

}

BOOL ESP8266_check_conn()
{
	UWifi_Send_String_mess("hello!");
	Delay_ms(5000);
	return (strstr((char*)UWifi_Rec_Buffer,"ok")!=NULL);
}

BOOL ESP8266_pre_config(BOOL is_show)
{
	flag_userConf_mode = TRUE;//开启配置模式
	if(is_show){tftDisp_mess("WiFi Config Prep... 1/3");}
	ESP8266_StopTrans();
	if(is_show){tftDisp_mess("WiFi Config Prep... 2/3");}
	ESP8266_change_mode(2);
	if(is_show){tftDisp_mess("WiFi Config Prep... 3/3");}
	ESP8266_SaveTrans("192.168.4.2",8080);
	if(is_show){tftDisp_mess("WiFi Config Prep Done");}
	Delay_ms(500);
	UWifi_Send_String_mess("Connect Ok!");
	if(is_show)
	{
		tim_task.enable_win_count = ENABLE;
		tim_task.win_count = 2;
	}	
	return TRUE;
}

BOOL ESP8266_sure_conn(struWifi	wifi_conf)
{
	ESP8266_StopTrans();
	ESP8266_change_mode(1);
	ESP8266_NetConfig(wifi_conf.ssid,wifi_conf.pwd);
	ESP8266_SaveTrans((uint8_t *)"39.106.213.217",8888);
}

void ESP8266_send_mess(struWifi* conf)
{
	if(conf->is_NetConf)
	{
		ESP8266_Send((uint8_t *)&sensor_data_now,MESS_REPO,conf);
		if(tim_task.net_conn_count >= 10){conf->is_net_conn = FALSE;}
	}
}
void ESP8266_read_mess(struWifi* conf)
{
//check if receive new message
	if(flag_Rec_mess)
	{
		tim_task.net_conn_count = 0;
		conf->is_net_conn = TRUE;
		//mess_proc();
		uint8_t type = 0x0F & wifi_Rec_Mess.wifiMess.dir_Type;
		if(sensor_data_now.data_humi>=600)
					{
						NRF24_send_cmd(0,3);
					}
		switch(type)
		{
			
			case 2:
				{
					
					//uint8_t cmd = wifi_Rec_Mess.wifiMess.data[0];
					uint8_t cmd = wifi_Rec_Mess.wifiMess.user_id[2];//temp
					NRF24_send_cmd(0,cmd);
					
					break;
				}
			
			default: break;		
		}
		
		flag_Rec_mess = FALSE;
	}
}
