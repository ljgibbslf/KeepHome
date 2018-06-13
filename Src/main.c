/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"
#include "adc.h"
#include "crc.h"
//#include "dcmi.h"
#include "dma.h"
#include "iwdg.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fsmc.h"

/* USER CODE BEGIN Includes */
#include  <string.h>
#include  "led.h"
#include  "common.h"
#include  "esp8266.h"
#include  "lcd_drive.h"
#include  "gui.h"
#include  "tftDisp.h"
#include  "w25q64.h"
#include  "touch.h"
#include  "dht12.h"
#include  "nrf24l0.h"
#include  "sensor.h"
#include  "window.h"
#include  "config.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
#define DEBUG_MODE
/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
/* ȫ�ֱ�����  ��Ҫʹ�����жϺ�������������----------------------------------- */
//=================================
//���������ʱ�ṹ��
struTimerTask      tim_task;
//=================================        
// UDebug ����
uint8_t   UDebug_Rec_Buffer[UDebug_REC_MAX_BYTES];  // ���ջ����� 
uint16_t  UDebug_Rec_Point;                     // ����ָ��
uint8_t   UDebug_Send_Buffer[UDebug_SEND_MAX_BYTES];// UDebug  ���ͻ����� 
// debug ���Ա���
uint8_t	  debug_Label;
//=================================
// UWifi ����
uint8_t   UWifi_Rec_Buffer[UWifi_REC_MAX_BYTES]; 
uint16_t  UWifi_Rec_Point;                     
uint8_t   UWifi_Send_Buffer[UWifi_SEND_MAX_BYTES];
//=================================
//UPm25 
uint8_t   UPm25_Rec_Buffer[PM25_DATA_LENGTH*PM25_BUFFER_NUM];
uint16_t  UPm25_Rec_Point;                    
//=================================
//UCH2O 
uint8_t   UCH2O_Rec_Buffer[CH2O_DATA_LENGTH*CH2O_BUFFER_NUM];
uint16_t  UCH2O_Rec_Point;                     
//=================================
//DATA
struData		sensor_data_now;		// ��ǰ����������
//=================================
// wifi
uniWifiMess 	wifi_Rec_Mess;					//���ͺͽ�����Ϣ�ṹ��
uniWifiMess 	wifi_Sed_Mess;
BOOL 	  		flag_Rec_mess;					//�ɼ�����֡��ɱ�־
BOOL 			flag_userConf_mode;             //�ڼ�⵽û���������ú� ��������ģʽ �ȴ�������������֡
BOOL			flag_userConf_get = FALSE;		//�ɼ���������֡��ɱ�־
uint8_t	  		user_conf_buffer[100];          //���ڼ�¼�û�������������
//----------------------------------------------
//2,4G ��Ϣ
uniNrfMess 	    nrf_Rec_Mess;
uniNrfMess 	    nrf_Sed_Mess;
BOOL 	  		flag_nrf_Rec_mess;



