#ifndef __ESP8266_H__
#define __ESP8266_H__
//----------------------------------------------
#include "common.h"
#include  "usart.h"
#include <stdio.h>
#include "w25q64.h"
#include <string.h>
#include "config.h"
#include "tftDisp.h"
#include "nrf24l0.h"
//----------------------------------------------
//----------------------------------------------
// define wifi message exchange args
#define 	START_BYTE			0x10
#define 	END_BYTE			0x20
#define 	MESS_LENG			16  //16 BYTE
#define		MESS_ID_LENG		3
#define		MESS_FLAG_LENG		5//5
#define		MESS_DATA_LENG		(MESS_LENG - MESS_FLAG_LENG - MESS_ID_LENG)
#define		DIR_SEND			0x1

#define		CONFIG_HEAD			0x11
#define		CONFIG_TAIL			0xFF

#define 	TCP_Server 			"192.168.137.1" //Inner Net
#define 	TCP_Port 			0x3334

#define 	UDP_REMOTE_PORT		0x1233
#define		UDP_REMOTE_IP		"192.168.4.2"
#define		UDP_LOCAL_PORT		0x1222

#define 	ESP8266_CMD(x)		WIFI_Send_String(x)

#define     WIFI_CE_PIN                       GPIO_PIN_0
#define     WIFI_CE_GPIO_PORT                 GPIOC
#define     WIFI_CE_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOD_CLK_ENABLE()
#define     WIFI_CE_ON()                      HAL_GPIO_WritePin(WIFI_CE_GPIO_PORT,WIFI_CE_PIN, GPIO_PIN_SET)
#define     WIFI_CE_OFF()                     HAL_GPIO_WritePin(WIFI_CE_GPIO_PORT,WIFI_CE_PIN, GPIO_PIN_RESET)

#define 	MAX_TRY				3
typedef enum
{
	MESS_REPO,
	MESS_ALARM,
	MESS_KEEP_ALIVE,
	MESS_TIME_SYN,
	MESS_ACK,
	MESS_CONFIG
}enumMessType;

typedef struct  
{
	uint8_t startByte;
	uint8_t	dir_Type;
	uint8_t	user_id[MESS_ID_LENG];//MESS_ID_LENG : 3
	uint8_t	data[MESS_DATA_LENG];//MESS_DATA_LENG : 8 
	uint8_t CRCByte;
	uint8_t res;
	uint8_t	endByte;
	BOOL	is_proc;
	BOOL	is_first_mess;
}struWifiMess;


typedef union
{
	uint8_t	message_Buffer[MESS_LENG];
	struWifiMess wifiMess;
}uniWifiMess;

//----------------------------------------------
extern BOOL 		flag_wait_userConf;
extern BOOL			flag_userConf_get;
extern uint8_t	  	user_conf_buffer[100];

//----------------------------------------------
void ESP8266_init(struWifi* config);
BOOL ESP8266_Start(void);
BOOL ESP8266_Stop(void);
BOOL ESP8266_Reset(void);
void ESP8266_Soft_Reset(void);
BOOL ESP8266_Sleep(void);
BOOL ESP8266_PowerOff(void);
BOOL ESP8266_PowerOn(void);


BOOL ESP8266_NetConfig(uint8_t * ssid,uint8_t * pwd);
//Trans = Transparent Transportion
BOOL ESP8266_TransConfig(uint8_t * addr,uint16_t port);
BOOL ESP8266_TestTrans(void);
BOOL ESP8266_SaveTrans(uint8_t * addr,uint16_t port);
BOOL ESP8266_StopTrans(void);

void ESP8266_StartSever(void);
void ESP8266_Sever_Connect(void);
void ESP8266_StopSever(void);

void ESP8266_ReadConf(struWifi* conf);
void ESp8266_Wait_Netconf();
void ESP8266_Send(uint8_t * data,enumMessType type,struWifi* conf);

void ESP8266_Get_UserConf(struWifi* conf);
void ESP8266_WriteConf(struWifi* conf);

BOOL ESP8266_change_mode(uint8_t mode);
BOOL ESP8266_check_conn();

BOOL ESP8266_pre_config(BOOL is_show);
BOOL ESP8266_sure_conn(struWifi wifi_conf);

void ESP8266_send_mess(struWifi* conf);
void ESP8266_read_mess(struWifi* conf);
//----------------------------------------------
#endif