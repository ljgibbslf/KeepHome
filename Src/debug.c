/*************************************************
//File name:	debug.c
//File info:	using for debugging
//Author:		fan Li
//Date:
*************************************************/

#include "debug.h"

extern  uint8_t	  debug_Label;

void debug_usart()
{
	switch(debug_Label)
	{
		case 0x01:{
			UDebug_Send_String((uint8_t *)"Debug Test 1");
			break;
		}
		case 0x02:{
			UDebug_Send_String((uint8_t *)"Debug Test 2");
			break;
		}
		case 0x03:{
			UDebug_Send_String((uint8_t *)"Debug Test 3");
			break;
		}
		case 0x04:{
			UDebug_Send_String((uint8_t *)"Debug Test 4");
			break;
		}
//		default:{
//			UDebug_Send_String((uint8_t *)"Unknown Test!");
//			break;
//		}
	}
}





//	if(stru_Usart_test.flag_01 == ENABLE)
//		{
//			UDebug_Send_String((uint8_t *)"ftest 1");
//			//DHT22_Read_Data();
//			DHT12_Read_Data(&sensor_data_now);
//			//tftDisp_SensorData(&sensor_data_now);
//			for(int i = 0;i < MESS_LENG;i++)
//			{
//				wifi_Sed_Mess.message_Buffer[i] = 0x11;
//			}
////			for(int i = 0;i < MESS_ID_LENG;i++)
////			{
////				wifi_Sed_Mess.user_id[i] = 0x22;
////			}
//			wifi_Sed_Mess.wifiMess.dir_Type = DIR_SEND | MESS_ALARM;
//			wifi_Sed_Mess.wifiMess.startByte = START_BYTE;
//			wifi_Sed_Mess.wifiMess.endByte = END_BYTE;
//			
//			
//			UWifi_Send_String(wifi_Sed_Mess.message_Buffer);
////			uint8_t dataSend[5]={0x11,0x22,0x33,0x44,0x55};
////			ESP8266_Send(dataSend);
//			//ESP8266_StopTrans();
//			//Delay_ms(1000);//delay at least 1ms after quit TransT
//			//ESP8266_StartSever();
//			//ESP8266_Soft_Reset();
//			
////			printf("ID:%04X\n",W25Q64_ReadID());
////			uint8_t tmp_buffer[100];
////			W25Q64_Read(tmp_buffer,221*4096,100);
////			printf("READ W25Q64:\n");
////			for(int i=0;i<100;i++)
////			{
////				printf("%02X",tmp_buffer[i]);
////				//tmp_buffer[i] = i;
////				if(i%4 == 0) printf("\n");
////			}
////			W25Q64_Write(tmp_buffer,CONFIG_ADDR,100);
////			W25Q64_Erase_Sector(CONFIG_SECTOR);
//		  //W25Q64_Write((uint8_t*)pic_down_buffer,222*4096,sizeof(pic_down_buffer) * 0x2);
//			stru_Usart_test.flag_01 = DISABLE;
//			
//			
//			
//		}
//		if(stru_Usart_test.flag_02 == ENABLE)
//		{
//			UDebug_Send_String((uint8_t *)"ftest 2");
//			//Gui_Draw_Pic(&icon1,METRO_X_STA + METRO_X_CLN * 0 + METRO_LEGHTH * 0,METRO_Y_STA,BLUE_2_4);
////			if(wifi_Rec_Mess.wifiMess.is_proc == FALSE)
////			{
////				printf("The Data Rec now:%X\n",wifi_Rec_Mess.wifiMess.data[0]);
////				wifi_Rec_Mess.wifiMess.is_proc = TRUE;
////			}else
////				printf("This Frame has been processed.\n");
//			//if(flag_userConf_get)
//			//{
//				ESP8266_StopTrans();
//				Delay_ms(10);
//				//ESP8266_Soft_Reset();
//				Delay_ms(10);
//				//uint8_t  ssid[100];
//				//uint8_t	 pwd[100]; 
//				ESP8266_NetConfig((uint8_t*)"4TEST-PC",(uint8_t*)"12345678");// need add \0?
//			//}
//			flag_userConf_mode = FALSE;
//			// check if enter normal mode successfully
//			
//			stru_Usart_test.flag_02 = DISABLE;
//			
//		}
//		if(stru_Usart_test.flag_03 == ENABLE)
//		{
//			UDebug_Send_String((uint8_t *)"ftest 3");
//			Lcd_Clear_All(BLUE_2_4);
//			//Gui_Draw_Pic_Ext(&pic_down,0,0,BLUE_2_4);
////			#ifdef IS_WIFI_DEBUG
////				memset(UWifi_Rec_Buffer, '\0', UWifi_REC_MAX_BYTES);
////				UWifi_Rec_Point = 0;
////			#endif
////			printf("nRF24 check:%d\n",NRF24_Check());
//			
//			
//			
//			ESP8266_NetConfig((uint8_t*)"4TEST-MB",(uint8_t*)"12345678");
//			ESP8266_SaveTrans((uint8_t*)"192.168.43.1",(uint16_t)3334);
//			stru_Usart_test.flag_03 = DISABLE;
//			
//		}
//		if(stru_Usart_test.flag_04 == ENABLE)
//		{
//			UDebug_Send_String((uint8_t *)"ftest 4");
//			#ifdef IS_WIFI_DEBUG
//				uint16_t length = 0;
//				uint8_t tempStr[100];
//	
//				length = strlen((char*)UDebug_Rec_Buffer);
//				memcpy(tempStr,(char*)UDebug_Rec_Buffer,length - 1);//send U1 buffer without 0x04(cmd)
//			
//				UWifi_Send_String((uint8_t*)tempStr);
//				//clear u1 recbuffer
//				memset(UDebug_Rec_Buffer, '\0', UDebug_REC_MAX_BYTES);
//				UDebug_Rec_Point = 0;
//				printf("usart1==>usart2:%s",tempStr);
//			#endif
//			#define TEST4_1
//			#ifdef TEST4_1
//				SetRTCTime_Test();
//			#endif
//			stru_Usart_test.flag_04 = DISABLE;
//			
//		}