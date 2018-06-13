/*************************************************
//File name:	config.c
//File info:	earse difference between flash chip
//Author:		fan Li
//Date:			18.5.8
*************************************************/

#include "common.h"
#include "w25q64.h"
#include "string.h"

void read_Wifi_Config(struWifi * conf)
{
	uint8_t tmp_buffer[100];
	W25Q64_Read(tmp_buffer,WIFI_CONFIG_ADDR,sizeof(*conf));
	memcpy((void*)conf,(void*)tmp_buffer,sizeof(struWifi));
}
void write_Wifi_Config(struWifi * conf)
{
	uint8_t buf[200];
	memcpy(&buf,conf,sizeof(*conf));
	W25Q64_Write(buf,WIFI_CONFIG_ADDR,sizeof(struWifi));
}

void read_Sys_Config(struSet *);
void write_Sys_Config(struSet *);