/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */
    struTouch       ctpxy;      	// ���ݴ������Ĳ���
    struRTC         rtcttime;   	// ʵʱʱ��
	struWin			win;			// ��Ļ��ʾ����ṹ��
	struButtomEvent	but_ent;		// ��Ļ��ť�ṹ��
	struSet			set_now;		// ��ǰ����
	struWifi		wifi_conf;		// WiFi������Ϣ�ṹ��
	//----------------------------------------------
	struButtom      but_list[BUTTON_NUM]; //��ť�б�
	//----------------------------------------------
	uint8_t			inf_low_count = 0;    //����ߵ͵�ƽ����
	uint8_t			inf_high_count = 0;
	//----------------------------------------------
	BOOL			flag_pwr_on;     //�����ϵ��־ ���ڿ���������ʾ
	uint8_t			alarm_tim_count; //��������ʱ�����
	uint8_t			ch4_heat_count;  //���鴫��������Ԥ�ȼ���
	BOOL 			light_onoff;
	uint32_t		syson_count;     //ϵͳ����ʱ������
	
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
	SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_DMA_Init();
	MX_ADC1_Init();
	MX_CRC_Init();
	//MX_DCMI_Init();
	//MX_IWDG_Init();
	MX_RTC_Init();
	MX_SPI1_Init();
	MX_SPI2_Init();
	MX_TIM4_Init();
	MX_UART4_Init();
	MX_USART2_UART_Init();
	MX_USART3_UART_Init();
	MX_USART6_UART_Init();
	MX_TIM5_Init();
	MX_FSMC_Init();
	MX_TIM7_Init();

  /* USER CODE BEGIN 2 */
	
	NRF24_init();             // NRF24����ģ���ʼ��
	if(!NRF24_Check()){NRF24_Check();}
	NRF24_RxMode();
	FT6336_I2C_GPIO_init();   // LCD���Ĵ��������ų�ʼ��
	LCD_init();		          // LCD��Ļ��ʼ��
	LED_GPIO_init();		  // LEDָʾ��GPIO���ų�ʼ��
	DHT12_I2C_GPIO_init();    // DHT12������IIC���ų�ʼ��
	sensor_init();            // ��������ʼ��
	ESP8266_init(NULL);       // WiFiģ���ʼ��
	tftDisp_btn_init((struButtom**)but_list);  //������ʾ������ʼ��
		
    tftDisp_welcome();        //���ú������������滶ӭ����
	win.mode = WIN_WELCOME;   
	//----------------------------------------------
    ReadRTCTime(&rtcttime);   //��ȡһ��RTCʱ��
	//----------------------------------------------
	HAL_ADC_Start(&hadc1);    //�������ڼ��鴫���������ɼ���ADC
	//----------------------------------------------
	
#ifdef DEBUG_MODE
	UDebug_Send_String((uint8_t *)"Debug Mode Start from U6"); //�ϵ���Ϣ��ӡ  ���ڵ���
#endif
	
	UWifi_Send_String_mess((uint8_t *)"hello!");//�������ӵ������ ����ģ��������������ʺ���Ϣ 
	read_Wifi_Config(&wifi_conf);//SPI Flash Dummy Read Flash�ϵ���һ��ȡ�޷���ȡ���� 
	
//#define CONNTST //�����������ò��� ÿ���ϵ�ʱȡ����־λ
#ifdef CONNTST
	wifi_conf.is_NetConf = FALSE;
	write_Wifi_Config(&wifi_conf);
#endif
	
	Delay_ms(2000); //������ʱ ���ڵȴ�WiFi���� ��ʱ���ڿ�������
	
	read_Wifi_Config(&wifi_conf); //��ȡ����������Ϣ
	
	if(wifi_conf.is_NetConf == FALSE)//�������û������ ���������ģʽ
	{		
		ESP8266_pre_config(FALSE);//�������õ�׼������ ���г�ʱ����
		
	}
	
	else//��������Ѿ�������� ��ȷ�����������ӣ������� ��������²���Ҫ��
	{
//#define SURE_CON
#ifdef SURE_CON
		ESP8266_sure_conn(wifi_conf);
#endif
	}
/* USER CODE END 2 */
	
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while(1)
	{
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
		
		IWDG_feed();//�������Ź�ι��
		
		ESP8266_read_mess(&wifi_conf);//����־λ �鿴�Ƿ���յ�wifi��Ϣ
		NRF24_rec_mess();//����־λ �鿴�Ƿ���յ�nrf24��Ϣ
		
		//TIMER TASK : tim_task.enable_PowerOn | 5ms | ���ڵ�һ�ο������� ������ʾ��������
		if(tim_task.enable_PowerOn && !flag_pwr_on)
		{
			
			Lcd_Clear_All(BK_COL);
			tftDisp_Main(&win);
			win.mode = WIN_MAIN;
			//----------------------------------------------

			ReadRTCTime(&rtcttime);         // ��ȡһ��RTCʱ��
			  // 
			tftDisp_AllDataTime(rtcttime);
			
			tftDisp_wifi_flag(wifi_conf.is_NetConf,wifi_conf.is_net_conn);
			flag_pwr_on = TRUE;
		}
		
		//TIMER TASK : tim_task.enable_ReadWin | 1ms | ��ȡ��������������������¼�
		if(tim_task.enable_ReadWin)
		{
			window_ctl(ctpxy,&win);//���ݴ������ ˢ����ʾ����
			
			buttom_event_ctl(ctpxy,&win,&but_ent);//�������¼�
			
			if(tim_task.win_count == 0 && tim_task.enable_win_count)
			{
				win.old_mode = win.mode;
				win.mode=WIN_MAIN;
				tim_task.enable_win_count = DISABLE;
			}//��ʱ�����ϲ㴰��
			
			tftDisp_fresh(&win);//ˢ����Ⱦ�µĴ���
			
			//if(wifi_conf.is_NetConf && win.mode == WIN_MAIN){tftDisp_wifi_flag();}//��ʾ�������
			if(win.mode == WIN_MAIN){tftDisp_wifi_flag(wifi_conf.is_NetConf,wifi_conf.is_net_conn);}
			
			tim_task.enable_ReadWin = DISABLE;
		}
		
		//TIMER TASK : tim_task.enable_Led  | 1s | LED ˢ���¼�
       if(tim_task.enable_Led)
		{
			LED2_TOGGLE();NRF24_RxMode();
			tim_task.enable_Led = DISABLE;
		}
		
		//TIMER TASK : tim_task.enable_ReadTouch  | 10ms | ��ȡ�������
		if(tim_task.enable_ReadTouch)
		{
			tim_task.enable_ReadTouch = DISABLE;
			ReadCTP(&ctpxy);                // ��ȡ�������Ĵ������꼰״̬

		}
		//TIMER TASK : tim_task.enable_ReadRTC  | 1s | ����RTCʱ��
		if(tim_task.enable_ReadRTC)
		{
			tim_task.enable_ReadRTC = DISABLE;
			ReadRTCTime(&rtcttime);     // ÿһ���Ӷ�ȡһ��RTCʱ��
			if(win.mode != WIN_WELCOME)
			{
				tftDisp_AllDataTime(rtcttime); // ��ʾ��ȡ��ʱ��
			}
		}
		
		//TIMER TASK : tim_task.enable_ReadSensor  | 1s | ��ȡ���������� ��ʾ���������� �������¼�
		if(tim_task.enable_ReadSensor)
		{
			tim_task.enable_ReadSensor = DISABLE;
			sensor_data_proc();
			tftDisp_SensorData(&win);
			//check if come to alarm mode
			if(sensor_data_now.data_ch4 >= CH4_ALR_VAL && syson_count >= 30)
			{
				win.old_mode = win.mode;
				win.mode = WIN_ALARM;//change win
				
				if(alarm_tim_count != 0)
				{
					buzzer_pwm_config(200 + 50 * alarm_tim_count);
					HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);//open buzzer
				}
				
				alarm_tim_count++;
				
				//if(alarm_tim_count >= 5){alarm_tim_count = 0;}//stop alarm 
				//if(alarm_tim_count == 0){HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_4);}
				
				ESP8266_Send(NULL,MESS_ALARM,&wifi_conf);//send alarm mess
				
				//HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
			}
			else if(sensor_data_now.data_ch4 < CH4_ALR_VAL && alarm_tim_count > 2)//�������
			{
				alarm_tim_count = 0;
				HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_4);
				if(win.mode == WIN_ALARM)
				{
					win.old_mode = win.mode;
					win.mode = WIN_MAIN;//change win
				}
			}
		}
		
		//TIMER TASK : tim_task.enable_SecOneTask  | 1s | һ���ӵ��ճ�����
		if(tim_task.enable_SecOneTask)
		{
			tim_task.enable_SecOneTask = DISABLE;
			if(win.mode == WIN_ALARM){tftDisp_alarm(win.is_rev);win.is_rev=!win.is_rev;} //refresh alarm win
			
			syson_count++;
//			if(wifi_conf.is_NetConf == FALSE)
//			{
//				UWifi_Send_String_mess("Connect Ok!");
//			}
		}
		
		//TIMER TASK : tim_task.enable_CH4_onoff  | 5s | ���鴫������ʱ�����ر�
		if(tim_task.enable_CH4_onoff)
		{
			tim_task.enable_CH4_onoff = DISABLE;
			ch4_sensor_onoff();
		}
		
		//----------------------------------------------
		//TIMER TASK : tim_task.enable_SendReport | 5s | ���ʹ��������ݲ���������Ϣ
		if(tim_task.enable_SendReport )
		{
			tim_task.enable_SendReport = DISABLE;
			if(wifi_conf.is_NetConf)
			{
				if(wifi_Sed_Mess.wifiMess.is_first_mess)
				{
					wifi_Sed_Mess.wifiMess.is_first_mess = FALSE;
					ESP8266_Send(NULL,MESS_CONFIG,&wifi_conf);
				}
				else
				{
					//ESP8266_Send(NULL,MESS_CONFIG,&wifi_conf);
					ESP8266_Send((uint8_t *)&sensor_data_now,MESS_REPO,&wifi_conf);
				}
				if(tim_task.net_conn_count >= 10){wifi_conf.is_net_conn = FALSE;}
			}			
		}
		
		
		//----------------------------------------------
		//TIMER TASK : tim_task.enable_ReadInf | 1s | ����������⴫�����¼�
		if(tim_task.enable_ReadInf)
		{
			tim_task.enable_ReadInf = DISABLE;
			if(Read_Inf() == GPIO_PIN_SET)
			{
				//printf("Y\n");
				inf_low_count = 0;
				inf_high_count++;
			}
			else
			{
				//printf("N\n");
				inf_high_count = 0;
				inf_low_count++;
			}
			if(ctpxy.ctpxy.ctp_x != 0xFFF)
			{
				inf_low_count = 0;
				inf_high_count++;
			}
			if(inf_low_count >= 13 && wifi_conf.is_net_conn){LCD_BKLED_OFF();}
			if(inf_high_count >= 2 || ctpxy.ctpxy.ctp_x != 0xFFF){LCD_BKLED_ON();}
		}
		
//		//TIMER TASK : tim_task.enable.enable_SendHeart | 100ms
//		if(tim_task.enable_SendHeart && !flag_AT_mode)
//		{
//			tim_task.enable_SendHeart = DISABLE;
//			ESP8266_Send(NULL,MESS_KEEP_ALIVE,0x00101112);
//		}
		
		//TIMER TASK : tim_task.enable_ReadWifiConf | 1s | flag_userConf_get = TRUE | ��ʱ��������������λ
		if(tim_task.enable_ReadWifiConf && flag_userConf_get)
		{
			tim_task.enable_ReadWifiConf = DISABLE;
			ESP8266_Get_UserConf(&wifi_conf);
			win.old_mode = WIN_MESS;
			win.mode = WIN_MESS;
			flag_userConf_get = FALSE;
			
		}

		
		//�����¼�----------------------------------------------
		if(but_ent.flag_wifitt_out)
		{
			printf("quit conn and wait for config new net");
			wifi_conf.is_NetConf = FALSE;
			wifi_conf.is_net_conn = FALSE;
			write_Wifi_Config(&wifi_conf);
			ESP8266_pre_config(TRUE);
			but_ent.flag_wifitt_out = FALSE;
		}
		

		if(but_ent.flag_light_on_off)
		{
			light_onoff=!light_onoff;
			if(light_onoff)
			{
				//printf("light on !");
				NRF24_send_cmd(0,1);
				
				tftDisp_mess("Light ON !");
				//Delay_ms(10);
			}
			else
			{
				NRF24_send_cmd(0,2);
				
				tftDisp_mess("Light OFF !");
				//Delay_ms(10);
			}
			
			
			tim_task.enable_win_count = ENABLE;
			tim_task.win_count = 2;
			but_ent.flag_light_on_off = FALSE;
		}
		//----------------------------------------------
	#ifdef DEBUG_MODE
		if(debug_Label == 0x01)
		{
			debug_Label = 0;
			if(NRF24_Check()){
				UDebug_Send_String((uint8_t *)"NRF24 OK\n");
				
				NRF24_TxMode();
				
				uint8_t str[50];
				memset(str, '\0', 50);
				strcpy((char*)str,"OK�Ϻ���ѧ.ͨ��ѧԺ. OK");
				NRF24_Write_Packet(str);
				//Delay_ms(1);
				NRF24_RxMode();
				
			}			
		}
		//debug_usart();
		
		if(debug_Label == 0x02)
		{
			debug_Label = 0;
			PM25_CE_OFF();
			CH4_CE_OFF();
		}
		if(debug_Label == 0x03)
		{
			debug_Label = 0;
			//sensor_deinit();
			printf("%d",HAL_ADC_GetValue(&hadc1));
			read_Wifi_Config(&wifi_conf);
			
		}
		if(debug_Label == 0x04)
		{
			debug_Label = 0;
			//if(Read_Inf() == GPIO_PIN_SET){printf("Y\n");}
			
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
			Delay_ms(500);
			HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_4);
		}
		if(debug_Label == 0x05)
		{
			debug_Label = 0;
			//flag_AT_mode = !flag_AT_mode;
			//printf("%d",flag_AT_mode);
			//ESP8266_NetConfig("4TEST-PC","12345678");
			ESP8266_StopTrans();
		}
		if(debug_Label == 0x06)
		{
			debug_Label = 0;
			memset(UDebug_Rec_Buffer,'\0',UDebug_REC_MAX_BYTES);
			UDebug_Rec_Point = 0x0;
			memset(UWifi_Rec_Buffer,'\0',UWifi_REC_MAX_BYTES);
			UWifi_Rec_Point = 0x0;
			
		}
		if(debug_Label == 0x0A)//"]"
		{
			debug_Label = 0;
			uint8_t tempStr[100];
			memset(tempStr,'\0',100);
			memcpy(tempStr,(char*)UDebug_Rec_Buffer,strlen((char*)UDebug_Rec_Buffer));
			
			printf("usartDebug==>usartWifi:%s",tempStr);
			UWifi_Send_String(tempStr);
			
			//clear
			memset(UDebug_Rec_Buffer,'\0',UDebug_REC_MAX_BYTES);
			UDebug_Rec_Point = 0x0;
			
			//clear
			//memset(UWifi_Send_Buffer,'\0',UWifi_SEND_MAX_BYTES);
			
			Delay_ms(1000);
			uint8_t tempStr2[100];
			memset(tempStr2,'\0',100);
			memcpy(tempStr2,(char*)UWifi_Rec_Buffer,strlen((char*)UWifi_Rec_Buffer));
			
			if(strstr((char*)tempStr2,"OK")!=NULL){printf("OK!");}
			if(strstr((char*)tempStr2,"ERROR")!=NULL){printf("ERROR!");}
			printf("usartWifi==>usartDebug:%s",tempStr2);
			//clear
			memset(UWifi_Rec_Buffer,'\0',UWifi_REC_MAX_BYTES);
			UWifi_Rec_Point = 0x0;
			
		}
		
		if(debug_Label == 0x08)
		{
			debug_Label = 0;
			//NRF24_pwdown();
			//NRF24_RxMode();
			//UWifi_Send_String("AT+CWMODE?\r\n");
			SetRTCTime_Test();
		}
		#endif
		
	}

  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI
                              |RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_HSI, RCC_MCODIV_1);

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
